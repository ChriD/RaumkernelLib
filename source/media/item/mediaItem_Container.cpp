
#include <raumkernel/media/item/mediaItem_Container.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Container::MediaItem_Container() : MediaItem()
            {
                type = MediaItemType::MIT_CONTAINER;
            }

            MediaItem_Container::~MediaItem_Container()
            {
            }

            void MediaItem_Container::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                MediaItem::initFromXMLNode(_xmlNode);

                title = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "dc:title"));
                description = "";
            }

        }
    }
}

