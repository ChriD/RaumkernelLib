
#include <raumkernel/media/item/mediaItem_Playlist.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Playlist::MediaItem_Playlist() : MediaItem()
            {
                type = MediaItemType::MIT_PLAYLIST;
            }

            MediaItem_Playlist::~MediaItem_Playlist()
            {
            }

        }
    }
}

