
#include <raumkernel/media/item/mediaItem_Composer.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Composer::MediaItem_Composer() : MediaItem()
            {
                type = MediaItemType::MIT_COMPOSER;
            }

            MediaItem_Composer::~MediaItem_Composer()
            {
            }

        }
    }
}

