
#include <raumkernel/media/item/mediaItem_Container.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Container::MediaItem_Container() : MediaItem()
            {
                type = MediaItemType::MIT_CONTAINER;
            }

            MediaItem_Container::~MediaItem_Container()
            {
            }

        }
    }
}

