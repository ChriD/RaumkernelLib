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
#ifndef RAUMKERNEL_MEDIAITEMCREATOR_H
#define RAUMKERNEL_MEDIAITEMCREATOR_H

#include <raumkernel/raumkernelBase.h>
#include <raumkernel/tools/uriUtil.h>
#include <raumkernel/media/item/mediaItems.h>
#include <raumkernel/xml/pugixml/pugixml.hpp>

namespace Raumkernel
{
    namespace Media
    {
        class MediaItemCreator : public RaumkernelBase
        {
            public:
                MediaItemCreator();
                virtual ~MediaItemCreator();

                EXPORT static std::shared_ptr<Media::Item::MediaItem> createObject(std::string _upnpClass, std::string _name);

                std::shared_ptr<Item::MediaItem> createMediaItemFromTrackMetadata(std::string _trackMetadata);                
                std::shared_ptr<Item::MediaItem> createMediaItemFromXMLNode(pugi::xml_node _xmlNode);

            protected:                
                std::string getNodeVal(const pugi::xml_node &_parentNode, const std::string &_nodeName, const std::string &_defaultVal = "");

            private:
        };
    }
}

#endif