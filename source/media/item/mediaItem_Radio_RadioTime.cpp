
#include <raumkernel/media/item/mediaItem_Radio_RadioTime.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Radio_RadioTime::MediaItem_Radio_RadioTime() : MediaItem_Radio()
            {
                type = MediaItemType::MIT_RADIO_RADIOTIME;
            }

            MediaItem_Radio_RadioTime::~MediaItem_Radio_RadioTime()
            {
            }


            void MediaItem_Radio_RadioTime::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                MediaItem::initFromXMLNode(_xmlNode);
                title = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "dc:title"));
                region = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:region"));
                albumArtUri = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:albumArtURI"));   
                description = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "dc:description"));
                signalStrength = std::stoi(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:signalStrength", "0"));                
                durability = std::stoi(Tools::XMLUtil::getChildNodeVal(_xmlNode, "raumfeld:durability", "0"));  
                bitrate = std::stoi(Tools::XMLUtil::getChildNodeAttributeVal(_xmlNode, "res", "bitrate", "0"));
            }

            /*                      
            <upnp:signalStrength>94< / upnp:signalStrength>         
            <upnp:albumArtURI dlna : profileID = "JPEG_TN">http://cdn-radiotime-logos.tunein.com/s68932q.png</upnp:albumArtURI>
            <dc : description>Relax< / dc : description>
            <raumfeld : ebrowse>http ://opml.radiotime.com/Tune.ashx?partnerId=7aJ9pvV5&formats=wma%2Cmp3%2Cogg&serial=00%3A0d%3Ab9%3A19%3Ab5%3Aa4&id=s68932&c=ebrowse</raumfeld:ebrowse>
            <res bitrate = "128" protocolInfo = "http-get:*:audio/x-mpegurl:*">http ://opml.radiotime.com/Tune.ashx?id=s68932&formats=wma,mp3,ogg&partnerId=7aJ9pvV5&serial=00:0d:b9:19:b5:a4</res>
            <raumfeld : name>Station< / raumfeld : name>
            <upnp : class>object.item.audioItem.audioBroadcast.radio< / upnp : class>
            <raumfeld : section>RadioTime< / raumfeld : section>
            <raumfeld : durability>120< / raumfeld : durability>
            < / item>
            -<item parentID = "0/RadioTime/CategoryMusic/c-c10635888" id = "0/RadioTime/CategoryMusic/c-c10635888/s-s90408" restricted = "1">
            <dc:title>181.FM Mellow Gold< / dc:title>
            <upnp:signalStrength>92< / upnp:signalStrength>
            <upnp:region>US< / upnp:region>
            <upnp:albumArtURI dlna : profileID = "JPEG_TN">http://cdn-radiotime-logos.tunein.com/s90408q.png</upnp:albumArtURI>
            <raumfeld : ebrowse>http ://opml.radiotime.com/Tune.ashx?partnerId=7aJ9pvV5&formats=wma%2Cmp3%2Cogg&serial=00%3A0d%3Ab9%3A19%3Ab5%3Aa4&id=s90408&c=ebrowse</raumfeld:ebrowse>
            <res bitrate = "128" protocolInfo = "http-get:*:audio/x-mpegurl:*">http ://opml.radiotime.com/Tune.ashx?id=s90408&formats=wma,mp3,ogg&partnerId=7aJ9pvV5&serial=00:0d:b9:19:b5:a4</res>
            <raumfeld : name>Station< / raumfeld : name>
            <upnp : class>object.item.audioItem.audioBroadcast.radio< / upnp : class>
            <raumfeld : section>RadioTime< / raumfeld : section>
            <raumfeld : durability>120< / raumfeld : durability>
            < / item>
            */

        }
    }
}

