
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
        }


        ZoneManager::~ZoneManager()
        {
            stopZoneRequests();
        }

        void ZoneManager::init()
        {  
            startZoneRequests();
        }    


        void ZoneManager::stopZoneRequests()
        {
            httpClient.killAllRequests();
        }


        void ZoneManager::startZoneRequests()
        {
            doGetZoneRequest();
        }


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

            doGetZoneRequest(updateId);
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
