
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
            zoneManager = nullptr;
            mediaListManager = nullptr;
        }


        ManagerEngineer::~ManagerEngineer()
        {
            logDebug("Destroying ManagerEngineer", CURRENT_POSITION);
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
         
            // create the Zone-Manager which will handle the requests to the RF-Host
            logDebug("Create Zone-Manager...", CURRENT_FUNCTION);
            zoneManager = std::shared_ptr<Manager::ZoneManager>(new Manager::ZoneManager());
            zoneManager->setLogObject(getLogObject());    

            // create the MediaList-Manager which will handle the media lists of the zones and other ones...
            logDebug("Create MediaList-Manager...", CURRENT_FUNCTION);
            mediaListManager = std::shared_ptr<Manager::MediaListManager>(new Manager::MediaListManager());
            mediaListManager->setLogObject(getLogObject());
        }


        std::shared_ptr<SettingsManager> ManagerEngineer::getSettingsManager()
        {
            logDebug("Calling SettingsManager!", CURRENT_POSITION);
            if (!settingsManager)
                logError("Calling SettingsManager without existance!", CURRENT_POSITION);
            return settingsManager;
        }


        std::shared_ptr<UPNPManager> ManagerEngineer::getUPNPManager()
        {
            logDebug("Calling UPNPManager!", CURRENT_POSITION);
            if (!upnpManager)
                logError("Calling UPNPManager without existance!", CURRENT_POSITION);
            return upnpManager;
        }


        std::shared_ptr<DeviceManager> ManagerEngineer::getDeviceManager()
        {
            logDebug("Calling DeviceManager!", CURRENT_POSITION);
            if (!deviceManager)
                logError("Calling DeviceManager without existance!", CURRENT_POSITION);
            return deviceManager;
        }


        std::shared_ptr<ZoneManager> ManagerEngineer::getZoneManager()
        {
            logDebug("Calling ZoneManager!", CURRENT_POSITION);
            if (!zoneManager)
                logError("Calling ZoneManager without existance!", CURRENT_POSITION);
            return zoneManager;
        }


        std::shared_ptr<MediaListManager> ManagerEngineer::getMediaListManager()
        {
            logDebug("Calling MediaListManager!", CURRENT_POSITION);
            if (!mediaListManager)
                logError("Calling MediaListManager without existance!", CURRENT_POSITION);
            return mediaListManager;
        }


    }
}