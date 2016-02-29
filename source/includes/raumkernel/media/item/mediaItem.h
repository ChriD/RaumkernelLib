//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_MEDIAITEM_H
#define RAUMKERNEL_MEDIAITEM_H

#include <raumkernel/raumkernelBase.h>


namespace Raumkernel
{
    namespace Media
    {
        enum class MediaItemType {
            MIT_TRACKCONTAINER = 0,
            MIT_ALBUM = 1,
            MIT_ARTIST = 2,
            MIT_GENRE = 3,
            MIT_COMPOSER = 4,
            MIT_CONTAINER = 5,
            MIT_RADIO = 6,
            MIT_PLAYLIST = 7,
            MIT_SHUFFLE = 8,
            MIT_RHAPSODYRADIO = 9,
            MIT_STORAGEFOLDER = 10,
            MIT_LINEIN = 11,
            MIT_TRACK = 12
        };


        namespace Item
        {

            class MediaItem : public RaumkernelBase
            {
                public:
                    MediaItem();
                    virtual ~MediaItem();

                    MediaItemType type;

                    std::string id;
                    std::string parentId;
                    std::string upnpClass;
                    std::string raumfeldName;
                    std::string raumfeldSection;
                    std::string res;

                protected:

                private:
            };

        }

    }

}

#endif 
