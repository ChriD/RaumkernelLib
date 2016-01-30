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
#ifndef RAUMKERNEL_REQUESTMANAGER_H
#define RAUMKERNEL_REQUESTMANAGER_H

#include <unordered_map>
#include <raumkernel/manager/managerBase.h>
#include <raumkernel/tools/uriUtil.h>
#include <raumkernel/httpclient/happyhttp.h>

namespace Raumkernel
{
    namespace Manager
    {
        class RequestManager : public ManagerBase
        {
            public:
                EXPORT RequestManager();
                EXPORT virtual ~RequestManager();

                /**
                * Init/ReInit of the Request Manager                
                */
                EXPORT void init(const std::string _raumfeldHostUrl, const std::uint16_t _raumfeldHostPort);

                EXPORT void requestZoneConfiguration();

                EXPORT void request(std::string _request, std::unordered_map<std::string, std::string> *_headerVars, std::unordered_map<std::string, std::string> *_postVars, void* _userdata);

            protected:                          
                
                static void onBeginRequest(const happyhttp::Response* _response, void* _userdata);
                static void onDataRequest(const happyhttp::Response* _response, void* _userdata, const unsigned char* _data, int _dataCount);
                static void onCompleteRequest(const happyhttp::Response* _response, void* _userdata);
     
        };
    }
}


#endif