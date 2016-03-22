
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


    void RaumkernelBase::logDebug(const std::string &_log, const std::string &_location)
    {
        if (logObject == nullptr)
            return;
        logObject->debug(_log, _location);
    }


    void RaumkernelBase::logWarning(const std::string &_log, const std::string &_location)
    {
        if (logObject == nullptr)
            return;
        logObject->warning(_log, _location);
    }


    void RaumkernelBase::logInfo(const std::string &_log, const std::string &_location)
    {
        if (logObject == nullptr)
            return;
        logObject->info(_log, _location);
    }


    void RaumkernelBase::logError(const std::string &_log, const std::string &_location)
    {
        if (logObject == nullptr)
            return;
        logObject->error(_log, _location);
    }


    void RaumkernelBase::logCritical(const std::string &_log, const std::string &_location)
    {
        if (logObject == nullptr)
            return;
        logObject->critical(_log, _location);
    }
}