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
#ifndef RAUMKERNEL_DEVICEEVENTPARSER_H
#define RAUMKERNEL_DEVICEEVENTPARSER_H

#include <raumkernel/raumkernelBase.h>
#include <raumkernel/device/device.h>
#include <raumkernel/xml/pugixml/pugixml.hpp>
#include <raumkernel/tools/numUtil.h>
#include <raumkernel/tools/uriUtil.h>
#include <raumkernel/tools/urlParser.h>
#include <raumkernel/media/item/mediaItems.h>
#include <raumkernel/media/mediaItemCreator.h>


namespace Raumkernel
{
    namespace Devices
    {
        namespace EventParser
        {
            /**
            * The DeviceEventParser
            *
            * This class handles all the subscriptions return xmls which we will get from a UPNP-Device
            */
            class DeviceEventParser : public RaumkernelBaseMgr
            {
                public:
                    DeviceEventParser();
                    virtual ~DeviceEventParser();
                    virtual void setDevice(Devices::Device *_device);

                protected:                    
                    virtual std::string getNodeVal(pugi::xml_node _parentNode, std::string _nodeName, std::string _oldVal, bool &_valChanged, std::string _attributeName = "val");

                /**
                *  A link to a UPNP-Device
                */
                Devices::Device *device;
         
            };
        }
    }
}


#endif