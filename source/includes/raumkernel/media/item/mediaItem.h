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
#include <raumkernel/tools/uriUtil.h>
#include <raumkernel/tools/xmlUtil.h>


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
            MIT_TRACK = 12,
            MIT_UNKNOWN = 99
        };
       
        namespace Item
        {

            class MediaItem : public RaumkernelBase
            {
                public:
                    MediaItem();
                    virtual ~MediaItem();

                    virtual void initFromXMLNode(const pugi::xml_node &_xmlNode);                    

                    MediaItemType type;

                    std::string id;
                    std::string parentId;
                    std::string upnpClass;
                    std::string raumfeldName;
                    std::string raumfeldSection;                    

                    static std::string mediaItemTypeToString(MediaItemType _mediaItemType)
                    {
                        switch (_mediaItemType)
                        {
                            case MediaItemType::MIT_ALBUM:
                                return "ALBUM";     
                            case MediaItemType::MIT_ARTIST:
                                return "ARTIST";
                            case MediaItemType::MIT_COMPOSER:
                                return "COMPOSER";
                            case MediaItemType::MIT_CONTAINER:
                                return "CONTAINER";
                            case MediaItemType::MIT_GENRE:
                                return "GENRE";
                            case MediaItemType::MIT_LINEIN:
                                return "LINEIN";
                            case MediaItemType::MIT_PLAYLIST:
                                return "PLAYLIST";
                            case MediaItemType::MIT_RADIO:
                                return "RADIO";
                            case MediaItemType::MIT_RHAPSODYRADIO:
                                return "RHAPSODYRADIO";
                            case MediaItemType::MIT_SHUFFLE:
                                return "SHUFFLE";
                            case MediaItemType::MIT_STORAGEFOLDER:
                                return "STORAGEFOLDER";
                            case MediaItemType::MIT_TRACK:
                                return "TRACK";
                            case MediaItemType::MIT_TRACKCONTAINER:
                                return "TRACKCONTAINER";
                        }
                        return "UNKNOWN";
                    }

                    static MediaItemType stringToMediaItemType(std::string _mediaItemType)
                    {
                        _mediaItemType = Tools::StringUtil::tolower(_mediaItemType);
                        if (_mediaItemType == "ALBUM")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "ARTIST")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "COMPOSER")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "CONTAINER")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "GENRE")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "LINEIN")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "PLAYLIST")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "RADIO")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "RHAPSODYRADIO")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "SHUFFLE")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "STORAGEFOLDER")
                            return MediaItemType::MIT_ALBUM;
                        if (_mediaItemType == "TRACKCONTAINER")
                            return MediaItemType::MIT_ALBUM;                                               
                        return MediaItemType::MIT_UNKNOWN;
                    }

                protected:                    

                private:
            };

        }

    }

}

#endif 