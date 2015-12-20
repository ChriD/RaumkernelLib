
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
        // create the log object which will be used throughout the whole kernel and his modules
        logObject = std::shared_ptr<Log::Log>(new Log::Log());

        // we do register some log adapters for the log object with standard values 
        logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_Console()));
        logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_File()));

    }

}