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
#ifndef RAUMKERNEL_HTTPREQUEST_H
#define RAUMKERNEL_HTTPREQUEST_H

#include <unordered_map>
#include <raumkernel/raumkernelBase.h>
#include <raumkernel/httpclient/mongoose.h>
#include <raumkernel/httpclient/httpResponse.h>
#include <raumkernel/tools/urlParser.h>


namespace Raumkernel
{
    namespace HttpClient
    {

      
        class HttpRequest : public RaumkernelBase
        {
            public:                
                EXPORT HttpRequest();
                EXPORT HttpRequest(const std::string _requestId, const std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars = nullptr, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars = nullptr, void *_userdata = nullptr, std::function<void(HttpRequest*)> _callback = nullptr);
                EXPORT virtual ~HttpRequest();
                EXPORT virtual void run();           
                EXPORT virtual void abort();
                EXPORT virtual std::string getId();
                EXPORT virtual std::string getRequestUrl();
                EXPORT virtual std::shared_ptr<HttpResponse> getResponse();
                EXPORT virtual bool isRequestFinished();
                void setGotResponse(bool _gotResponse);       
                void setRequestUrl(std::string _requestUrl);
                void setResponse(std::shared_ptr<HttpResponse> _httpResponse);          

            protected:
                void doRequest(std::string _url, std::atomic_bool _stopThread);
                virtual void runThread(std::atomic_bool _stopThread);

                /**
                * shared pointer to the response object
                * will only be filled when response is ready, otherweis its a nullptr
                */
                std::shared_ptr<HttpResponse> httpResponse;
                /**
                * url which we will request
                */
                std::string requestUrl;             
                /**
                *  unique request id 
                */
                std::string requestId;
                /**
                *  pointer to any user defined data
                */
                void *userData;
                /**
                *  the request callback function specified in the constructor by the developer
                */
                std::function<void(HttpRequest*)> requestFinishedUserCallback;         

                std::thread threadRequestRun;
                std::atomic_bool stopRequestThread;
                std::atomic_bool requestFinished;

                // mongose stuff
                struct mg_mgr mongoose_mgr;
                bool gotResponse;

                static void mongoose_handler(struct mg_connection *nc, int ev, void *ev_data);             

        };        
    }
}

#endif