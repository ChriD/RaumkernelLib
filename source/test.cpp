
#include <raumkernel/raumkernel.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/httpclient/httpClient.h>
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/rlutil/rlutil.h>



static void testLog(Raumkernel::Log::Log &_logObject)
{
    for (unsigned int i = 0; i <= 200; ++i)
    {
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_CRITICALERROR, "I am a fatal error log! I am a fatal error log! I am a fatal error log", CURRENT_FUNCTION);
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_ERROR, "I am a error log! I am a error log! I am a error log! I am a error log!", CURRENT_FUNCTION);
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_WARNING, "I am a warning log! I am a warning log! I am a warning log! I am a warning log!", CURRENT_FUNCTION);
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_INFO, "I am a info log! I am a info log! I am a info log! I am a info log! I am a info log!", CURRENT_FUNCTION);
        _logObject.addLog(Raumkernel::Log::LogType::LOGTYPE_DEBUG, "I am a debug log! I am a debug log! I am a debug log! I am a debug log! I am a debug log!", CURRENT_FUNCTION);
    }
}

/*
void doSomething(std::function<void()> func)
{
    func();
}


void myCallback(int a, int b)
{
}
*/


int main()
{
   // doSomething(std::bind(myCallback, 1, 2));

    /*
    std::chrono::steady_clock::time_point timePointStart, timePointEnd;
    std::chrono::milliseconds miliseconds;

    // test object and the performance of the logger by writing 1000 log entries to file 
    Raumkernel::Log::Log	logObjectFile; 
    logObjectFile.registerAdapter(std::shared_ptr<Raumkernel::Log::LogAdapter>(new Raumkernel::Log::LogAdapter_File()));
    timePointStart = std::chrono::steady_clock::now();    
    testLog(logObjectFile);
    
    timePointEnd = std::chrono::steady_clock::now();
    miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePointEnd.time_since_epoch() - timePointStart.time_since_epoch());
    std::cout << "Average time to create one log entry [FILE]: " + std::to_string((float)miliseconds.count() / 1000) + "ms\n";
    */

    Raumkernel::Raumkernel  raumkernel;

    raumkernel.init(Raumkernel::Log::LogType::LOGTYPE_DEBUG);

    rlutil::getkey();

    Raumkernel::HttpClient::HttpClient client;

    client.test();

    //raumkernel.getManagerEngineer()->getRequestManager()->request("http://10.0.0.5:47365/getZones", nullptr, nullptr, "zoneLongPolling");

    rlutil::getkey();
    
    std::shared_ptr<Raumkernel::Devices::MediaServer_Raumfeld> mediaServer = raumkernel.getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer();
    mediaServer->browse("0", Raumkernel::Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, "root", true);

    rlutil::getkey();

    std::shared_ptr<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual> renderer = std::dynamic_pointer_cast<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual>(raumkernel.getManagerEngineer()->getDeviceManager()->getMediaRenderer("uuid:b1b6b57e-5a8f-4286-b7b0-22568beb83f6"));
    renderer->play();
    
    renderer->getMediaInfo();
    renderer->getPositionInfo();
    renderer->getTransportInfo();
    renderer->getTransportSettings();

    rlutil::getkey();

    renderer->pause();

    rlutil::getkey();

    renderer->play();

    rlutil::getkey();

    renderer->next();

    rlutil::getkey();

    renderer->previous();

    rlutil::getkey();

    renderer->stop();


    rlutil::getkey();
    
    /*
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
    */

   
    return 0;
}





