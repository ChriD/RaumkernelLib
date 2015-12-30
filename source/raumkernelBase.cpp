
#include <raumkernel/raumkernelBase.h>

namespace Raumkernel
{
    RaumkernelBase::RaumkernelBase()
    {
        logObject = nullptr;
    }


    RaumkernelBase::~RaumkernelBase()
    {
    }


    void RaumkernelBase::setLogObject(std::shared_ptr<Log::Log> _logObject)
    {
        logObject = _logObject;
    }


    std::shared_ptr<Log::Log> RaumkernelBase::getLogObject()
    {
        return logObject;
    }


    void RaumkernelBase::logDebug(std::string _log, std::string _location)
    {
        if (logObject == nullptr)
            return;
        logObject->debug(_log, _location);
    }


    void RaumkernelBase::logWarning(std::string _log, std::string _location)
    {
        if (logObject == nullptr)
            return;
        logObject->warning(_log, _location);
    }


    void RaumkernelBase::logInfo(std::string _log, std::string _location)
    {
        if (logObject == nullptr)
            return;
        logObject->info(_log, _location);
    }


    void RaumkernelBase::logError(std::string _log, std::string _location)
    {
        if (logObject == nullptr)
            return;
        logObject->error(_log, _location);
    }


    void RaumkernelBase::logCritical(std::string _log, std::string _location)
    {
        if (logObject == nullptr)
            return;
        logObject->critical(_log, _location);
    }
}