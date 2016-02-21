
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
            httpClient.setLogObject(getLogObject());
            httpClient.setManagerEngineer(getManagerEngineer());
            httpClient.init();
        }    


        void ZoneManager::stopZoneRequests()
        {
            //startZoneRequest = false;
            //stopZoneRequestThread = true;
            logDebug("Killing all requests of zone manager!", CURRENT_POSITION);
//            httpClient.killAllRequests();
            // TODO: Stop long polling request from request manager?!
        }


        void ZoneManager::startZoneRequests()
        {
            //startZoneRequest = true;
            //stopZoneRequestThread = false;
            //threadZoneRequestStart = std::thread(&ZoneManager::runStartZoneRequestsThread, this);
            logDebug("Staring all automatic requests of zone manager!", CURRENT_POSITION);
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
            std::unique_lock<std::mutex> lock(mutexStartRequest);

            std::shared_ptr<std::unordered_map<std::string, std::string>> headerVars = nullptr;
            std::string hostIP = getManagerEngineer()->getDeviceManager()->getRaumfeldHostIP();
            std::string hostPort = getManagerEngineer()->getSettingsManager()->getValue(SETTINGS_RAUMKERNEL_HOSTREQUESTPORT);
            if (!hostIP.empty())
            {
                logDebug("Starting zone configuration request with updateId: " + _updateId, CURRENT_POSITION);

                if (!_updateId.empty())
                {
                    headerVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);
                    headerVars->insert(std::make_pair("updateid", _updateId));
                }
                httpClient.request("http://" + hostIP + ":" + hostPort + "/getZones", headerVars, nullptr, nullptr, std::bind(&ZoneManager::zoneRequestFinished, this, std::placeholders::_1));
            }
            else
            {
                logError("Trying to start zone configuration request without host-IP", CURRENT_POSITION);
            }
        
        }


        void ZoneManager::zoneRequestFinished(HttpClient::HttpRequest *_request)
        {
            std::shared_ptr<HttpClient::HttpResponse> response = _request->getResponse();
            std::string updateId = response->getHeaderVar("updateId");     

            logDebug("Zone configuration request finished", CURRENT_POSITION);

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
