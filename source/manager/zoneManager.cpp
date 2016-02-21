
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
            httpClient.setLogObject(getLogObject());
            httpClient.setManagerEngineer(getManagerEngineer());
            httpClient.init();
        }    


        void ZoneManager::stopZoneRequests()
        {    
            logDebug("Killing all requests of zone manager!", CURRENT_POSITION);
            httpClient.abortAllRequests();            
        }


        void ZoneManager::startZoneRequests()
        {           
            logDebug("Staring all automatic requests of zone manager!", CURRENT_POSITION);
            doGetZoneRequest();
        }

        std::string ZoneManager::getZoneRequestUrl()
        {
            std::string hostIP = getManagerEngineer()->getDeviceManager()->getRaumfeldHostIP();
            std::string hostPort = getManagerEngineer()->getSettingsManager()->getValue(SETTINGS_RAUMKERNEL_HOSTREQUESTPORT);
            if (hostIP.empty() || hostPort.empty())
                return "";
            return "http://" + hostIP + ":" + hostPort;
        }
        

        void ZoneManager::doGetZoneRequest(std::string _updateId)
        {
            std::unique_lock<std::mutex> lock(mutexStartRequest);

            std::shared_ptr<std::unordered_map<std::string, std::string>> headerVars = nullptr;
            std::string hostIP = getManagerEngineer()->getDeviceManager()->getRaumfeldHostIP();
            std::string hostPort = getManagerEngineer()->getSettingsManager()->getValue(SETTINGS_RAUMKERNEL_HOSTREQUESTPORT);
            if (!hostIP.empty())
            {
                logDebug("Get zone configuration with updateId: " + _updateId, CURRENT_POSITION);

                if (!_updateId.empty())
                {
                    headerVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);
                    headerVars->insert(std::make_pair("updateid", _updateId));
                }
                httpClient.request(getZoneRequestUrl() + "/getZones", headerVars, nullptr, nullptr, std::bind(&ZoneManager::zoneRequestFinished, this, std::placeholders::_1));
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

            // we have now parsed the zone xml, so we may now call the long pollong request again (we have to use the 
            // updateId to make the request be a long polling request)
            doGetZoneRequest(updateId);            
        }


        void ZoneManager::connectRoomToZone(std::string _roomUDN, std::string _zoneUDN)
        {
            // if the request url is empty we can not do anything
            if (getZoneRequestUrl().empty())
            {
                logError("Trying to connect room to zone without host-IP", CURRENT_POSITION);
                return;
            }
            logDebug("Connect room '" + _roomUDN + "' to zone  '" + _zoneUDN + "'", CURRENT_POSITION);

            // add the roomUDN and zoneUDN as posting parameters            
            auto postVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);
            postVars->insert(std::make_pair("zoneUDN", _zoneUDN));
            postVars->insert(std::make_pair("roomUDN", _roomUDN));

            // call the request for adding a room to a zone. We do attach a Callback when the requets is finished
            // but in fact there is no need for the callback because the "zoneChanged" long polling request will
            // be responsing if a room is added to a zone         
            httpClient.request(getZoneRequestUrl() + "/connectRoomToZone", nullptr, postVars, nullptr, std::bind(&ZoneManager::connectRoomToZoneFinished, this, std::placeholders::_1));
        }


        void ZoneManager::connectRoomToZoneFinished(HttpClient::HttpRequest *_request)
        {
            logDebug("Connect room to zone request finished", CURRENT_POSITION);
        }


        void ZoneManager::connectRoomsToZone(std::vector<std::string> _roomUDNs, std::string _zoneUDN)
        {
            // if the request url is empty we can not do anything
            if (getZoneRequestUrl().empty())
            {
                logError("Trying to connect rooms to zone without host-IP", CURRENT_POSITION);
                return;
            }

            // the roomUDNs have to be comma separated for the post parameter
            std::string roomUDNs;
            for (auto roomUDN : _roomUDNs)
            {
                roomUDNs += roomUDNs.empty() ? "" : ",";
                roomUDNs += roomUDN;
            }

            logDebug("Connect rooms '" + roomUDNs + "' to zone  '" + _zoneUDN + "'", CURRENT_POSITION);

            // add the roomUDN and zoneUDN as posting parameters            
            auto postVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);
            postVars->insert(std::make_pair("zoneUDN", _zoneUDN));
            postVars->insert(std::make_pair("roomUDN", roomUDNs));

            // call the request for adding a room to a zone. We do attach a Callback when the requets is finished
            // but in fact there is no need for the callback because the "zoneChanged" long polling request will
            // be responsing if a room is added to a zone         
            httpClient.request(getZoneRequestUrl() + "/connectRoomToZone", nullptr, postVars, nullptr, std::bind(&ZoneManager::connectRoomsToZoneFinished, this, std::placeholders::_1));
        }


        void ZoneManager::connectRoomsToZoneFinished(HttpClient::HttpRequest *_request)
        {
            logDebug("Connect rooms to zone request finished", CURRENT_POSITION);
        }


        void ZoneManager::dropRoom(std::string _roomUDN)
        {
            // if the request url is empty we can not do anything
            if (getZoneRequestUrl().empty())
            {
                logError("Trying to drop room from zone without host-IP", CURRENT_POSITION);
                return;
            }
            logDebug("Drop room '" + _roomUDN + "' from zone", CURRENT_POSITION);

            auto postVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>);            
            postVars->insert(std::make_pair("roomUDN", _roomUDN));

            // call the request for dropping a room from a zone. We do attach a Callback when the requets is finished
            // but in fact there is no need for the callback because the "zoneChanged" long polling request will
            // be responsing if a room is added to a zone       
            httpClient.request(getZoneRequestUrl() + "/dropRoomJob", nullptr, postVars, nullptr, std::bind(&ZoneManager::dropRoomFinished, this, std::placeholders::_1));
        }


        void ZoneManager::dropRoomFinished(HttpClient::HttpRequest *_request)
        {
            logDebug("Drop room request finished", CURRENT_POSITION);
        }


        void ZoneManager::createZoneFromRoom(std::string _roomUDN)
        {
            logDebug("Create zone from room '" + _roomUDN  + "'", CURRENT_POSITION);
            // when we want to creat a new zone from a room we havce to provide a emoty zone value
            connectRoomToZone(_roomUDN, "");
        }


        void ZoneManager::createZoneFromRooms(std::vector<std::string> _roomUDNs)
        {
            // only for debug information
            std::string roomUDNs;
            for (auto roomUDN : _roomUDNs)
            {
                roomUDNs += roomUDNs.empty() ? "" : ",";
                roomUDNs += roomUDN;
            }

            logDebug("Create zone from rooms '" + roomUDNs + "'", CURRENT_POSITION);
            // when we want to creat a new zone from a room we havce to provide a emoty zone value
            connectRoomsToZone(_roomUDNs, "");
        }

    }
}
