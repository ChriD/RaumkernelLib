
#include <raumkernel/media/item/mediaItem_TrackContainer.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_TrackContainer::MediaItem_TrackContainer() : MediaItem()
            {
                type = MediaItemType::MIT_TRACKCONTAINER;
            }

            MediaItem_TrackContainer::~MediaItem_TrackContainer()
            {
            }

        }
    }
}

