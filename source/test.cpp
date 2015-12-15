
#include <raumkernel/logger/logger.h>
#include <raumkernel/rlutil/rlutil.h>



static void testLog(Raumkernel::Log::Log &_logObject)
{
    for (unsigned int i = 0; i <= 200; ++i)
    {
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_CRITICALERROR, "I am a fatal error log! I am a fatal error log! I am a fatal error log");
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_ERROR, "I am a error log! I am a error log! I am a error log! I am a error log!");
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_WARNING, "I am a warning log! I am a warning log! I am a warning log! I am a warning log!");
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_INFO, "I am a info log! I am a info log! I am a info log! I am a info log! I am a info log!");
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_DEBUG, "I am a debug log! I am a debug log! I am a debug log! I am a debug log! I am a debug log!");
    }
}



int main()
{
    std::chrono::steady_clock::time_point timePointStart, timePointEnd;
    std::chrono::milliseconds miliseconds;

    

    // test object and the performance of the logger by writing 1000 log entries to file 
    Raumkernel::Log::Log	logObjectFile; 
    logObjectFile.registerAdapter(std::shared_ptr<Raumkernel::Log::LogAdapter>(new Raumkernel::Log::LogAdapter_File()));
    timePointStart = std::chrono::steady_clock::now();    
    testLog(logObjectFile);
    
    timePointEnd = std::chrono::steady_clock::now();
    miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePointEnd.time_since_epoch() - timePointStart.time_since_epoch());
    std::cout << "Average time to create one log entry [FILE]: " + std::to_string((float)miliseconds.count() / 1000) + "ms";


    rlutil::getkey();

    

    // test object and the performance of the logger by writing 1000 log entries to console 
    Raumkernel::Log::Log	logObjectConsole;
    logObjectConsole.registerAdapter(std::shared_ptr<Raumkernel::Log::LogAdapter>(new Raumkernel::Log::LogAdapter_Console()));
    timePointStart = std::chrono::steady_clock::now();
    testLog(logObjectConsole);
    timePointEnd = std::chrono::steady_clock::now();
    miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePointEnd.time_since_epoch() - timePointStart.time_since_epoch());
    std::cout << "Average time to create one log entry [FILE]: " + std::to_string((float)miliseconds.count() / 1000) + "ms";


    rlutil::getkey();


    // test object and the performance of the logger by writing 1000 log entries to file and console 
    Raumkernel::Log::Log	logObject;
    logObject.registerAdapter(std::shared_ptr<Raumkernel::Log::LogAdapter>(new Raumkernel::Log::LogAdapter_Console()));
    logObject.registerAdapter(std::shared_ptr<Raumkernel::Log::LogAdapter>(new Raumkernel::Log::LogAdapter_File()));
    timePointStart = std::chrono::steady_clock::now();
    testLog(logObject);
    timePointEnd = std::chrono::steady_clock::now();
    miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePointEnd.time_since_epoch() - timePointStart.time_since_epoch());
    std::cout << "Average time to create one log entry [FILE][CONSOLE]: " + std::to_string((float)miliseconds.count() / 1000) + "ms";


    rlutil::getkey();

   
    return 0;
}





