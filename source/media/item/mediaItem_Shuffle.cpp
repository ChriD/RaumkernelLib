
#include <raumkernel/media/item/mediaItem_Shuffle.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Shuffle::MediaItem_Shuffle() : MediaItem()
            {
                type = MediaItemType::MIT_SHUFFLE;
            }

            MediaItem_Shuffle::~MediaItem_Shuffle()
            {
            }

        }
    }
}

