
#include <raumkernel/media/item/mediaItem.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {

            MediaItem::MediaItem() : RaumkernelBase()
            {
                id = "";
                parentId = "";
                upnpClass = "";
                raumfeldName = "";
                raumfeldSection = "";               
                res = "";
            }

            MediaItem::~MediaItem()
            {
            }

        }

    }


}

