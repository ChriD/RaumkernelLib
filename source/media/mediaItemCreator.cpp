
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
            rapidxml::xml_document<> doc;
            rapidxml::xml_node<> *itemNode, *rootNode;
            std::shared_ptr<Item::MediaItem> mediaItem;

            try
            {

                // to parse the string we have to put it into char* (because c_str() returns const char*)
                char* cstr = new char[_trackMetadata.size() + 1];
                strcpy(cstr, _trackMetadata.c_str());
                doc.parse<0>(cstr);

                // find the root node which has to be the 'DIDL-Lite' node	
                rootNode = doc.first_node("DIDL-Lite", 0, false);
                if (!rootNode)
                {
                    logError("TrackMetadata XML is not formated properly! (Missing 'DIDL-Lite' node)", CURRENT_POSITION);
                    return nullptr;
                }

                // there should be only one item in the trackMetadata XML 
                itemNode = rootNode->first_node("item", 0, false);
                if (!itemNode)
                {
                    logError("TrackMetadata XML is not formated properly! (Missing 'Item' node)", CURRENT_POSITION);
                    return nullptr;
                }
             
                // noe that we have successfully found  the item node we can try to create the mediaItem object 
                mediaItem = this->createMediaItemFromXMLNode(itemNode);

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


        std::shared_ptr<Item::MediaItem> MediaItemCreator::createMediaItemFromXMLNode(rapidxml::xml_node<> *_xmlNode)
        {
            // TODO: create object with correct class from "upnp:class"
            // TODO: create better xml parsing with default values like in subscription!

            rapidxml::xml_node<> *itemNode = _xmlNode, *valueNode;
            rapidxml::xml_attribute<> *attribute;
            std::shared_ptr<Item::MediaItem> mediaItem = std::shared_ptr<Item::MediaItem>(new Item::MediaItem()); // TODO: @@@

            attribute = itemNode->first_attribute("id", 0, false);
            if (attribute)
                mediaItem->id = attribute->value();

            attribute = itemNode->first_attribute("parentId", 0, false);
            if (attribute)
                mediaItem->parentId = attribute->value();

            valueNode = itemNode->first_node("raumfeld:name", 0, false);
            if (valueNode)
                mediaItem->raumfeldName = valueNode->value();

            /*
            valueNode = itemNode->first_node("dc:title", 0, false);
            if (valueNode)
                mediaItem->title = valueNode->value();
                */

            valueNode = itemNode->first_node("upnp:class", 0, false);
            if (valueNode)
                mediaItem->upnpClass = valueNode->value();

            valueNode = itemNode->first_node("raumfeld:section", 0, false);
            if (valueNode)
                mediaItem->raumfeldSection = valueNode->value();

            valueNode = itemNode->first_node("res", 0, false);
            if (valueNode)
            {
                mediaItem->res = valueNode->value();
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