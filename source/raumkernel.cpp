
#include <raumkernel/raumkernel.h>
#include <raumkernel/manager/managerengineer.h>

namespace Raumkernel
{

    Raumkernel::Raumkernel() : RaumkernelBaseMgr()
    {
    }


    Raumkernel::~Raumkernel()
    {
    }


    void Raumkernel::init()
    {
        // create the log object (if not already provided) which will be used throughout the whole kernel and his modules 
        if (logObject == nullptr)
        {
            // we do register some log adapters for the log object with standard values and set to log only ERRORS and CRITICALERRORS
            // the log level itself will be set after reading the settings file but we want to have logging while reading settings file
            // so we create the logObject with some standard values
            logObject = std::shared_ptr<Log::Log>(new Log::Log());            
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_Console()));
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_File()));
            logObject->setLogLevel(Log::LogType::LOGTYPE_ERROR);
        }

        // create the manager engineer which will hold references to all managers. this engineer will be present in each manager and each class
        // which is inherited from 'RaumfeldBaseMgr', but has to be set explicit
        managerEngineer = std::shared_ptr<Manager::ManagerEngineer>(new Manager::ManagerEngineer());
        managerEngineer->setLogObject(logObject);
        managerEngineer->createManagers();

        // all managers are now created and we can work with them. so first lets get the settings manager in action and let it read our kernel 
        // and application settings


        // TODO: get settings from ini file or xml settings file?

        // TODO: update log settings after reading the raumkernel settings

    }

}