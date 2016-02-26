//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
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
#ifndef RAUMKERNEL_MEDIALISTMANAGER_H
#define RAUMKERNEL_MEDIALISTMANAGER_H

#include <raumkernel/manager/managerBase.h>
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/device/deviceMediaServer_RF.h>

namespace Raumkernel
{
    namespace Manager
    {

        const std::string CONTAINERUPDATEID_ZONEIDENTIFIER = "0/Zones/";
        
        const std::string LISTID_ZONEIDENTIFIER = "ztl:";
        const std::string LISTID_PLAYLISTIDENTIFIER = "pls:";
        const std::string LISTID_FAVOURITEIDENTIFIER = "fav:";
        const std::string LISTID_LASTPLAYEDIDENTIFIER = "lpl:";

        /**
        * The MediaList-Manager
        *
        * This class handles all the lists we are retrieveing from the media server. That means it contains/chaches playlists and zone list,...
        */
        class MediaListManager : public ManagerBase
        {
            public:
                MediaListManager();
                virtual ~MediaListManager();

                virtual void init();
                /**
                * this method is used to set the media server link the mediaServerList manager should use for retrieving the data
                */
                virtual void setMediaServer(std::shared_ptr<Devices::MediaServer_Raumfeld> _mediaServer);
                
                /**
                * will retrieve the list for the given containerId
                */
                EXPORT void getMediaItemListByContainerId(std::string _containerId, std::string _searchCriteria = "", std::string _listId = "");                
                /**
                * will retrieve the list for the given zoneUDN
                */
                EXPORT void getMediaItemListByZoneUDN(std::string _zoneUDN);
                /**
                * will retrieve the list for the given container updateIds
                * a container updateId will look soemthing like thid: "0/Zones/uuid%3Ad225b9e5-6787-4421-b776-e31b142591ef,42571234"
                */
                EXPORT void getMediaItemListsByContainerUpdateIds(std::string _containerUpdateIds);

                /**
                * this signal will be fired if any list has been updated
                * this signal is in the mutex lock of 'mutexMapAccess' and so acces to the maps is the callback is okay
                */
                sigs::signal<void(std::string)> sigListDataChanged;

            protected:
                /**
                * A mutex for locking the lists
                */
                std::mutex mutexMapAccess;
                /**
                * a raumfeld media server reference which we will use to get the data from 
                */
                std::shared_ptr<Devices::MediaServer_Raumfeld> mediaServer;
                /**
                * connection for signals
                */
                sigs::connections connections;
                /**
                * a map which contains all cached and selected lists
                * the key may consists od an identifier and a listId. eg. zpls:[zoneUDN] or pls:[playlistID]
                */
                //std::unordered_map<std::string, std::vector<MediaItem>>;


                void onMediaServerBrowseExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData);
                void onMediaServerSearchExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData);

        };
    }
}


#endif