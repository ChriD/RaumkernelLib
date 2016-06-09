
#include <raumkernel/manager/upnpManager.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        UPNPManager::UPNPManager() : ManagerBase()
        {    
            upupDeviceListAll = nullptr;
            stopThreads = false;
            refreshDeviceListThreadStarted = false;
        }


        UPNPManager::~UPNPManager()
        {
            stopThreads = true;
            if (refreshDeviceListThreadStarted && refreshDeviceListThreadObject.joinable())
            {
                logDebug("Waiting for DeviceRefeshList thread to finish (This may take some time...)", CURRENT_POSITION);
                refreshDeviceListThreadObject.join();
            }

            logDebug("Closing OpenHome UPNP Control Stack", CURRENT_POSITION);
            OpenHome::Net::UpnpLibrary::Close();

            logDebug("Destroying UPNP-Manager", CURRENT_POSITION);
        }


        void UPNPManager::init(std::string _networkAdapterName)
        {            
            OpenHome::Net::InitialisationParams*		initParams;
            std::vector<OpenHome::NetworkAdapter*>*		networkAdapterList;
            std::vector<NetworkAdapterIdentifier>       preferedNetworkAdapterList;
            std::int8_t                                 networkAdapterIdx = -1;
            TIpAddress									networkAdapterAddress;

            try
            {

                logDebug("Init OpenHome UPNP Control Stack", CURRENT_POSITION);

                initParams = OpenHome::Net::InitialisationParams::Create();
                OpenHome::Net::UpnpLibrary::Initialise(initParams);                                

                if (!_networkAdapterName.empty())
                    preferedNetworkAdapterList.emplace_back(NetworkAdapterIdentifier(_networkAdapterName, 0));

                for (std::uint16_t priorityIdx = 1; priorityIdx <= 10; priorityIdx++)
                {
                    std::int32_t waitTime = 0;
                    std::string nodeName = SETTINGS_RAUMKERNEL_NETWORKADAPTERNAME + "[@priority='" + std::to_string(priorityIdx) + "']";
                    _networkAdapterName = getManagerEngineer()->getSettingsManager()->getValue(nodeName);
                    if (!_networkAdapterName.empty())
                    {
                        auto waitForAppearanceValue = getManagerEngineer()->getSettingsManager()->getAttributeValue(nodeName, "waitForAppearance");
                        if (!waitForAppearanceValue.empty())
                            waitTime = std::stoi(waitForAppearanceValue);
                        preferedNetworkAdapterList.emplace_back(NetworkAdapterIdentifier(_networkAdapterName, waitTime));
                    }
                }                

                if (preferedNetworkAdapterList.empty())
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

                // output adapter names from the upnp stack
                for (std::uint8_t i = 0; i < (*networkAdapterList).size(); i++)
                {
                    std::string adapterName = (*networkAdapterList)[i]->Name();
                    logDebug("Adapter " + std::to_string(i) + ": " + adapterName, CURRENT_POSITION);                   
                }

                // try to use the prefered adapter beginning with the topmost priority
                for (auto preferedAdapter : preferedNetworkAdapterList)
                {
                    std::int32_t waitedMS = 0;
                    logDebug("Waiting for Adapter " + preferedAdapter.adapterIdentifier + " to appear", CURRENT_POSITION);

                    while (true)
                    {
                        // iterate through the list of the stack and try to find the adapter with the given name
                        for (std::uint8_t i = 0; i < (*networkAdapterList).size(); i++)
                        {
                            std::string adapterName = (*networkAdapterList)[i]->Name();
                            if (adapterName == preferedAdapter.adapterIdentifier)
                            {
                                networkAdapterIdx = i;
                                break;
                            }
                        }

                        // if we have not found the adapter then wait a little bit and try it again
                        if (networkAdapterIdx < 0)
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                            OpenHome::Net::UpnpLibrary::RefreshNetworkAdapterList();
                            waitedMS += 50;
                        }
                        else
                        {
                            break;
                        }

                        if (waitedMS > preferedAdapter.timeToWaitForAdapterMS && preferedAdapter.timeToWaitForAdapterMS != -1)
                            break;
                    }

                    // adapter 
                    if (networkAdapterIdx >= 0)
                        break;                            
                }

                // if we have defined a network adapter name, but we did not find it in the networkAdapter list we will give some warning
                if (!preferedNetworkAdapterList.empty() && networkAdapterIdx == -1)
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
            OpenHome::Net::FunctorCpDeviceCpp functorDeviceFound = OpenHome::Net::MakeFunctorCpDeviceCpp(*this, &UPNPManager::onDeviceFound);
            OpenHome::Net::FunctorCpDeviceCpp functorDeviceLost = OpenHome::Net::MakeFunctorCpDeviceCpp(*this, &UPNPManager::onDeviceLost);       
            upupDeviceListAll = new OpenHome::Net::CpDeviceListCppUpnpAll(functorDeviceFound, functorDeviceLost);   

            // start  
            if (!refreshDeviceListThreadStarted)
            {
                std::uint32_t refreshTime = 30000;
                std::string refreshTimeActiveString = getManagerEngineer()->getSettingsManager()->getValue(Raumkernel::Manager::SETTINGS_RAUMKERNEL_UPNPREFRESHTIMEACTIVE);
                std::string refreshTimeString   = getManagerEngineer()->getSettingsManager()->getValue(Raumkernel::Manager::SETTINGS_RAUMKERNEL_UPNPREFRESHTIME);
                if (!refreshTimeString.empty() && refreshTimeActiveString == "1")
                {
                    if (refreshTimeString.empty())
                    {
                        logWarning("UPNP refresh time is not set. Will use Standard value of " + std::to_string(refreshTime) + "ms", CURRENT_POSITION);
                    }
                    else
                    {
                        refreshTime = std::stoi(refreshTimeString);
                    }
                    logDebug("Starting UPNP-Stack auto referesh thread", CURRENT_POSITION);
                    refreshDeviceListThreadObject = std::thread(&UPNPManager::refreshDeviceListThread, this, std::ref(stopThreads), refreshTime);
                    refreshDeviceListThreadStarted = true;
                }
                else
                {
                    logWarning("UPNP refresh time is disabled!", CURRENT_POSITION);
                }
            }
        }

        
        void UPNPManager::refresh()
        {
            // force refreshing of the upnpDevice list which may lead to 'deviceFound' or 'deviceLost' signals
            if (upupDeviceListAll != nullptr)                
                upupDeviceListAll->Refresh();
        }


        // will be called if a UPNP Device is found in the network
        void UPNPManager::onDeviceFound(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string deviceFriendlyName;
            _device.GetAttribute("Upnp.FriendlyName", deviceFriendlyName);
            logDebug("UPNP Device found: " + deviceFriendlyName + "(" + _device.Udn() + ")", CURRENT_POSITION);
            getManagerEngineer()->getDeviceManager()->addDevice(_device);           
        }


        // will be called if a UPNP Device disappears from the network
        void UPNPManager::onDeviceLost(OpenHome::Net::CpDeviceCpp& _device)
        {
            std::string deviceFriendlyName;
            _device.GetAttribute("Upnp.FriendlyName", deviceFriendlyName);
            logDebug("UPNP Device lost: " + deviceFriendlyName + "(" + _device.Udn() + ")", CURRENT_POSITION);
            getManagerEngineer()->getDeviceManager()->removeDevice(_device);
        }

   
            
        void UPNPManager::refreshDeviceListThread(std::atomic_bool &_stopThread, std::uint32_t _refreshTimeMS)
        {     
            std::uint32_t timeCount = 0;
            while (!_stopThread)
            {
                try
                {                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));   
                    timeCount += 500;
                    if (timeCount > _refreshTimeMS)
                    {
                        logDebug("Refreshing UPNP device list", CURRENT_POSITION);
                        refresh();
                        timeCount = 0;
                    }
                }
                catch (Raumkernel::Exception::RaumkernelException &e)
                {
                    if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                        throw e;
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
            }
        }

    }
}