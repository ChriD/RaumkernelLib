
#include <raumkernel/media/item/mediaItem_Radio.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Radio::MediaItem_Radio() : MediaItem()
            {
                type = MediaItemType::MIT_UNKNOWN;
                title = "";
                region = "";
                albumArtUri = "";
                description = "";
                signalStrength = 0;
                bitrate = 0;
                durability = 0;
            }

            MediaItem_Radio::~MediaItem_Radio()
            {
            }           

        }
    }
}

