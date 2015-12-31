
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        ManagerEngineer::ManagerEngineer() : RaumkernelBase()
        {
            settingsManager = nullptr;
            upnpManager = nullptr;
        }


        ManagerEngineer::~ManagerEngineer()
        {
        }


        void ManagerEngineer::createManagers()
        {
            // create the settings manager wich will hold all of the settings for the kernel and the corresponding app
            logDebug("Create Settings Manager...", CURRENT_FUNCTION);
            settingsManager = std::shared_ptr<Manager::SettingsManager>(new Manager::SettingsManager());            
            settingsManager->setLogObject(getLogObject());

            // create the UPNPDevice Manager which will hold all UPNP devices found in the networt (OhNetDevices)
            logDebug("Create UPNP-Device Manager...", CURRENT_FUNCTION);
            upnpManager = std::shared_ptr<Manager::UPNPManager>(new Manager::UPNPManager());            
            upnpManager->setLogObject(getLogObject());
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

    }
}