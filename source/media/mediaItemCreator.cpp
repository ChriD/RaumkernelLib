
#include <raumkernel/media/mediaItemCreator.h>

namespace Raumkernel
{
    namespace Media
    {
        MediaItemCreator::MediaItemCreator() : RaumkernelBase()
        {
        }


        MediaItemCreator::~MediaItemCreator()
        {
        }


        std::shared_ptr<Media::Item::MediaItem> MediaItemCreator::createObject(std::string _upnpClass, std::string _name)
        {            
            if (_upnpClass == "object.container")
                return std::shared_ptr<Media::Item::MediaItem_Container>(new Media::Item::MediaItem_Container());
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_Track>(new Media::Item::MediaItem_Track());            
            if (_upnpClass == "object.item.audioItem.audioBroadcast.radio")
                return std::shared_ptr<Media::Item::MediaItem_Radio_RadioTime>(new Media::Item::MediaItem_Radio_RadioTime());
            if (_upnpClass == "object.container.album.musicAlbum")
                return std::shared_ptr<Media::Item::MediaItem_Album>(new Media::Item::MediaItem_Album());
            if (_upnpClass == "object.container.person.musicArtist")
                return std::shared_ptr<Media::Item::MediaItem_Artist>(new Media::Item::MediaItem_Artist());
            if (_upnpClass == "object.container.playlistContainer")
                return std::shared_ptr<Media::Item::MediaItem_Playlist>(new Media::Item::MediaItem_Playlist());


            // TODO: @@@
            if (_upnpClass == "object.container.albumContainer")
                return std::shared_ptr<Media::Item::MediaItem_Container>(new Media::Item::MediaItem_Container());
            if (_upnpClass == "object.container.favoritesContainer")
                return std::shared_ptr<Media::Item::MediaItem_Container>(new Media::Item::MediaItem_Container());            
            if (_upnpClass == "object.container.trackContainer.allTrack")
                return std::shared_ptr<Media::Item::MediaItem_TrackContainer>(new Media::Item::MediaItem_TrackContainer());
                                    

            /*
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_TrackContainer>(new Media::Item::MediaItem_TrackContainer());                       
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_Composer>(new Media::Item::MediaItem_Composer());           
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_Genre>(new Media::Item::MediaItem_Genre());
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_LineIn>(new Media::Item::MediaItem_LineIn());              
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_RhapsodyRadio>(new Media::Item::MediaItem_RhapsodyRadio());
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_Shuffle>(new Media::Item::MediaItem_Shuffle());
            if (_upnpClass == "object.item.audioItem.musicTrack")
                return std::shared_ptr<Media::Item::MediaItem_StorageFolder>(new Media::Item::MediaItem_StorageFolder());
            */

            return std::shared_ptr<Media::Item::MediaItem_Unknown>(new Media::Item::MediaItem_Unknown());
        }


        std::shared_ptr<Item::MediaItem> MediaItemCreator::createMediaItemFromTrackMetadata(std::string _trackMetadata)
        {
            pugi::xml_document doc;
            pugi::xml_node itemNode, containerNode, rootNode;
            std::shared_ptr<Item::MediaItem> mediaItem;

            try
            {

                pugi::xml_parse_result result = doc.load_string(_trackMetadata.c_str());

                // find the root node which has to be the 'DIDL-Lite' node	
                rootNode = doc.child("DIDL-Lite");
                if (!rootNode)
                {
                    logError("TrackMetadata XML is not formated properly! (Missing 'DIDL-Lite' node)", CURRENT_POSITION);
                    return nullptr;
                }            

                // there should be only one item in the trackMetadata XML, but this can be a "container" too
                itemNode = rootNode.child("item");
                containerNode = rootNode.child("container");

                if (!itemNode && !containerNode)
                {
                    logError("TrackMetadata XML is not formated properly! (Missing 'item' or 'container' node)", CURRENT_POSITION);
                    return nullptr;
                }                
            
                // now that we have successfully found the item node we can try to create the mediaItem object 
                if (itemNode)
                    mediaItem = this->createMediaItemFromXMLNode(itemNode);

                // if we found a container node, well, we do nothing for now... we may read the container data maybe we can use the 'createMediaItemFromXMLNode'
                // without any changes?!
                //if (containerNode)
                //    mediaItem = this->createMediaItemFromXMLNode(containerNode);

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
            catch (...)
            {
                logError("Unknown Exception", CURRENT_FUNCTION);
            }

            return mediaItem;
        }


        std::shared_ptr<Item::MediaItem> MediaItemCreator::createMediaItemFromXMLNode(pugi::xml_node _xmlNode)
        {           
            // ATTENTION: Unescaping of values is done because the webserver cant handle % in result value

            pugi::xml_node itemNode = _xmlNode, valueNode;
            pugi::xml_attribute attribute;

            auto raumfeldName = Tools::XMLUtil::getChildNodeVal(itemNode, "raumfeld:name");
            auto upnpClass = Tools::XMLUtil::getChildNodeVal(itemNode, "upnp:class");

            std::shared_ptr<Item::MediaItem> mediaItem = createObject(upnpClass, raumfeldName);
            mediaItem->initFromXMLNode(itemNode);

            return mediaItem;

        }
    }
}