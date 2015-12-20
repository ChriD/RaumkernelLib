
#include <raumkernel/raumkernel.h>

namespace Raumkernel
{

    Raumkernel::Raumkernel() : RaumkernelBase()
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
            // the log levele itself will be set after reading the settings file but we want to have logginf while reading settings file
            // so we create the logObject with some standard values
            logObject = std::shared_ptr<Log::Log>(new Log::Log());            
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_Console()));
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_File()));
            logObject->setLogLevel(Log::LogType::LOGTYPE_ERROR);
        }

        // TODO: create the settings object (if not already provided)

        // TODO: get settings from ini file or xml settings file?

        // TODO: update log settings after reading the raumkernel settings

    }

}