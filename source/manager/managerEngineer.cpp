
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        ManagerEngineer::ManagerEngineer() : RaumkernelBase()
        {
            settingsManager = nullptr;
            upnpManager = nullptr;
            deviceManager = nullptr;
            subscriptionReceiverManager = nullptr;            
        }


        ManagerEngineer::~ManagerEngineer()
        {
        }


        void ManagerEngineer::createManagers()
        {
            // create the settings manager wich will hold all of the settings for the kernel and the corresponding app
            logDebug("Create Settings-Manager...", CURRENT_FUNCTION);
            settingsManager = std::shared_ptr<Manager::SettingsManager>(new Manager::SettingsManager());            
            settingsManager->setLogObject(getLogObject());

            // create the UPNP-Manager which will hold all UPNP devices found in the networt (OhNetDevices)
            logDebug("Create UPNP-Manager...", CURRENT_FUNCTION);
            upnpManager = std::shared_ptr<Manager::UPNPManager>(new Manager::UPNPManager());            
            upnpManager->setLogObject(getLogObject());

            // create the Device-Manager which will hold all UPNP devices found in the networt 
            logDebug("Create Device-Manager...", CURRENT_FUNCTION);
            deviceManager = std::shared_ptr<Manager::DeviceManager>(new Manager::DeviceManager());
            deviceManager->setLogObject(getLogObject());

            // create the SubscriptionReceiver-Manager which will handle the subcsription returns from the upnp devices
            logDebug("Create SubscriptionReceiver-Manager...", CURRENT_FUNCTION);
            subscriptionReceiverManager = std::shared_ptr<Manager::SubscriptionReceiverManager>(new Manager::SubscriptionReceiverManager());
            subscriptionReceiverManager->setLogObject(getLogObject());
         
            // create the Zone-Manager which will handle the requests to the RF-Host
            logDebug("Create Zoone-Manager...", CURRENT_FUNCTION);
            zoneManager = std::shared_ptr<Manager::ZoneManager>(new Manager::ZoneManager());
            zoneManager->setLogObject(getLogObject());            
        }


        std::shared_ptr<SettingsManager> ManagerEngineer::getSettingsManager()
        {
            return settingsManager;
        }


        std::shared_ptr<UPNPManager> ManagerEngineer::getUPNPManager()
        {
            return upnpManager;
        }


        std::shared_ptr<DeviceManager> ManagerEngineer::getDeviceManager()
        {
            return deviceManager;
        }


        std::shared_ptr<SubscriptionReceiverManager> ManagerEngineer::getSubscriptionReceiverManager()
        {
            return subscriptionReceiverManager;
        }


        std::shared_ptr<ZoneManager> ManagerEngineer::getZoneManager()
        {
            return zoneManager;
        }


    }
}