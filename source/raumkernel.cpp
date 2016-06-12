
#include <raumkernel/raumkernel.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{

    Raumkernel::Raumkernel() : RaumkernelBaseMgr()
    {    
        isOnline = false;
    }


    Raumkernel::~Raumkernel()
    {
    } 


    void Raumkernel::initLogObject(Log::LogType _defaultLogLevel, const std::string &_logFilePath, const std::vector<std::shared_ptr<Log::LogAdapter>> &_adapterList)
    {
        // create the log object (if not already provided) which will be used throughout the whole kernel and his modules                
        logObject = std::shared_ptr<Log::Log>(new Log::Log());

        // we do register some log adapters for the log object with standard values and set to log only ERRORS and CRITICALERRORS
        // the log level itself will be set after reading the settings file but we want to have logging while reading settings file
        // so we create the logObject with some standard values if they are not given
        if (_adapterList.empty())
        {
            auto logAdapterConsole = std::shared_ptr<Log::LogAdapter_Console>(new Log::LogAdapter_Console());
            logObject->registerAdapter(logAdapterConsole);

            auto logAdapterFile = std::shared_ptr<Log::LogAdapter_File>(new Log::LogAdapter_File());
            if (!_logFilePath.empty())
                logAdapterFile->setLogFilePath(_logFilePath);
            logObject->registerAdapter(logAdapterFile);            
        }
        else
        {
            for (auto i : _adapterList)
            {
                logObject->registerAdapter(i);
            }
        }

        logObject->setLogLevel(_defaultLogLevel);
    }


    void Raumkernel::init(const std::string &_settingsFileName)
    {        

        logDebug("Preparing Kernel-Manager-Engineer...", CURRENT_POSITION);

        // create the manager engineer which will hold references to all managers. this engineer will be present in each manager and each class
        // which is inherited from 'RaumfeldBaseMgr', but has to be set explicit
        managerEngineer = std::shared_ptr<Manager::ManagerEngineer>(new Manager::ManagerEngineer());
        managerEngineer->setLogObject(logObject);
        managerEngineer->createManagers();

        // set links to the manager engineer for all managers (this is a little bit of circular dependencies because the managers have a link to the
        // managerEngineer, which has links to the managers again. But this should be no problem, in this case)
        managerEngineer->getSettingsManager()->setManagerEngineer(managerEngineer);        
        managerEngineer->getUPNPManager()->setManagerEngineer(managerEngineer);
        managerEngineer->getDeviceManager()->setManagerEngineer(managerEngineer);                  
        managerEngineer->getZoneManager()->setManagerEngineer(managerEngineer);
        managerEngineer->getMediaListManager()->setManagerEngineer(managerEngineer);

        logDebug("Raumkernel Manager-Engineer is prepared", CURRENT_POSITION);

        // all managers are now created and we can work with them. so first lets get the settings manager in action and let it read our kernel 
        // and application settings.      
        if (!_settingsFileName.empty())
            managerEngineer->getSettingsManager()->setFileName(_settingsFileName);
        managerEngineer->getSettingsManager()->initSettings();

        // okay now, when the settingsManager is ready and we have loaded the settings we may get the log settings (log level)   
        std::string logLevelString = managerEngineer->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_LOGLEVEL);
        logObject->setLogLevel(Log::Log::logTypeStringToLogType(logLevelString));
        logDebug("Log level was set to: " + logLevelString, CURRENT_POSITION);

        // lets do some subscriptions
        connections.connect(managerEngineer->getDeviceManager()->sigMediaServerAdded, this, &Raumkernel::onMediaServerAdded);
        connections.connect(managerEngineer->getDeviceManager()->sigMediaServerRemoved, this, &Raumkernel::onMediaServerRemoved);        
        connections.connect(logObject->sigLog, this, &Raumkernel::onLog);
        
            
        // let's wake up the UPNP Stack and start discovering UPNP devices of all kinds
        managerEngineer->getUPNPManager()->init();        
        managerEngineer->getUPNPManager()->discover();

        // the zone manager has to request the actual zone configuration which can be done by long polling a special request        
        managerEngineer->getZoneManager()->init();        
        
        logInfo("Kernel initialized! Waiting for Raumfeld System to appear!", CURRENT_POSITION);
    }


    void Raumkernel::onMediaServerAdded(std::shared_ptr<Devices::MediaServer> _mediaServer)
    {
        // if the raumfeld media server was added, we can be sure that we have a ip for the requests
        // so we can start the zone configuration request    
        if (_mediaServer->isRaumfeldMediaServer())
        {
            managerEngineer->getZoneManager()->startZoneRequests();
            managerEngineer->getMediaListManager()->setMediaServer(std::dynamic_pointer_cast<Devices::MediaServer_Raumfeld>(_mediaServer));

            getManagerEngineer()->getDeviceManager()->lockDeviceList();
            getManagerEngineer()->getZoneManager()->lockLists();

            try
            {
                // It may be that renderers are online before the media server is online or is found
                // Due the media renderers inform the media list manager that he should load their playlists from the
                // media server and the media server s not online the media list manager will not load the lists
                // so we tell him now to do so...
                for (auto pair : getManagerEngineer()->getDeviceManager()->getMediaRenderers())
                {
                    if (std::dynamic_pointer_cast<Devices::MediaRenderer_RaumfeldVirtual>(pair.second))
                        getManagerEngineer()->getMediaListManager()->loadMediaItemListByZoneUDN(pair.first);
                }
            }
            catch (...)
            {
                logError("Error while updateing zone lists on media server appearance!", CURRENT_POSITION);
            }

            getManagerEngineer()->getDeviceManager()->unlockDeviceList();
            getManagerEngineer()->getZoneManager()->unlockLists();


            isOnline = true;
            sigRaumfeldSystemOnline.fire();
        }
    }


    void Raumkernel::onMediaServerRemoved(std::shared_ptr<Devices::MediaServer> _mediaServer)
    {
        // if the raumfeld media server was removed, we have to stop the zone configuration request
        if (_mediaServer->isRaumfeldMediaServer())
        {
            managerEngineer->getZoneManager()->stopZoneRequests(); 
            managerEngineer->getMediaListManager()->setMediaServer(nullptr);                     
            isOnline = false;
            sigRaumfeldSystemOffline.fire();
        }
    
    }


    bool Raumkernel::isRaumfeldSystemOnline()
    {
        return isOnline;
    }

    void Raumkernel::onLog(Log::LogData _logData)
    {
        sigLog.fire(_logData);
    }


    VersionInfo::VersionInfo Raumkernel::getVersionInfo()
    {
        return versionInfo;
    }


}