
#include <raumkernel/manager/upnpManager.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        UPNPManager::UPNPManager() : ManagerBase()
        {    
            upupDeviceListAll = nullptr;
        }


        UPNPManager::~UPNPManager()
        {
            logDebug("Closing OpenHome UPNP Control Stack", CURRENT_POSITION);
            OpenHome::Net::UpnpLibrary::Close();
        }


        void UPNPManager::init(std::string _networkAdapterName)
        {            
            OpenHome::Net::InitialisationParams*		initParams;
            std::vector<OpenHome::NetworkAdapter*>*		networkAdapterList;
            std::int8_t                                 networkAdapterIdx = -1;
            TIpAddress									networkAdapterAddress;

            try
            {

                logDebug("Init OpenHome UPNP Control Stack", CURRENT_POSITION);

                initParams = OpenHome::Net::InitialisationParams::Create();
                OpenHome::Net::UpnpLibrary::Initialise(initParams);

                // get network adapter name either from parameter or from settings
                if (_networkAdapterName.empty())
                    _networkAdapterName = getManagerEngineer()->getSettingsManager()->getValue(SETTINGS_RAUMKERNEL_NETWORKADAPTERNAME);

                if (_networkAdapterName.empty())
                {
                    logInfo("Network adapter name not specified! Raumkernel will use the first one found!", CURRENT_POSITION);
                    networkAdapterIdx = 0;
                }

                logDebug("Retrieve network adapter list", CURRENT_POSITION);
                networkAdapterList = OpenHome::Net::UpnpLibrary::CreateSubnetList();

                if ((*networkAdapterList).size() == 0)
                {
                    logCritical("No network adapter available!", CURRENT_POSITION);
                    throw Raumkernel::Exception::RaumkernelException(Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH, CURRENT_POSITION, "Unrecoverable error! ABORT!", 200);
                }

                // iterate through the list and try to find the adapter with the given name
                for (std::uint8_t i = 0; i < (*networkAdapterList).size(); i++)
                {
                    std::string adapterName = (*networkAdapterList)[i]->Name();
                    logDebug("Adapter " + std::to_string(i) + ": " + adapterName, CURRENT_POSITION);
                    if (!_networkAdapterName.empty() && adapterName == _networkAdapterName)
                    {
                        networkAdapterIdx = i;
                    }
                }

                // if we have defined a network adapter name, but we did not find it in the networkAdapter list we will give some warning
                if (!_networkAdapterName.empty() && networkAdapterIdx == -1)
                {
                    logWarning("Network adapter '" + _networkAdapterName + "' not found! Raumkernel will use the first one found!", CURRENT_POSITION);
                    networkAdapterIdx = 0;
                }

                std::string adapterName = (*networkAdapterList)[networkAdapterIdx]->Name();
                logDebug("Using Network Adapter : " + adapterName, CURRENT_POSITION);
                logDebug("Getting IP-Subnet of adapter", CURRENT_POSITION);
                networkAdapterAddress = (*networkAdapterList)[networkAdapterIdx]->Subnet();

                // clean up the subnet list, we do not need it anymore...
                OpenHome::Net::UpnpLibrary::DestroySubnetList(networkAdapterList);
               
                logInfo("Starting OpenHome UPNP Control Stack with network adapter: " + adapterName, CURRENT_POSITION);
                OpenHome::Net::UpnpLibrary::StartCp(networkAdapterAddress);

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
            }
            catch (std::exception &e)
            {
                throw e;
            }
            catch (std::string &e)
            {
                throw e;
            }
            catch (OpenHome::Exception &e)
            {
                throw e;
            }
            catch (...)
            {
                throw std::runtime_error("Unknown exception! [UPNPManager::initUPNP]");
            }

        }


        void UPNPManager::discover()
        {           
            // start discover for all UPNP devices on the network. We may also get devices we are not interested in but the screening will be done by the 'DeviceManager'
            OpenHome::Net::FunctorCpDeviceCpp functorDeviceFound = OpenHome::Net::MakeFunctorCpDeviceCpp(*this, &UPNPManager::OnDeviceFound);
            OpenHome::Net::FunctorCpDeviceCpp functorDeviceLost = OpenHome::Net::MakeFunctorCpDeviceCpp(*this, &UPNPManager::OnDeviceLost);       
            upupDeviceListAll = new OpenHome::Net::CpDeviceListCppUpnpAll(functorDeviceFound, functorDeviceLost);            
        }

        
        void UPNPManager::refresh()
        {
            // forec refreshing of the upnpDevice list which may lead to 'deviceFound' or 'deviceLost' signals
            if (upupDeviceListAll != nullptr)                
                upupDeviceListAll->Refresh();
        }


        // DeviceManager::DeviceFound
        // will be called if a UPNP Device is found in the network
        void UPNPManager::OnDeviceFound(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string deviceFriendlyName;
            _device.GetAttribute("Upnp.FriendlyName", deviceFriendlyName);
            logDebug("UPNP Device found: " + deviceFriendlyName + "(" + _device.Udn() + ")", CURRENT_POSITION);
            //getManagerEngineer()->getDeviceManager()->addDevice(_device);

            /*
            bool deviceAlreadyInList = false;
            std::string friendlyName, location, deviceXML, deviceUDN;
            UPNPDevice *upnpDevice = nullptr;

            this->Lock();

            try
            {
                deviceUDN = Utils::FormatUDN(_device.Udn());

                _device.GetAttribute("Upnp.DeviceXml", deviceXML);
                _device.GetAttribute("Upnp.Location", location);
                _device.GetAttribute("Upnp.FriendlyName", friendlyName);

                this->Log(LogType::LOGDEBUG, "Found device: " + friendlyName, __FUNCTION__);

                // we add a refrence of the device to our internal list and to be sure we do not store it twice we do delete
                // all devices with the same UDN before. This should normaly not happen because "onDeviceLost" should be called before
                this->RemoveDeviceClassRef(deviceUDN);
                this->RemoveDeviceRef(deviceUDN);

                // create the proper UPNPDevice class derviate and add it to the clasDevice ref map
                // we do set a pointer link to the CPDevice the UPNPDevice is attached to
                upnpDevice = this->CreateUPNPDeviceObjectFromDeviceXML(deviceXML);
                if (upnpDevice)
                {
                    upnpDevice->SetCpDevice(&_device);
                    this->AddDeviceClassRef(upnpDevice);
                }

                this->AddDeviceRef(_device);
                _device.AddRef();

            }
            catch (std::exception &ex)
            {
                this->Log(LogType::LOGERROR, ex.what(), __FUNCTION__);
            }
            catch (const std::string& ex)
            {
                this->Log(LogType::LOGERROR, ex, __FUNCTION__);
            }
            catch (...)
            {
                this->Log(LogType::LOGERROR, "Unresolved Error", __FUNCTION__);
            }

            this->UnLock();


            if (friendlyName == raumkernSettings.RAUMKERNEL_FRIENDLYNAME_CONFIGDEVICE)
            {
                this->Log(LogType::LOGINFO, "Configuration service found! (Location: " + location + ")", __FUNCTION__);
                this->OnConfigDeviceFound(_device);
            }

            // if we found a raumfeld media server, then signal out!
            if (upnpDevice && dynamic_cast<RaumfeldMediaServer*>(upnpDevice))
            {
                // if we found the raumfeld media server, the content manager has to subscribe to it, so that the content manager is aware of list changes, ect...
                managerList.contentManager->SubscribeToMediaServer();
                signalMediaServerFound();
            }

            signalDeviceListChanged();
            */
        }


        // DeviceManager::DeviceLost
        // will be called if a UPNP Device disappears from the network
        void UPNPManager::OnDeviceLost(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string deviceFriendlyName;
            _device.GetAttribute("Upnp.FriendlyName", deviceFriendlyName);
            logDebug("UPNP Device lost: " + deviceFriendlyName + "(" + _device.Udn() + ")", CURRENT_POSITION);
            //getManagerEngineer()->getDeviceManager()->removeDevice(_device);


            /*
            std::string friendlyName, location;
            std::string deviceUDN;
            bool mediaServerRemoved = false;

            this->Lock();

            try
            {
                deviceUDN = Utils::FormatUDN(_device.Udn());

                _device.GetAttribute("Upnp.Location", location);
                _device.GetAttribute("Upnp.FriendlyName", friendlyName);

                this->Log(LogType::LOGDEBUG, "Lost device: " + friendlyName, __FUNCTION__);

                // remove the DeviceClass (eg. MediaRenderer, MediaServer,..) and the device reference (CPdevice) itself
                if (this->GetMediaServer(deviceUDN))
                    mediaServerRemoved = true;

                this->RemoveDeviceClassRef(deviceUDN);
                this->RemoveDeviceRef(deviceUDN);

            }
            catch (std::exception &ex)
            {
                this->Log(LogType::LOGERROR, ex.what(), __FUNCTION__);
            }
            catch (const std::string& ex)
            {
                this->Log(LogType::LOGERROR, ex, __FUNCTION__);
            }
            catch (...)
            {
                this->Log(LogType::LOGERROR, "Unresolved Error", __FUNCTION__);
            }

            this->UnLock();

            if (friendlyName == raumkernSettings.RAUMKERNEL_FRIENDLYNAME_CONFIGDEVICE)
            {
                this->Log(LogType::LOGWARNING, "Configuration service lost! (Location: " + location + ")", __FUNCTION__);
                this->OnConfigDeviceLost(_device);
            }

            if (mediaServerRemoved)
                signalMediaServerFound();

            signalDeviceListChanged();
            */

        }

    }
}