
#include <raumkernel/logger/logger.h>


namespace Raumkernel
{
    namespace Log
    {
        Log::Log()
        {
            // as standard value we set the log level to 'LOGDEBUG'
            logTypeLevel = LogType::LOGTYPE_DEBUG;         
        }

        
        Log::~Log()
        {
        }


        // We pass the logAdapter shared_ptr per value. This code is non performance relevant and therfore we do not need to pass it by reference
        // (but of course this would be ok in this case because "pushing back" to the vector would create a copy again and  so the usage count would 
        // never fall down to 0 and we keep the vector elements alive as long as the class is existent!)
        void Log::registerAdapter(std::shared_ptr<LogAdapter> _logAdapter)
        {
            logAdapterList.push_back(_logAdapter);
        }


        void Log::debug(std::string _log)
        {
            addLog(LogType::LOGTYPE_DEBUG, _log);
        }


        void Log::warning(std::string _log)
        {
            addLog(LogType::LOGTYPE_WARNING, _log);
        }


        void Log::info(std::string _log)
        {
            addLog(LogType::LOGTYPE_INFO, _log);
        }


        void Log::error(std::string _log)
        {
            addLog(LogType::LOGTYPE_ERROR, _log);
        }


        void Log::critical(std::string _log)
        {
            addLog(LogType::LOGTYPE_CRITICALERROR, _log);
        }


        void Log::addLog(LogType _logType, std::string _log)
        {
            // check log level of log so we can decide if we should log or not
            if (_logType > logTypeLevel)
                return;

            mutexLog.lock();  

            // fill log data struct with the available log data and the current timestamp
            // this struct is used by the adapters and as parameter for signal subsribers
            LogData logData;
            logData.type = _logType;
            logData.log  = _log;
            logData.logDateTimeStamp = Raumkernel::Tools::DateUtil::getCurrentDateTimeStamp();

            // run through all defined adapters (shared pointers) and call 'log' on them 
            // we will not catch any critical errors here, this has to be done by the adapter if necessary!
            for (auto it = logAdapterList.begin(); it != logAdapterList.end(); it++)
            {
                it->get()->log(logData);
            }      
            
            mutexLog.unlock();

            // after we have release the lock we can signal attached subscribers
            // we do not want the subscriber to be in the same mutex lock. The subscriber should handle this by himself            
            sigLog.fire(logData);
        }      

    }
}