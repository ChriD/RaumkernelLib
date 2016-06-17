
#include <raumkernel/media/item/mediaItem.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {

            MediaItem::MediaItem() : RaumkernelBase()
            {
                id = "";
                parentId = "";
                upnpClass = "";
                raumfeldName = "";
                raumfeldSection = "";                               
            }

            MediaItem::~MediaItem()
            {
            }

            void MediaItem::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                id = Tools::UriUtil::unescape(Tools::XMLUtil::getNodeAttributeVal(_xmlNode, "id"));
                parentId = Tools::UriUtil::unescape(Tools::XMLUtil::getNodeAttributeVal(_xmlNode, "parentID"));
                upnpClass = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:class"));
                raumfeldName = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "raumfeld:name"));
                raumfeldSection = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "raumfeld:section"));                
            }

        }

    }


}

