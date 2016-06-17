
#include <raumkernel/media/item/mediaItem_StorageFolder.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_StorageFolder::MediaItem_StorageFolder() : MediaItem()
            {
                type = MediaItemType::MIT_STORAGEFOLDER;
            }

            MediaItem_StorageFolder::~MediaItem_StorageFolder()
            {
            }

        }
    }
}

