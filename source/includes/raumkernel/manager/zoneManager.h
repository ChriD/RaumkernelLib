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

#include <raumkernel/manager/managerBase.h>

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
                * Drops a room from the zone it is in
                * If the given room is not in a zone, nothing will happen
                */
                EXPORT void dropRoom(std::string _roomUDN);
        };
    }
}


#endif