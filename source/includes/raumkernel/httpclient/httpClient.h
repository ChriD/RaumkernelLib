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
#ifndef RAUMKERNEL_HTTPCLIENT_H
#define RAUMKERNEL_HTTPCLIENT_H

#include <unordered_map>
#include <functional>
#include <thread>
#include <raumkernel/raumkernelBaseMgr.h>
#include <raumkernel/httpclient/httpRequest.h>


namespace Raumkernel
{
    namespace HttpClient
    {

        class HttpClient : public RaumkernelBaseMgr
        {
            public:
                EXPORT HttpClient();
                EXPORT virtual ~HttpClient();                 
                /**
                * init has to be called after the HttpClient is instanciated
                * using the HttpClient without calling init() will not work!
                */
                EXPORT void init();
                /**
                * adds a request to the map and executes the request immediately
                * this method is async and in fact the callback function has to be given if you want to have a response info
                * currently there is no sync version of this method
                */
                EXPORT void request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars = nullptr, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars = nullptr, void *_userData = nullptr, std::function<void(HttpRequest*)> _callback = nullptr);
                /**
                * aborts all pending requests
                */
                EXPORT void abortAllRequests();
                /**
                * returns a shared pointer to a request which has the given id
                */
                EXPORT std::shared_ptr<HttpRequest> getRequest(std::string _requestId);           
                /**
                * lock the request map.
                * due the map consists of shared pointer references the lock is only needed if there is a 
                * direct acces to the map itself (delete/add)
                */
                void lockRequestMap();
                /**
                * unlock the request map               
                */
                void unlockRequestMap();
             

        protected:      
                /**
                * removes deletable requests (finished + processed ones) from the map
                */
                void cleanupRequests();
                /**
                * start thread wich will do the handling of redirections and deleteing non pending requests
                */            
                void startRequestHandlerThread();
                /**
                * Stop thread wich will do the handling of redirections and deleteing non pending requests
                * All requests will be aborted
                */
                void stopRequestHandlerThread();
                /**
                * The thread method wich will do the handling of redirections and deleteing non pending requests
                * All threads will be polled if they are redirections of if they are deletable or finished.
                * The method takes care of each of the states 
                */
                void requestHandlerThread();
                /**
                * Returns a id for a thread that is unique throughout the request map
                * this is used to identify a request. The request id is sent in the header of the request to
                */
                std::string getNextRequestId();
             
                /**
                * This map holds all the request that are pending and will be updated when adding a request or
                * if the requst handler thread removes finished requests
                */
                std::unordered_map<std::string, std::shared_ptr<HttpRequest>> requestMap;
                /**
                * Sleep time for the request handler after to check the states of the requests periodically
                */
                std::uint32_t sleepTimeRequestHandler;
                /**
                * Sleep time for the request pump which will look for incomming data
                */
                std::uint32_t sleepTimeRequestPump;
                /**
                * This mutex controls the access to the request map
                */
                std::mutex mutexRequestMap;
                /**
                * The thread for the request handler which will control the states of the requests periodically
                */
                std::thread threadRequestHandler;
                /**
                * Is used to abort the request handler thread. No more polling will be done therfore no signals of
                * finished requests will be delivered
                */
                std::atomic_bool abortRequestHandlerThread;           

        };
    }
}

#endif