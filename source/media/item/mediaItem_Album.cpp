
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
            }

            MediaItem_Album::~MediaItem_Album()
            {
            }

        }
    }
}

