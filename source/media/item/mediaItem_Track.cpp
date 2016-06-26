
#include <raumkernel/media/item/mediaItem_Track.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Track::MediaItem_Track() : MediaItem_Album()
            {
                type = MediaItemType::MIT_TRACK;
                title = "";
                duration = "";
            }

            MediaItem_Track::~MediaItem_Track()
            {
            }


            void MediaItem_Track::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                MediaItem_Album::initFromXMLNode(_xmlNode);

                // TODO: @@@
                title = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "dc:title"));
                duration = "";
            }
        }
    }
}

