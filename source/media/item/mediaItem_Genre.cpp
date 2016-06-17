
#include <raumkernel/media/item/mediaItem_Genre.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Genre::MediaItem_Genre() : MediaItem()
            {
                type = MediaItemType::MIT_GENRE;
            }

            MediaItem_Genre::~MediaItem_Genre()
            {
            }

        }
    }
}

