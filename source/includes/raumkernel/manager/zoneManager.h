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

#include <raumkernel/manager/managerBase.h>
#include <raumkernel/httpclient/httpClient.h>

namespace Raumkernel
{
    namespace Manager
    {
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
                EXPORT void connectRoomToZone(std::string _roomUDN, std::string _zoneUDN);
                /**
                * Puts the room with the given roomUDN's in the zone with the zoneUDN
                * zoneUDN: The udn of the zone to connect the room to. If zone udn is empty, a new zone is created
                * roomUDN: The udn of the room that has to be put into that zone.If empty, all available rooms(rooms that have active renderers) are put into the zone.
                */
                EXPORT void connectRoomsToZone(std::vector<std::string> _roomUDNs, std::string _zoneUDN);
                /**
                * Drops a room from the zone it is in
                * If the given room is not in a zone, nothing will happen
                */
                EXPORT void dropRoom(std::string _roomUDN);
                /**
                * creates a zone from a roomUDN no matter if the room is in a zone
                * if the room is in a zone it will be dropped from the zone
                */
                EXPORT void createZoneFromRoom(std::string _roomUDN);
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
                void doGetZoneRequest(std::string _updateId = "");
                /**
                * Returns the requestUrl for zone requests
                */
                std::string getZoneRequestUrl();
                /**
                * The HTTPClient for requesting the zones in a 'long polling' style and for other zone actions
                */
                HttpClient::HttpClient httpClient;
                /**
                * A mutex for the getZoneRequest
                */
                std::mutex mutexStartRequest;

        };
    }
}


#endif