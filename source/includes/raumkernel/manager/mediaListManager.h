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
#include <raumkernel/media/item/mediaItems.h>

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
                EXPORT void loadMediaItemListByContainerId(const std::string &_containerId, const std::string &_searchCriteria = "", const std::string &_listId = "");
                /**
                * will retrieve the list for the given zoneUDN
                */
                EXPORT void loadMediaItemListByZoneUDN(const std::string &_zoneUDN);
                /**
                * will retrieve the list for the given container updateIds
                * a container updateId will look soemthing like this: "0/Zones/uuid%3Ad225b9e5-6787-4421-b776-e31b142591ef,42571234"
                */
                EXPORT void loadMediaItemListsByContainerUpdateIds(const std::string &_containerUpdateIds);
                /**
                * will return a list from the cache                
                */
                EXPORT std::vector<std::shared_ptr<Media::Item::MediaItem>> getList(const std::string &_listId);
                /**
                * will return the last update id for a list
                */
                EXPORT std::string getLastUpdateIdForList(std::string _listId);

                EXPORT void lockLists();
                EXPORT void unlockLists();

                /**
                * this signal will be fired if any list has been updated                
                */
                sigs::signal<void(std::string)> sigMediaListDataChanged;

            protected:

                void onMediaServerBrowseExecuted(const std::string &_result, const std::uint32_t &_numberReturned, const std::uint32_t &_totalMatches, const std::uint32_t &_updateId, const std::string &_extraData);
                void onMediaServerSearchExecuted(const std::string &_result, const std::uint32_t &_numberReturned, const std::uint32_t &_totalMatches, const std::uint32_t &_updateId, const std::string &_extraData);
                void createListFromResultXML(const std::string &_resultXML, const std::string &_extraData);
                void createEmptyList(const std::string &_listId);
                void listChanged(const std::string &_listId);
                void setLastUpdateIdForList(const std::string &_listId);
                std::string generateNewUpdateId(const std::string &_oldId = "");
                                          
                /**
                * a raumfeld media server reference which we will use to get the data from 
                */
                std::shared_ptr<Devices::MediaServer_Raumfeld> mediaServer;
                /**
                * a map which contains all cached and selected lists
                * the key may consists od an identifier and a listId. eg. zpls:[zoneUDN] or pls:[playlistID]
                */
                std::unordered_map<std::string, std::vector<std::shared_ptr<Media::Item::MediaItem>>> mediaListCache;
                std::mutex mutexMapAccess;
                /**
                * a map which stores the last update ids for a list
                */
                std::unordered_map<std::string, std::string> lastUpdateIds;
                std::mutex mutexlastUpdateIds;
                /**
                * connection for signals
                */
                sigs::connections connections;                                           
        };
    }
}


#endif