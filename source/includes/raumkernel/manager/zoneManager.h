//
// The MIT License (MIT)
//
// Copyright (c) 2016 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_ZONEMANAGER_H
#define RAUMKERNEL_ZONEMANAGER_H

#include <atomic>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <list>

#include <raumkernel/manager/managerBase.h>
#include <raumkernel/httpclient/httpClient.h>
#include <raumkernel/xml/rapidxml.hpp>

namespace Raumkernel
{
    namespace Manager
    {

        /**
        * Structure for the general room information
        */
        struct RoomInformation
        {
            std::string UDN;
            std::string zoneUDN;
            std::string name;
            std::string color;
            // there may be more than one renderer attached to the room, so we use a list for storing the rendererUDN's
            std::list<std::string> rendererUDN;
            // a room should be normaly online, but there may be the case that we do a "hard shut off" of the renderers
            // attached to a room and so the room may be mentioned in the zone (also in the zone request from the RF System)
            // but it is not  online
            bool isOnline;
        };


        /**
        * Structure for the general zone information
        */
        struct ZoneInformation
        {
            std::string UDN;
            std::string name;
            // a zone may consist of several rooms which room udns will be stored here
            std::list<std::string> roomsUDN;
        };



        class ZoneManager : public ManagerBase
        {
            public:
                EXPORT ZoneManager();
                EXPORT virtual ~ZoneManager();

                /**
                * Init of the Zone Manager
                * This will start the long polloing of the zone configuration!
                */
                EXPORT void init();
                /**
                * Puts the room with the given roomUDN in the zone with the zoneUDN
                * zoneUDN: The udn of the zone to connect the room to. If zone udn is empty, a new zone is created
                * roomUDN: The udn of the room that has to be put into that zone.If empty, all available rooms(rooms that have active renderers) are put into the zone.
                */              
                EXPORT void connectRoomToZone(const std::string &_roomUDN, const std::string &_zoneUDN);
                /**
                * Puts the room with the given roomUDN's in the zone with the zoneUDN
                * zoneUDN: The udn of the zone to connect the room to. If zone udn is empty, a new zone is created
                * roomUDN: The udn of the room that has to be put into that zone.If empty, all available rooms(rooms that have active renderers) are put into the zone.
                */
                EXPORT void connectRoomsToZone(std::vector<std::string> _roomUDNs, const std::string &_zoneUDN);
                /**
                * Drops a room from the zone it is in
                * If the given room is not in a zone, nothing will happen
                */
                EXPORT void dropRoom(const std::string &_roomUDN);
                /**
                * creates a zone from a roomUDN no matter if the room is in a zone
                * if the room is in a zone it will be dropped from the zone
                */
                EXPORT void createZoneFromRoom(const std::string &_roomUDN);
                /**
                * creates a zone from given roomIds no matter if the rooms are in a zone
                * if a room is in a zone it will be dropped from the zone
                */
                EXPORT void createZoneFromRooms(std::vector<std::string> _roomUDNs);
                /**
                * kills the zone configuration request
                */
                EXPORT void stopZoneRequests();
                /**
                * starts the zone configuration request
                */
                EXPORT void startZoneRequests();
                /**
                * Returns the information if a room is currently online
                */
                EXPORT bool isRoomOnline(const std::string &_roomUDN);
                /**
                * set the 'online' var on the room information           
                */
                EXPORT void setRoomOnline(const std::string &_roomUDN, bool _isOnline = true);
                /**
                * set the 'online' var on the room information which contains the given rendererUDN
                */
                EXPORT void setRoomOnlineForRenderer(const std::string &_rendererUDN, bool _isOnline = true);
                /**
                * returns a roomUDN for a rendereUDN if the renderer is in a room
                */
                EXPORT std::string getRoomUDNFromRendererUDN(const std::string &_rendererUDN);
                /**
                * returns the zoneUDN where the Renderer is in.
                * If the zone UDN is empty the renderer is not in a zone or it doesnt exists (use "existsRoomUDN" to check if its exists)
                */
                EXPORT std::string getZoneUDNForRoomUDN(const std::string &_roomUDN);
                /**
                * returns the roomUDN for a room name.
                * returns an empty string if roomName is not found in roomInformationMap
                */
                EXPORT std::string getRoomUDNForRoomName(const std::string &_roomName);
                /**
                * returns the virtual renderreUDN for the zone
                * returns an empyt string if the zoneUDN is not found
                */
                EXPORT std::string getRendererUDNForZoneUDN(const std::string &_zoneUDN);
                /**
                * returns true if the room with the given UDN is found in the map
                */
                EXPORT bool existsRoomUDN(const  std::string &_roomUDN);
                /**
                * returns true if the zone with the given UDN is found in the map
                */
                EXPORT bool existsZoneUDN(const  std::string &_roomUDN);
                /**
                * returns true if the room is in the givem zone
                */
                EXPORT bool isRoomInZone(const std::string &_roomUDN, const std::string &_zoneUDN);
                /**
                * returns a copy of the zone information map
                */
                EXPORT std::unordered_map<std::string, Manager::ZoneInformation> getZoneInformationMap();
                /**
                * returns a copy of the room information map
                */
                EXPORT std::unordered_map<std::string, Manager::RoomInformation> getRoomInformationMap();
           

