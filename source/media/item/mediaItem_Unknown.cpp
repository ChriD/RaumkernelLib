
#include <raumkernel/media/item/mediaItem_Unknown.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Unknown::MediaItem_Unknown() : MediaItem()
            {
                type = MediaItemType::MIT_UNKNOWN;
            }

            MediaItem_Unknown::~MediaItem_Unknown()
            {
            }

        }
    }
}

