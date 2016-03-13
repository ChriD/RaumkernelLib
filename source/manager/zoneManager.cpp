
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
            logDebug("Starting all automatic requests of zone manager!", CURRENT_POSITION);
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

            // parse the given xml   
            if (!_request->getResponse()->getErrorCode())
            {
                logDebug("Zone configuration request finished", CURRENT_POSITION);
                parseZoneConfiguration(_request->getResponse()->getData(), updateId);        
            }
            else
            {
                logError("Zone configuration request finished with Error: " + std::to_string(_request->getResponse()->getErrorCode()), CURRENT_POSITION);
            }

            // we have now parsed the zone xml, so we may now call the long pollong request again (we have to use the 
            // updateId to make the request be a long polling request)
            doGetZoneRequest(updateId);            
        }


        void ZoneManager::connectRoomToZone(std::string _roomUDN, std::string _zoneUDN)
        {
            std::unique_lock<std::mutex> lock(mutexStartRequest);

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
            std::unique_lock<std::mutex> lock(mutexStartRequest);

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
            std::unique_lock<std::mutex> lock(mutexStartRequest);

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


        void ZoneManager::addRoomInformationFromXmlNode(rapidxml::xml_node<>* _parentNode, ZoneInformation *_zoneInformation)
        {
            rapidxml::xml_node<> *roomNode, *rendererNode;
            rapidxml::xml_attribute<> *attribute;
            std::string roomColor = "", roomUDN = "", roomName = "", rendererUDN = "";

            roomNode = _parentNode->first_node("room", 0, false);
            while (roomNode)
            {
                RoomInformation		roomInfo;
                bool                rendererOnline = false;

                attribute = roomNode->first_attribute("udn", 0, false);
                if (attribute) roomUDN = attribute->value();

                attribute = roomNode->first_attribute("color", 0, false);
                if (attribute) roomColor = attribute->value();

                attribute = roomNode->first_attribute("name", 0, false);
                if (attribute) roomName = attribute->value();

                roomInfo.UDN = roomUDN;
                roomInfo.zoneUDN = "";
                roomInfo.name = roomName;
                roomInfo.color = roomColor;

                rendererNode = roomNode->first_node("renderer", 0, false);
                while (rendererNode)
                {
                    attribute = rendererNode->first_attribute("udn", 0, false);
                    if (attribute) rendererUDN = attribute->value();

                    roomInfo.rendererUDN.push_back(rendererUDN);

                    // at lest one renderer should be online to give the room the state 'online'
                    rendererOnline = getManagerEngineer()->getDeviceManager()->getMediaRenderer(rendererUDN) == nullptr ? rendererOnline || false : true;

                    rendererNode = rendererNode->next_sibling("renderer", 0, false);
                }

                // set room state to "online/offline" if at least one of the renderes of the room is found in device list
                roomInfo.isOnline = rendererOnline;

                if (_zoneInformation)
                {
                    roomInfo.zoneUDN = _zoneInformation->UDN;
                    _zoneInformation->roomsUDN.push_back(roomUDN);
                }

                roomInformationMap.insert(std::make_pair(roomInfo.UDN, roomInfo));                

                roomNode = roomNode->next_sibling("room", 0, false);
            }
        }

        void ZoneManager::addZoneInformationFromXmlNode(rapidxml::xml_node<>* _parentNode)
        {
            rapidxml::xml_node<> *zoneNode;
            rapidxml::xml_attribute<> *attribute;
            std::string zoneUDN, zoneName;

            zoneNode = _parentNode->first_node("zone", 0, false);
            while (zoneNode)
            {
                ZoneInformation		zoneInfo;
                zoneName = "";

                attribute = zoneNode->first_attribute("udn", 0, false);
                if (attribute) zoneUDN = attribute->value();

                zoneInfo.UDN = zoneUDN;

                addRoomInformationFromXmlNode(zoneNode, &zoneInfo);

                // create name for zone
                for (auto &roomUdn : zoneInfo.roomsUDN)
                {
                    RoomInformation roomInfo = roomInformationMap.at(roomUdn);
                    if (!zoneName.empty())
                        zoneName += ", ";
                    zoneName += roomInfo.name;
                }

                zoneInfo.name = zoneName;

                zoneInformationMap.insert(std::make_pair(zoneInfo.UDN, zoneInfo));

                zoneNode = zoneNode->next_sibling("zone", 0, false);
            }
        }


        void ZoneManager::parseZoneConfiguration(std::string _zonesXML, std::string _updateId)
        {
            rapidxml::xml_document<> doc;
            rapidxml::xml_node<> *zoneConfig, *zones, *unassignedRoomsNode;

            // INFO: this is a little workaround to be sure we do only parse and signal if really something in the configuration has changed
            // i have recognized that changes to the zones will sometimes lead to 2 long polling returns and i don't know why.
            // it may be a problem in the current Raumfeld Firmware or the Kernel may have a bug with the updateId.
            // i have to investigate this 
            if (!lastZoneConfigurationXML.empty() && lastZoneConfigurationXML == _zonesXML)
            {
                logDebug("Zones XML retrieved but no changes found!", CURRENT_POSITION);
                return;
            }

            logDebug("Parsing zone configuration XML", CURRENT_POSITION);  

            lastZoneConfigurationXML = _zonesXML;

            std::unique_lock<std::mutex> lock(mutexMapAccess);    

            try
            {

                // to parse the string we have to put it ino char* (because c_str() returns const char*)
                char* cstr = new char[_zonesXML.size() + 1];
                std::strcpy(cstr, _zonesXML.c_str());
                doc.parse<0>(cstr);

                // remove lists because we do create them here again with the new values (may be more or less items)
                this->clearZoneInformationMap();
                this->clearRoomInformationMap();

                // find the root node which has to be the 'device' node	
                zoneConfig = doc.first_node("zoneConfig", 0, false);
                if (!zoneConfig)
                {
                    logError("Requested zome XML  does not contain 'zoneConfig' block!", __FUNCTION__);
                    return;
                }

                // do zones and rooms in zones
                zones = zoneConfig->first_node("zones", 0, false);
                if (zones)
                {
                    addZoneInformationFromXmlNode(zones);
                }

                // do unassigned rooms
                unassignedRoomsNode = zoneConfig->first_node("unassignedRooms", 0, false);
                if (unassignedRoomsNode)
                {
                    addRoomInformationFromXmlNode(unassignedRoomsNode);
                }

                // store the current update id
                lastUpdateId = _updateId;

                // now the zone configuration has changed, we do fire a signal and we stay in locked scope
                // so acces to the maps while signal is beeing processes id locked and the use of the map in the signal is ok
                sigZoneConfigurationChanged.fire();

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logError("Unknown Exception", CURRENT_FUNCTION);
            }
        }


        void ZoneManager::clearZoneInformationMap()
        {
            zoneInformationMap.clear();
        }


        void ZoneManager::clearRoomInformationMap()
        {
            roomInformationMap.clear();
        }


        void ZoneManager::clearMaps()
        {
            std::unique_lock<std::mutex> lock(mutexMapAccess);           

            clearZoneInformationMap();
            clearRoomInformationMap();        
        }


        bool ZoneManager::isRoomOnline(std::string _roomUDN)
        {
            std::unique_lock<std::mutex> lock(mutexMapAccess);
            if (roomInformationMap.find(_roomUDN) != roomInformationMap.end())
                return roomInformationMap.find(_roomUDN)->second.isOnline;
            return false;
        }


        std::string ZoneManager::getRoomUDNFromRendererUDN(std::string _rendererUDN)
        {
            for (auto &roomInfo : roomInformationMap)
            {                
                auto it = std::find(roomInfo.second.rendererUDN.begin(), roomInfo.second.rendererUDN.end(), _rendererUDN);
                if (it != roomInfo.second.rendererUDN.end())
                    return roomInfo.second.UDN;
            }
            return "";
        }


        void ZoneManager::setRoomOnline(std::string _roomUDN, bool _isOnline)
        {                               
            if (roomInformationMap.find(_roomUDN) != roomInformationMap.end())
                roomInformationMap[_roomUDN].isOnline = _isOnline;
        }


        void ZoneManager::setRoomOnlineForRenderer(std::string _rendererUDN, bool _isOnline)
        {
            std::unique_lock<std::mutex> lock(mutexMapAccess);

            std::string roomUDN = getRoomUDNFromRendererUDN(_rendererUDN);
            if(!roomUDN.empty())
                setRoomOnline(roomUDN, _isOnline);
        }

    }
}