                /**
                * this signal will be fired if the zone configuration changes
                * this signal is in the mutex lock of 'mutexMapAccess' and so acces to the maps is the callback is okay                
                */
                sigs::signal<void()> sigZoneConfigurationChanged;

            protected:
                /**
                * The callback method which will be called when the 'getZones' request is finished
                */
                void zoneRequestFinished(HttpClient::HttpRequest *_request);
                /**
                * The callback method which will be called when the 'connectRoomToZone' request is finished
                */
                void connectRoomToZoneFinished(HttpClient::HttpRequest *_request);
                /**
                * The callback method which will be called when the 'connectRoomsToZone' request is finished
                */
                void connectRoomsToZoneFinished(HttpClient::HttpRequest *_request);
                /**
                * The callback method which will be called when the 'dropRoom' request is finished
                */
                void dropRoomFinished(HttpClient::HttpRequest *_request);
                /**
                * Does the request to get the zone information given by the raumfeld system
                * the '_updateId' parameter is usd for longPolling
                */
                void doGetZoneRequest(const std::string &_updateId = "");
                /**
                * Returns the requestUrl for zone requests
                */
                std::string getZoneRequestUrl();
                /**
                * parses the room xml none for the given zones and adds them to the room map
                */
                void addRoomInformationFromXmlNode(rapidxml::xml_node<>* _parentNode, ZoneInformation *_zoneInformation = nullptr);
                /**
                * parses the zone xml none for the given zones and adds them to the map
                */
                void addZoneInformationFromXmlNode(rapidxml::xml_node<>* _parentNode);
                /**
                * parses the zone xml string and fill the 'zoneInformationMap' and 'roomInformationMap'
                */
                void parseZoneConfiguration(const std::string &_zonesXML, const std::string &_updateId);
                /**
                * clears the zoneInformation map
                */
                void clearZoneInformationMap();
                /**
                * clears the room information map
                */
                void clearRoomInformationMap();
                /**
                * clears the maps
                */
                void clearMaps();

                /**
                * The HTTPClient for requesting the zones in a 'long polling' style and for other zone actions
                */
                HttpClient::HttpClient httpClient;
                /**
                * A mutex for the getZoneRequest
                */
                std::mutex mutexStartRequest;
                /**
                * A mutex for the getZoneRequest
                */
                std::mutex mutexMapAccess;

                /**                
                * A map which stores all the available zones and the info for the zone
                * if there is an entry which key is empty, then this zone is not  really created. It's a dummy
                * zone for all roooms which are not assigned to a zone
                */
                std::unordered_map<std::string, Manager::ZoneInformation> zoneInformationMap;
                /**
                * A map which contains all rooms with their general room information
                * All rooms are listed in this map no matter if assigned or not assigned
                */
                std::unordered_map<std::string, Manager::RoomInformation> roomInformationMap;

                /**
                * stores the last zone configuration retrieved by the request
                */
                std::string lastZoneConfigurationXML;
                /**
                * stores the last upadteId for long polling issues
                */
                std::string lastUpdateId;

        };
    }
}


#endif