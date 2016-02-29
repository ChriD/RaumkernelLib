
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
        }


        void MediaListManager::init()
        {
        }


        void MediaListManager::setMediaServer(std::shared_ptr<Devices::MediaServer_Raumfeld> _mediaServer)
        {
            // lock all list actions because the media server has been changed
            std::unique_lock<std::mutex> lock(mutexMapAccess);

            mediaServer = _mediaServer;
            // TODO: clear all lists due media server has changed or was lost
            
            // add connections to the media server to know when a browse or a search is done
            connections.connect(mediaServer->sigBrowseExecuted, this, &MediaListManager::onMediaServerBrowseExecuted);
            connections.connect(mediaServer->sigSearchExecuted, this, &MediaListManager::onMediaServerSearchExecuted);           
        }

            	
        void MediaListManager::getMediaItemListsByContainerUpdateIds(std::string _containerUpdateIds)
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
                        this->getMediaItemListByContainerId(containerUpdateId, "", listId);
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

        
        void MediaListManager::getMediaItemListByZoneUDN(std::string _zoneUDN)
        {
            std::string zoneUDN = Tools::CommonUtil::formatUDN(_zoneUDN);
            std::string containerId = "", listId = LISTID_ZONEIDENTIFIER + zoneUDN;
            //std::shared_ptr<Devices::MediaRenderer_RaumfeldVirtual> mediaRenderer;
            std::shared_ptr<Devices::MediaRenderer> mediaRenderer;

            try
            {
                // we will only get the the lists of virtual media renderers due they combine all other renderers
                // the zoneUDN is the same UDN as the virtual Media Renderer has
                mediaRenderer = getManagerEngineer()->getDeviceManager()->getMediaRenderer(zoneUDN);
                if (mediaRenderer)
                {
                    containerId = mediaRenderer->state().containerId;
                    // if there is an container id we have to reload the list with the container id
                    if (!containerId.empty())
                    {
                        this->getMediaItemListByContainerId(containerId, "", listId);
                    }
                    // if there is no container fiven on the current renderer there is only one item in the list
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


        void MediaListManager::getMediaItemListByContainerId(std::string _containerId, std::string _searchCriteria, std::string _listId)
        {
            // do nothing if we have no media server reference, but give a warning
            if (!mediaServer)
            {
                logWarning("Trying to get list from mediaServer without media server object!", CURRENT_POSITION);
                return;
            }
           
            logDebug("Get MediaList: " + _listId + "  for container: " + _containerId, CURRENT_POSITION);
           
            // if we have specified no list id we create some
            if (_listId.empty())            
                _listId = _containerId + (_searchCriteria.empty() == true ? "" : (":" + _searchCriteria));                 

            if (!_searchCriteria.empty())
            {
                mediaServer->search(_containerId, _searchCriteria, "listId=" + _listId);
            }
            else
            {
                mediaServer->browse(_containerId, Devices::MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, "listId=" + _listId);
            }

        }



        void MediaListManager::onMediaServerBrowseExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData)
        {
            // TODO: @@@
            //this->CreateListFromResultXML(_result, _extraData);
        }


        void MediaListManager::onMediaServerSearchExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData)
        {
            // TODO: @@@
            //this->CreateListFromResultXML(_result, _extraData);
        }
        

    }
}