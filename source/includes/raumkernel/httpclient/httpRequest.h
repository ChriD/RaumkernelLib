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

#include <functional>
#include <unordered_map>
#include <raumkernel/raumkernelBase.h>
//#include <raumkernel/httpclient/mongoose.h>
#include <raumkernel/httpclient/happyhttp.h>
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
                EXPORT virtual std::string getId();
                EXPORT virtual std::string getRequestUrl();
                EXPORT virtual std::shared_ptr<HttpResponse> getResponse();
                EXPORT virtual bool isFinished();
                EXPORT virtual bool isRedirection();
                EXPORT virtual bool isDeleteable();
                EXPORT void setGotResponse(bool _gotResponse);
                EXPORT void setRequestUrl(std::string _requestUrl);
                EXPORT void setResponse(std::shared_ptr<HttpResponse> _httpResponse);
                EXPORT void setFinished(bool _finished = true);
                EXPORT void setDeleteable(bool _deletable = true);
                EXPORT void emitRequestFinishCallback();

                EXPORT std::string getRedirectionLocation();
                EXPORT std::string getRedirectionUrl();

                EXPORT void doRequest();
                EXPORT void abort();

                EXPORT virtual std::string getPostVarsString();
                EXPORT virtual std::string getHeaderVarsString();


            protected:
                virtual void createHeadersAndPostStringVars();
                virtual void runRequestPumpThread();

                void onBegin(const happyhttp::Response* _r);
                void onData(const happyhttp::Response* _r, const unsigned char* _data, int _n);
                void onComplete(const happyhttp::Response* _r);
              
                static void onBeginCallback(const happyhttp::Response* _r, void* _userdata);
                static void onDataCallback(const happyhttp::Response* _r, void* _userdata, const unsigned char* _data, int _n);
                static void onCompleteCallback(const happyhttp::Response* _r, void* _userdata);

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
                * 
                */
                std::shared_ptr<std::unordered_map<std::string, std::string>> headerVars;
                std::string headerVarsString = "";                
                /**
                *
                */
                std::shared_ptr<std::unordered_map<std::string, std::string>> postVars;
                std::string postVarsString = "";
                /**
                *  the request callback function specified in the constructor by the developer
                */
                std::function<void(HttpRequest*)> requestFinishedUserCallback;         

                std::thread threadRequestRun;
                std::atomic_bool stopRequestThread;

                std::atomic_bool finished;
                std::atomic_bool deleteable;
                std::atomic_bool redirection;
                std::string redirectionLocation;

                bool gotResponse;
               

        };        
    }
}

#endif
