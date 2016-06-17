
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
                res = "";
            }

            MediaItem::~MediaItem()
            {
            }


            std::string MediaItem::getNodeVal(const pugi::xml_node &_parentNode, const std::string &_nodeName, const std::string &_defaultVal)
            {
                return Tools::XMLUtil::getNodeVal(_parentNode, _nodeName, _defaultVal);
            }


            void MediaItem::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                id = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "id"));
                parentId = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "parentID"));
                upnpClass = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "upnp:class"));
                raumfeldName = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "raumfeld.name"));                
                raumfeldSection = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "raumfeld:section"));
                res = Tools::UriUtil::unescape(getNodeVal(_xmlNode, "res"));
            }

        }

    }


}

