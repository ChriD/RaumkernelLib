
#include <raumkernel/raumkernel.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/httpclient/httpClient.h>
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/rlutil/rlutil.h>


#include <random>
#include <iostream>
#include <functional>


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


void myCallback(Raumkernel::HttpClient::HttpRequest *_request)
{
    
}


/// https://httpbin.org/

int main(int argc, char** argv)
{

    Raumkernel::Raumkernel  raumkernel;

    raumkernel.initLogObject();
    raumkernel.init();

    rlutil::getkey();

   
    auto roomUDN = raumkernel.getManagerEngineer()->getZoneManager()->getRoomUDNForRoomName("Küche");
    //auto roomUDN = raumkernel.getManagerEngineer()->getZoneManager()->getRoomUDNForRoomName("Wohnzimmer");
    //auto rendererUDN = raumkernel.getManagerEngineer()->getZoneManager()->getRendererUDNForRoomUDN(roomUDN);
    auto rendererUDN = raumkernel.getManagerEngineer()->getZoneManager()->getZoneUDNForRoomUDN(roomUDN);
    //auto mediaRenderer = std::dynamic_pointer_cast<Raumkernel::Devices::MediaRenderer_Raumfeld>(raumkernel.getManagerEngineer()->getDeviceManager()->getMediaRenderer(rendererUDN));
    auto mediaRenderer = dynamic_cast<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual*>(raumkernel.getManagerEngineer()->getDeviceManager()->getMediaRenderer(rendererUDN));

    auto name = mediaRenderer->getName();

    rlutil::getkey();

    //raumkernel.getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer()->browse("0/My Music/AllTracks", Raumkernel::Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, "", true);
    raumkernel.getManagerEngineer()->getMediaListManager()->loadMediaItemListByContainerId("0/My Music/AllTracks", "", "TESTID001");
    
    //mediaRenderer->enterManualStandby();

    rlutil::getkey();

    //mediaRenderer->leaveStandby();

    rlutil::getkey();

    /*
     auto UDN = raumkernel.getManagerEngineer()->getZoneManager()->getRoomUDNForRoomName("Wohnzimmer");
     auto ZONEUDN = raumkernel.getManagerEngineer()->getZoneManager()->getZoneUDNForRoomUDN(UDN); 
     auto exists = raumkernel.getManagerEngineer()->getZoneManager()->existsZoneUDN(ZONEUDN);
     auto rendererUDN = raumkernel.getManagerEngineer()->getZoneManager()->getRendererUDNForZoneUDN(ZONEUDN);

     if (!rendererUDN.empty())
     {
         auto mediaRenderer = std::dynamic_pointer_cast<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual>(raumkernel.getManagerEngineer()->getDeviceManager()->getMediaRenderer(rendererUDN));
         mediaRenderer->loadShuffle("0/Playlists/Shuffles/TopArtists", "");
     }
     */

    //Raumkernel::HttpClient::HttpClient client;

    //client.request("http://10.0.0.5:47365/getZones", nullptr, nullptr, "Test User Data", std::bind(&MyClass::Callback, this, _1));
    //client.request("http://10.0.0.5:47365/getZones", nullptr, nullptr, "Test User Data", std::bind(myCallback, std::placeholders::_1));

    //raumkernel.getManagerEngineer()->getRequestManager()->request("http://10.0.0.5:47365/getZones", nullptr, nullptr, "zoneLongPolling");

    //rlutil::getkey();
    
    //std::shared_ptr<Raumkernel::Devices::MediaServer_Raumfeld> mediaServer = raumkernel.getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer();
    //mediaServer->browse("0", Raumkernel::Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, "root", true);
    //mediaServer->browse("0", Raumkernel::Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, "root");

    auto mediaListManager = raumkernel.getManagerEngineer()->getMediaListManager();
    //mediaListManager->loadMediaItemListByContainerId("0/Napster");
    //mediaListManager->loadMediaItemListByContainerId("0/My Music/Artists");
    //mediaListManager->loadMediaItemListByContainerId("0/My Music/Artists/2Raumwohnung");
    mediaListManager->loadMediaItemListByContainerId("0/RadioTime/CategoryMusic/c-c10635888");
    
   
   

    rlutil::getkey();

    /*
    std::shared_ptr<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual> renderer = std::dynamic_pointer_cast<Raumkernel::Devices::MediaRenderer_RaumfeldVirtual>(raumkernel.getManagerEngineer()->getDeviceManager()->getMediaRenderer("uuid:b1b6b57e-5a8f-4286-b7b0-22568beb83f6"));
    renderer->play();
    
    renderer->getMediaInfo();
    renderer->getPositionInfo();
    renderer->getTransportInfo();
    renderer->getTransportSettings();
    */
  

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





