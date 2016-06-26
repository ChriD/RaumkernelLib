
#include <raumkernel/media/item/mediaItem_Artist.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Artist::MediaItem_Artist() : MediaItem()
            {
                artist = "";
                artistArtUri = "";
                type = MediaItemType::MIT_ARTIST;
            }

            MediaItem_Artist::~MediaItem_Artist()
            {
            }


            void MediaItem_Artist::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                MediaItem::initFromXMLNode(_xmlNode);
                artist = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:artist"));
                artistArtUri = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:albumArtURI"));
            }

            /*

            <container parentID="0/My Music/Artists" id="0/My Music/Artists/3%20Colours%20Red" restricted="1" childCount="2" numberOfAlbums="1">
            <raumfeld:name>Artist</raumfeld:name>
            <upnp:class>object.container.person.musicArtist</upnp:class>
            <raumfeld:section>My Music</raumfeld:section>
            <dc:title>3 Colours Red</dc:title>
            <upnp:artist>3 Colours Red</upnp:artist>
            <upnp:albumArtURI dlna:profileID="JPEG_TN">http://10.0.0.1:47366/?artist=3%20Colours%20Red</upnp:albumArtURI>
            <res protocolInfo="dlna-playcontainer:*:application/xml:*">dlna-playcontainer://uuid%3Af9fb29f4-334d-4a94-afcf-8b382982a9bd?sid=urn%3Aupnp-org%3AserviceId%3AContentDirectory&cid=0%2FMy%20Music%2FArtists%2F3%2520Colours%2520Red%2FAllTracks&fid=0&fii=0&sc=%2Bupnp%3Aalbum%2C%2Bupnp%3AoriginalTrackNumber%2C%2Bdc%3Atitle</res>
            </container>
            - <container parentID="0/My Music/Artists" id="0/My Music/Artists/3%20Doors%20Down" restricted="1" childCount="6" numberOfAlbums="5">
            <raumfeld:name>Artist</raumfeld:name>
            <upnp:class>object.container.person.musicArtist</upnp:class>
            <raumfeld:section>My Music</raumfeld:section>
            <dc:title>3 Doors Down</dc:title>
            <upnp:artist>3 Doors Down</upnp:artist>
            <upnp:albumArtURI dlna:profileID="JPEG_TN">http://10.0.0.1:47366/?artist=3%20Doors%20Down</upnp:albumArtURI>
            <res protocolInfo="dlna-playcontainer:*:application/xml:*">dlna-playcontainer://uuid%3Af9fb29f4-334d-4a94-afcf-8b382982a9bd?sid=urn%3Aupnp-org%3AserviceId%3AContentDirectory&cid=0%2FMy%20Music%2FArtists%2F3%2520Doors%2520Down%2FAllTracks&fid=0&fii=0&sc=%2Bupnp%3Aalbum%2C%2Bupnp%3AoriginalTrackNumber%2C%2Bdc%3Atitle</res>
            </container>

            */

        }
    }
}

