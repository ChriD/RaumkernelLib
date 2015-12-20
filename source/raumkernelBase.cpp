
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
}