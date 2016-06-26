
#include <raumkernel/media/item/mediaItem_Album.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Album::MediaItem_Album() : MediaItem_Artist()
            {
                album = "";
                albumArtUri = "";
                albumDate = "";
                albumTotalPlaytime = "00:00:00";
                albumTrackCount = 0;
                type = MediaItemType::MIT_ALBUM;
            }

            MediaItem_Album::~MediaItem_Album()
            {
            }


            void MediaItem_Album::initFromXMLNode(const pugi::xml_node &_xmlNode)
            {
                MediaItem_Artist::initFromXMLNode(_xmlNode);
   
                album = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:album"));
                albumArtUri = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "upnp:albumArtURI"));
                albumDate = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "dc:date"));
                albumTotalPlaytime = Tools::UriUtil::unescape(Tools::XMLUtil::getChildNodeVal(_xmlNode, "raumfeld:totalPlaytime"));                
                albumTrackCount = std::stoi(Tools::XMLUtil::getNodeAttributeVal(_xmlNode, "childCount", "0"));
            }

          
            /*    
            <container parentID="0/My Music/Artists/2Raumwohnung" id="0/My Music/Artists/2Raumwohnung/AllTracks" restricted="1" childCount="24">
            <raumfeld:name>AllTracks</raumfeld:name>
            <upnp:class>object.container.trackContainer.allTracks</upnp:class>
            <raumfeld:section>My Music</raumfeld:section>
            <dc:title>All Tracks by 2Raumwohnung</dc:title>
            <upnp:artist>2Raumwohnung</upnp:artist>
            </container>
            - <container parentID="0/My Music/Artists/2Raumwohnung" id="0/My Music/Artists/2Raumwohnung/2Raumwohnung+In%20Wirklich" restricted="1" childCount="11">
            <raumfeld:name>Album</raumfeld:name>
            <upnp:class>object.container.album.musicAlbum</upnp:class>
            <raumfeld:section>My Music</raumfeld:section>
            <upnp:artist>2Raumwohnung</upnp:artist>
            <dc:date>2002</dc:date>
            <upnp:album>In Wirklich</upnp:album>
            <upnp:albumArtURI dlna:profileID="JPEG_TN">http://10.0.0.1:47366/?albumArtist=2Raumwohnung&album=In%20Wirklich</upnp:albumArtURI>
            <raumfeld:totalPlaytime>0:51:38</raumfeld:totalPlaytime>
            <dc:title>In Wirklich</dc:title>
            </container>

            */


        }
    }
}

