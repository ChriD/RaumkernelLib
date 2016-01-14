
#include <raumkernel/manager/deviceManager.h>


namespace Raumkernel
{
    namespace Manager
    {
       
        DeviceManager::DeviceManager() : ManagerBase()
        {
        }


        DeviceManager::~DeviceManager()
        {          
        }


        void DeviceManager::lockDeviceList()
        {
            mutexDeviceLists.lock();
        }

        void DeviceManager::unlockDeviceList()
        {
            mutexDeviceLists.unlock();
        }

        
        void DeviceManager::addDevice(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string friendlyName, location, deviceXML, deviceUDN;
            std::shared_ptr<Devices::Device> device = nullptr;

            lockDeviceList();

            try
            {
                deviceUDN = Tools::CommonUtil::FormatUDN(_device.Udn());

                _device.GetAttribute("Upnp.DeviceXml", deviceXML);
                _device.GetAttribute("Upnp.Location", location);
                _device.GetAttribute("Upnp.FriendlyName", friendlyName);

                logDebug("Adding device '" + friendlyName + "' to manager", CURRENT_POSITION);    

                // add upnpDevice reference to our internal list and then inform ohNet UPNP Stack that we are holding a reference
                // to be sure we do not have any lost reference we check the map if there is the same device already inserted
                // (this should not be because "removeDevice" will alwayys be called before "addDevice")
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
                // if we got a pointer to a device, than the device is useable for the kernel
                if (device != nullptr)
                {
                    device->setCpDevice(&_device);      
                    device->setManagerEngineer(getManagerEngineer());
                   
                    if (std::dynamic_pointer_cast<Devices::MediaRenderer>(device))
                    {                        
                        if (mediaRendererMap.find(deviceUDN) != mediaRendererMap.end())
                            mediaRendererMap.erase(deviceUDN);
                        mediaRendererMap.insert(std::make_pair(deviceUDN, std::dynamic_pointer_cast<Devices::MediaRenderer>(device)));
                        logDebug("Media Renderer '" + friendlyName + "' is now useable!", CURRENT_POSITION);                       
                    }
                    // elseIf(...)

                    // TODO: Add to renderer or media server list
                    // ...
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

            unlockDeviceList(); 

            // list is unlocked. now fire signals
            //sigMediaRendererAdded.fire(std::dynamic_pointer_cast<Devices::MediaRenderer>(device));    
            sigMediaRendererAdded.fire_if(std::dynamic_pointer_cast<Devices::MediaRenderer>(device) != nullptr, std::dynamic_pointer_cast<Devices::MediaRenderer>(device));
            sigDeviceListChanged.fire();
        }

  
        void DeviceManager::removeDevice(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string friendlyName, deviceUDN;
            std::shared_ptr<Devices::Device> device = nullptr;

            lockDeviceList();

            try
            {
                deviceUDN = Tools::CommonUtil::FormatUDN(_device.Udn());           
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
                    mediaRendererMap.erase(deviceUDN); 
                    logDebug("Media Renderer '" + friendlyName + "' removed", CURRENT_POSITION);
                }

                // ...
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

            unlockDeviceList();

            if (device != nullptr)
            {
                sigMediaRendererAdded.fire_if(std::dynamic_pointer_cast<Devices::MediaRenderer>(device) != nullptr, std::dynamic_pointer_cast<Devices::MediaRenderer>(device));
            }
            sigDeviceListChanged.fire();
        }


        std::shared_ptr<Devices::MediaRenderer> DeviceManager::getMediaRenderer(std::string _udn)
        {
            std::lock_guard<std::mutex> lock(mutexDeviceLists);

            _udn = Tools::CommonUtil::FormatUDN(_udn);
            if (mediaRendererMap.find(_udn) == mediaRendererMap.end())
                return nullptr;
            auto device = (mediaRendererMap.find(_udn)->second);
            return device;
        }

    }
}