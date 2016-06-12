
#include <raumkernel/manager/upnpManager.h>
#include <raumkernel/manager/mediaListManager.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/manager/deviceManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        MediaListManager::MediaListManager() : ManagerBase()
        {
        }


        MediaListManager::~MediaListManager()
        {
            logDebug("Destroying MediaList-Manager", CURRENT_POSITION);
        }


        void MediaListManager::init()
        {
        }


        void MediaListManager::lockLists()
        {
            mutexMapAccess.lock();
        }


        void MediaListManager::unlockLists()
        {
            mutexMapAccess.unlock();
        }


        void MediaListManager::setMediaServer(std::shared_ptr<Devices::MediaServer_Raumfeld> _mediaServer)
        {
            lockLists();

            try
            {
                mediaServer = _mediaServer;
                
                // clear all lists due media server has changed or was lost
                mediaListCache.clear();

                // add connections to the media server to know when a browse or a search is done
                connections.disconnect_all();
                connections.connect(mediaServer->sigBrowseExecuted, this, &MediaListManager::onMediaServerBrowseExecuted);
                connections.connect(mediaServer->sigSearchExecuted, this, &MediaListManager::onMediaServerSearchExecuted);
            }
            catch( ... )
            {
                logError("Unknown error!", CURRENT_POSITION);
            }

            unlockLists();
        }


        std::vector<std::shared_ptr<Media::Item::MediaItem>> MediaListManager::getList(const std::string &_listId)
        {
            std::vector<std::shared_ptr<Media::Item::MediaItem>> tmpVector;

            lockLists();

            try
            {
                auto it = mediaListCache.find(_listId);
                if (it != mediaListCache.end())
                {
                    tmpVector = it->second;
                }
            }
            catch (...)
            {
                logError("Unknown error!", CURRENT_POSITION);
            }

            unlockLists();

            return tmpVector;
        }
         

        void MediaListManager::loadMediaItemListsByContainerUpdateIds(const std::string &_containerUpdateIds)
        {
            // a container updateID will look something like this:
            // "0/Zones/uuid%3Ad225b9e5-6787-4421-b776-e31b142591ef,42571234"
            // This is a special one for the zone title/playlist and this means we have to reload the mediaList for the zone title list
            std::string containerUpdateId = "", listId = "";

            logDebug("Container UpdateID's have changed: " + _containerUpdateIds, CURRENT_POSITION);

            try
            {
                auto containerUpdateIdVector = Tools::StringUtil::explodeString(_containerUpdateIds, ",");
                for (auto &containerUpdateId : containerUpdateIdVector)
                {
                    // we only search for zone containers and do update the zone container list, all other lists do not bother us for now
                    // zone containers starts with "0/Zones/" and ends with zoneUDN. The list for the zones are stored with the zone
                    // Identifier constant and the zoneUdn. 
                    if (containerUpdateId.find(CONTAINERUPDATEID_ZONEIDENTIFIER) != std::string::npos)
                    {                       
                        listId = containerUpdateId.substr(CONTAINERUPDATEID_ZONEIDENTIFIER.length(), containerUpdateId.length() - CONTAINERUPDATEID_ZONEIDENTIFIER.length());
                        listId = LISTID_ZONEIDENTIFIER + Tools::UriUtil::unescape(listId);                 
                        logDebug("Zone container id was updated for list: " + listId, CURRENT_POSITION);
                        this->loadMediaItemListByContainerId(containerUpdateId, "", listId);
                    }

                    // TODO: we should cover LastPlayed and Favourites list changes here too

                }

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

        
        void MediaListManager::loadMediaItemListByZoneUDN(const std::string &_zoneUDN)
        {
            std::string zoneUDN = Tools::CommonUtil::formatUDN(Tools::UriUtil::unescape(_zoneUDN));
            std::string containerId = "";
            //std::shared_ptr<Devices::MediaRenderer_RaumfeldVirtual> mediaRenderer;
            std::shared_ptr<Devices::MediaRenderer> mediaRenderer;
   
            try
            {

                auto listId = LISTID_ZONEIDENTIFIER + zoneUDN;        
                // we will only get the the lists of virtual media renderers due they combine all other renderers
                // the zoneUDN is the same UDN as the virtual Media Renderer has
                mediaRenderer = getManagerEngineer()->getDeviceManager()->getMediaRenderer(zoneUDN);
                if (mediaRenderer)
                {
                    if (!mediaRenderer->state().containerId.empty())
                        containerId = mediaRenderer->state().containerId;
                    // if there is an container id we have to reload the list with the container id
                    if (!containerId.empty())
                    {
                        this->loadMediaItemListByContainerId(containerId, "", listId);
                    }
                    // if there is no container given on the current renderer there is only one item in the list or its some kind of favorite?e
                    // therfore we can only get the info by getting the media item information on ther renderer itself (because its no list or query) 
                    else
                    {
                        /*
                        // no container? then it means we do have only one item in list! that means the current item on the MediaRenderer is the list!
                        // TODO: @@@
                        this->Lock();

                        std::list<MediaItem> newList;

                        MediaItem mediaItem = mediaRenderer->GetCurrentMediaItem();
                        if (!mediaItem.id.empty())
                        {
                            newList.push_back(mediaItem);

                            auto it = listCache.find(listId);
                            if (it != listCache.end())
                                listCache.erase(listId);
                            listCache.insert(std::make_pair(listId, newList));
                        }

                        this->UnLock();

                        this->ListReady(listId, true);
                        */
                    }
                }

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


        void MediaListManager::loadMediaItemListByContainerId(const std::string &_containerId, const std::string &_searchCriteria, const std::string &_listId)
        {
            // do nothing if we have no media server reference, but give a warning
            if (!mediaServer)
            {
                logWarning("Trying to get list from mediaServer without media server object!", CURRENT_POSITION);
                return;
            }
           
            logDebug("Get MediaList: " + _listId + "  for container: " + _containerId, CURRENT_POSITION);

            if (_containerId.empty() && !_listId.empty())
            {
                createEmptyList(_listId);
                return;
            }
           
            // if we have specified no list id we create some
            std::string listId = _listId;
            if (listId.empty())
                listId = _containerId + (_searchCriteria.empty() == true ? "" : (":" + _searchCriteria));

            if (!_searchCriteria.empty())
            {
                mediaServer->search(_containerId, _searchCriteria, listId);
            }
            else
            {
                mediaServer->browse(_containerId, Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, listId);            
            }

        }


        void MediaListManager::onMediaServerBrowseExecuted(const std::string &_result, const std::uint32_t &_numberReturned, const std::uint32_t &_totalMatches, const std::uint32_t &_updateId, const std::string &_extraData)
        {
            // TODO: @@@
            createListFromResultXML(_result, _extraData);
        }


        void MediaListManager::onMediaServerSearchExecuted(const std::string &_result, const std::uint32_t &_numberReturned, const std::uint32_t &_totalMatches, const std::uint32_t &_updateId, const std::string &_extraData)
        {
            // TODO: @@@
            createListFromResultXML(_result, _extraData);
        }


        void MediaListManager::createEmptyList(const std::string &_listId)
        {
            std::vector<std::shared_ptr<Media::Item::MediaItem>> mediaItemList;

            lockLists();
            try
            {
                mediaListCache.insert(std::make_pair(_listId, mediaItemList));
            }
            catch (...)
            {
                logError("Error while parsing media list result!", CURRENT_POSITION);
            }
            unlockLists();

            sigMediaListDataChanged.fire(_listId);
        }


        void MediaListManager::createListFromResultXML(const std::string &_resultXML, const std::string &_extraData)
        {
            pugi::xml_node rootNode;
            pugi::xml_document doc;
            Media::MediaItemCreator mediaItemCreator;
            std::vector<std::shared_ptr<Media::Item::MediaItem>> mediaItemList;

            lockLists();

            try
            {
              
                pugi::xml_parse_result result = doc.load_string(_resultXML.c_str());

                // find the root node
                rootNode = doc.child("DIDL-Lite");
                if (rootNode)
                {
                    auto containerNodes = rootNode.select_nodes(".//container");
                    for (auto containerNode : containerNodes)
                    {                                                
                        auto mediaItem = mediaItemCreator.createMediaItemFromXMLNode(containerNode.node());
                        mediaItemList.emplace_back(mediaItem);                       
                    }
                    containerNodes = rootNode.select_nodes(".//item");
                    for (auto containerNode : containerNodes)
                    {
                        auto mediaItem = mediaItemCreator.createMediaItemFromXMLNode(containerNode.node());
                        mediaItemList.emplace_back(mediaItem);
                    }
                    mediaListCache.insert(std::make_pair(_extraData, mediaItemList));
                }
                else
                {
                    logError("Media list result doesn not have root (DIDL-Lite) block!", CURRENT_POSITION);
                }                                  
               
            }
            catch ( ... )
            {
                logError("Error while parsing media list result!", CURRENT_POSITION);
            }
            
            unlockLists();          

            sigMediaListDataChanged.fire(_extraData);
        }        
    }
}