
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
            // TODO: create object with correct class from "upnp:class"
            // TODO: create better xml parsing with default values like in subscription!

            pugi::xml_node itemNode = _xmlNode, valueNode;
            pugi::xml_attribute attribute;
            std::shared_ptr<Item::MediaItem> mediaItem = std::shared_ptr<Item::MediaItem>(new Item::MediaItem()); // TODO: @@@

            attribute = itemNode.attribute("id");
            if (attribute)
                mediaItem->id = attribute.value();

            attribute = itemNode.attribute("parentID");
            if (attribute)
                mediaItem->parentId = attribute.value();

            valueNode = itemNode.child("raumfeld:name");
            if (valueNode)
                mediaItem->raumfeldName = valueNode.child_value();

            /*
            valueNode = itemNode->first_node("dc:title", 0, false);
            if (valueNode)
                mediaItem->title = valueNode->value();
                */

            valueNode = itemNode.child("upnp:class");
            if (valueNode)
                mediaItem->upnpClass = valueNode.child_value();

            valueNode = itemNode.child("raumfeld:section");
            if (valueNode)
                mediaItem->raumfeldSection = valueNode.child_value();

            valueNode = itemNode.child("res");
            if (valueNode)
            {
                mediaItem->res = valueNode.child_value();
                /*
                attribute = valueNode->first_attribute("duration", 0, false);
                if (attribute)
                    mediaItem->duration = attribute->value();
                    */
            }

            /*
            // ALBUM
            valueNode = itemNode->first_node("upnp:album", 0, false);
            if (valueNode)
                mediaItem.album = valueNode->value();

            valueNode = itemNode->first_node("upnp:albumArtUri", 0, false);
            if (valueNode)
                mediaItem.albumArtUri = valueNode->value();

            // ARTIST
            valueNode = itemNode->first_node("upnp:artist", 0, false);
            if (valueNode)
                mediaItem.artist = valueNode->value();

            valueNode = itemNode->first_node("upnp:artistArtUri", 0, false);
            if (valueNode)
                mediaItem.artistArtUri = valueNode->value();
                */



            return mediaItem;

        }
    }
}