
#include <raumkernel/manager/zoneManager.h>
#include <raumkernel/manager/deviceManager.h>
#include <raumkernel/manager/settingsManager.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        ZoneManager::ZoneManager() : ManagerBase()
        {
            //lastZoneRequestUpdateId = "";
            //startZoneRequest = false;
            //stopZoneRequestThread = false;
        }


        ZoneManager::~ZoneManager()
        {
            stopZoneRequests();
        }

        void ZoneManager::init()
        {  
            //startZoneRequests();
        }    


        void ZoneManager::stopZoneRequests()
        {
            //startZoneRequest = false;
            //stopZoneRequestThread = true;
            httpClient.killAllRequests();
        }


        void ZoneManager::startZoneRequests()
        {
            //startZoneRequest = true;
            //stopZoneRequestThread = false;
            //threadZoneRequestStart = std::thread(&ZoneManager::runStartZoneRequestsThread, this);
            doGetZoneRequest();
        }

        /*
        void ZoneManager::runStartZoneRequestsThread()
        {
            while (!stopZoneRequestThread)
            {
                if (startZoneRequest)
                {
                    doGetZoneRequest(lastZoneRequestUpdateId);
                    startZoneRequest = false;           
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        */

        void ZoneManager::doGetZoneRequest(std::string _updateId)
        {
            std::shared_ptr<std::unordered_map<std::string, std::string>> headerVars = nullptr;
            std::string hostIP = getManagerEngineer()->getDeviceManager()->getRaumfeldHostIP();
            std::string hostPort = getManagerEngineer()->getSettingsManager()->getValue(SETTINGS_RAUMKERNEL_HOSTREQUESTPORT);
            if (!hostIP.empty())
            {                           
                if (!_updateId.empty())
                {
                    headerVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);
                    headerVars->insert(std::make_pair("updateid", _updateId));
                }                   
                httpClient.request("http://" + hostIP + ":" + hostPort + "/getZones", headerVars, nullptr, nullptr, std::bind(&ZoneManager::zoneRequestFinished, this, std::placeholders::_1));
            }
        }


        void ZoneManager::zoneRequestFinished(HttpClient::HttpRequest *_request)
        {
            std::shared_ptr<HttpClient::HttpResponse> response = _request->getResponse();
            std::string updateId = response->getHeaderVar("updateId");          

            // TODO: parse XML String
            //lastZoneRequestUpdateId = updateId;

            // TODO: we can not call the long polling request again here directly because this would be some sort of endless reference on the request objects  
            // so we save the update id and afterwards set some atomic bool to signal our zoneUpdate thread that he can do a request again
            doGetZoneRequest(updateId);
            //startZoneRequest = true;
        }

        void ZoneManager::connectRoomToZone(std::string _roomUDN, std::string _zoneUDN)
        {
            // TODO: @@@
        }

        void ZoneManager::dropRoom(std::string _roomUDN)
        {
            // TODO: @@@
        }

    }
}
