
#include <raumkernel/manager/deviceManager.h>
#include <raumkernel/manager/zoneManager.h>
#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{
    namespace Manager
    {
       
        DeviceManager::DeviceManager() : ManagerBase()
        {
        }


        DeviceManager::~DeviceManager()
        {       
            logDebug("Destroying Device-Manager", CURRENT_POSITION);
        }


        void DeviceManager::lock()
        {            
            mutexDeviceLists.lock();
        }

        void DeviceManager::unlock()
        {            
            mutexDeviceLists.unlock();
        }


        std::unordered_map<std::string, Devices::MediaRenderer*> DeviceManager::getMediaRenderers()
        {
            return mediaRendererMap;
        }


        std::unordered_map<std::string, Devices::MediaServer*> DeviceManager::getMediaServers()
        {
            return mediaServerMap;
        }

        
        void DeviceManager::addDevice(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string friendlyName, location, deviceXML, deviceUDN;
            Devices::Device* device = nullptr;

            // when adding a new device we have to be sure that the device manager and zone manager are locked
            // if not we do wait until it gets unlocked and then proceed witg adding the device
            lock();
            getManagerEngineer()->getZoneManager()->lock();

            try
            {
                deviceUDN = Tools::CommonUtil::formatUDN(_device.Udn());

                _device.GetAttribute("Upnp.DeviceXml", deviceXML);
                _device.GetAttribute("Upnp.Location", location);
                _device.GetAttribute("Upnp.FriendlyName", friendlyName);              

                logDebug("Adding device '" + friendlyName + "' to manager", CURRENT_POSITION);    

                // add upnpDevice reference to our internal list and then inform ohNet UPNP Stack that we are holding a reference
                // to be sure we do not have any lost reference we check the map if there is the same device already inserted
                // (this should not be because "removeDevice" will always be called before "addDevice")
                if (upnpDeviceMap.find(deviceUDN) != upnpDeviceMap.end())
                {                    
                    upnpDeviceMap.erase(deviceUDN);
                    _device.RemoveRef();
                }
                upnpDeviceMap.insert(std::make_pair(deviceUDN, &_device));
                _device.AddRef();

                // create the propper UPNPDevice class from the device xml, we can use the deviceCreator for this
                Devices::DeviceCreator deviceCreator;
                deviceCreator.setLogObject(getLogObject());
                deviceCreator.setManagerEngineer(getManagerEngineer());                
                device = deviceCreator.createDeviceFromDeviceXML(deviceXML);

                // do not add non raumfeld devices
                if (device != nullptr && device->getIsRaumfeldDevice() == false && getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_ADDNONRAUMFELDDEVICES) == "0")
                {
                    logDebug("Sevice '" + friendlyName + "' is not a Raumfeld Device! Skip adding!", CURRENT_POSITION);
                    // this will release the memory because its a shared pointer;
                    device = nullptr;
                }

                // if we got a pointer to a device, than the device is useable for the kernel
                if (device != nullptr)
                {
                    device->setManagerEngineer(getManagerEngineer());
                    device->setCpDevice(&_device);       
                                
                    if (dynamic_cast<Devices::MediaRenderer*>(device))                          
                    {
                        if (mediaRendererMap.find(deviceUDN) != mediaRendererMap.end())
                            mediaRendererMap.erase(deviceUDN);
                        mediaRendererMap.insert(std::make_pair(deviceUDN, dynamic_cast<Devices::MediaRenderer*>(device)));
                        logDebug("Media Renderer '" + friendlyName + "' is now useable!", CURRENT_POSITION);     

                        // set room state to "online" if renderer which is added is found in zone management 
                        getManagerEngineer()->getZoneManager()->setRoomOnlineForRenderer(deviceUDN, true);                      
                    }
                    else if (dynamic_cast<Devices::MediaServer*>(device)) 
                    {
                        if (mediaServerMap.find(deviceUDN) != mediaServerMap.end())
                            mediaServerMap.erase(deviceUDN);
                        mediaServerMap.insert(std::make_pair(deviceUDN, dynamic_cast<Devices::MediaServer*>(device)));
                        logDebug("Media Server '" + friendlyName + "' is now useable!", CURRENT_POSITION);
                        
                        // if its the raumfeld media server we will store the udn so we can find him any time we want in our list
                        if (dynamic_cast<Devices::MediaServer_Raumfeld*>(device))                        
                        {
                            raumfeldMediaServerUDN = Tools::CommonUtil::formatUDN(deviceUDN);                            
                            _device.GetAttribute("Upnp.Location", location);                          
                            std::int16_t firstPosIP = location.find_first_of(":") + 3;
                            raumfeldHostIP = location.substr(firstPosIP, location.find_last_of(":") - firstPosIP);                             
                        }
                    }  

                    // its oka< to signal raw pointer because the list is locked and the signal will be processed sync
                    sigMediaRendererAdded.fire_if(dynamic_cast<Devices::MediaRenderer*>(device) != nullptr, dynamic_cast<Devices::MediaRenderer*>(device));
                    sigMediaServerAdded.fire_if(dynamic_cast<Devices::MediaServer*>(device) != nullptr, dynamic_cast<Devices::MediaServer*>(device));
                    sigDeviceListChanged.fire();
                }
                else
                {                    
                    upnpDeviceMap.erase(deviceUDN);
                    _device.RemoveRef();
                }
               
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logError(e.what(), CURRENT_POSITION);
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_POSITION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_POSITION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {                
                logError("Unknown exception!", CURRENT_POSITION);
            }

            getManagerEngineer()->getZoneManager()->unlock();
            unlock();             
        }

  
        void DeviceManager::removeDevice(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string friendlyName, deviceUDN;
            Devices::Device* device = nullptr;

            lock();
            getManagerEngineer()->getZoneManager()->lock();

            try
            {
                deviceUDN = Tools::CommonUtil::formatUDN(_device.Udn());           
                _device.GetAttribute("Upnp.FriendlyName", friendlyName);

                logDebug("Removing device '" + friendlyName + "' from manager", CURRENT_POSITION);

                // remove from device list

                // remove upnpDevice reference to our internal list and then inform ohNet UPNP Stack that we are releasing a reference
                if (upnpDeviceMap.find(deviceUDN) != upnpDeviceMap.end())
                {
                    upnpDeviceMap.erase(deviceUDN);
                    _device.RemoveRef();
                    logDebug("UPNP device '" + friendlyName + "' removed", CURRENT_POSITION);
                }
                else
                {
                    logWarning("Could not find device " + friendlyName + " (" + deviceUDN + ") in device list!", CURRENT_POSITION);
                }

                // remove from media renderer map
                if (mediaRendererMap.find(deviceUDN) != mediaRendererMap.end())
                {                   
                    device = (mediaRendererMap.find(deviceUDN)->second);
                    device->setCpDevice(nullptr);
                    // signal the removeing of the renderer (before it goes out of scope)
                    sigMediaRendererRemoved.fire_if(dynamic_cast<Devices::MediaRenderer*>(device) != nullptr, dynamic_cast<Devices::MediaRenderer*>(device));                    
                    // Kill all threads on the device (eg. FadeToVolume thread!)
                    mediaRendererMap[deviceUDN]->beforeDelete();
                    // delete object before removing from the pointer list
                    delete mediaRendererMap[deviceUDN];
                    mediaRendererMap.erase(deviceUDN); 
                    logDebug("Media Renderer '" + friendlyName + "' removed", CURRENT_POSITION);

                    // set room state to "offline" if renderer which is removed is found in zone management 
                    // INFO: Okay there may be more than one renderers attached to a room, but for now we do not consider this here!
                    getManagerEngineer()->getZoneManager()->setRoomOnlineForRenderer(deviceUDN, false);
                }

                // remove from media servers map
                if (mediaServerMap.find(deviceUDN) != mediaServerMap.end())
                {
                    device = (mediaServerMap.find(deviceUDN)->second);
                    device->setCpDevice(nullptr);
                    
                    // well, we lost our raumfeld media server. That's too bad
                    if (dynamic_cast<Devices::MediaServer_Raumfeld*>(device))
                    {
                        raumfeldMediaServerUDN = "";
                        raumfeldHostIP = "";
                    }
                    // signal the removeing of the server (before it goes out of scope)
                    sigMediaServerRemoved.fire_if(dynamic_cast<Devices::MediaServer*>(device) != nullptr, dynamic_cast<Devices::MediaServer*>(device));
                    // Kill all threads on the device
                    mediaRendererMap[deviceUDN]->beforeDelete();
                    // delete object before removing from the pointer list
                    delete mediaServerMap[deviceUDN];
                    mediaServerMap.erase(deviceUDN);                   
                    logDebug("Media Server '" + friendlyName + "' removed", CURRENT_POSITION);
                }     

                sigDeviceListChanged.fire();

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logError(e.what(), CURRENT_POSITION);
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_POSITION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_POSITION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logError("Unknown exception!", CURRENT_POSITION);
            }

            getManagerEngineer()->getZoneManager()->unlock();
            unlock();            
        }


        Devices::MediaRenderer* DeviceManager::getMediaRenderer(std::string _udn)
        {         
            _udn = Tools::CommonUtil::formatUDN(_udn);
            if (mediaRendererMap.find(_udn) == mediaRendererMap.end())
                return nullptr;
            auto device = (mediaRendererMap.find(_udn)->second);
            return device;
        }


        Devices::MediaServer* DeviceManager::getMediaServer(std::string _udn)
        {           
            _udn = Tools::CommonUtil::formatUDN(_udn);
            if (mediaServerMap.find(_udn) == mediaServerMap.end())
                return nullptr;
            auto device = (mediaServerMap.find(_udn)->second);
            return device;
        }


        Devices::MediaServer_Raumfeld* DeviceManager::getRaumfeldMediaServer()
        {
            if (raumfeldMediaServerUDN.empty())
                return nullptr;
            if (mediaServerMap.find(raumfeldMediaServerUDN) == mediaServerMap.end())
                return nullptr;
            auto device = (mediaServerMap.find(raumfeldMediaServerUDN)->second);
            return (Devices::MediaServer_Raumfeld*)device;
        }


        std::string DeviceManager::getRaumfeldHostIP()
        {
            return raumfeldHostIP;
        }


    }
}