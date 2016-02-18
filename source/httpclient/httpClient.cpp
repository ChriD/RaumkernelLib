#include <raumkernel/httpclient/httpClient.h>

namespace Raumkernel
{
    namespace HttpClient
    {
        HttpClient::HttpClient() : RaumkernelBase()
        {
            abortPollingThread = false;
            mg_mgr_init(&mongoose_mgr, this);
            startRequestPollingThread();
        }


        HttpClient::~HttpClient()
        {
            abortPollingThread = true;
            if (threadRequestPolling.joinable())
                threadRequestPolling.join();
            mg_mgr_free(&mongoose_mgr);
        }


        /*
      
        void HttpClient::killAllRequests()
        {
            
            mutexRequestMap.lock();
            try
            {
                for each (auto mapitem in requestMap)
                {
                    std::string requestId = mapitem.second->getId();
                    logDebug("Aborting Request: " + requestId + " / " + mapitem.second->getRequestUrl(), CURRENT_POSITION);
                    mapitem.second->abort();
                    logDebug("Request aborted: " + requestId, CURRENT_POSITION);
                }
            }
            catch (...)
            {
                // TODO: @@@ we should never get here!
            }
            mutexRequestMap.unlock();
            cleanupRequests();
        }


        void HttpClient::cleanupRequests()
        {
            std::lock_guard<std::mutex> lock(mutexRequestMap);    
            std::int32_t cleanUpCount = 0;

            for (auto it = requestMap.cbegin(); it != requestMap.cend())
            {               
                if (it->second->isRequestFinished())
                {
                    it = requestMap.erase(it);
                    cleanUpCount++;
                }
                else
                {
                    ++it;
                }
                
            }            
            
            logDebug("Requests cleaned up! Count: " + std::to_string(cleanUpCount), CURRENT_POSITION);
        }
        */
        


        void HttpClient::request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback)
        {                                 
            // try to clean up pending requests
            //cleanupRequests();

            std::lock_guard<std::mutex> lock(mutexRequestMap);

            // create a new request object which will be stored in a map. Those requet object holds the headers and post vars and some other
            // useful data as the callback function when the request is finished
            std::shared_ptr<Raumkernel::HttpClient::HttpRequest> httpRequest = std::shared_ptr<HttpRequest>(new HttpRequest(std::to_string(Tools::CommonUtil::randomUInt32()), _requestUrl, _headerVars, _postVars, _userData, _callback));                     
            httpRequest->setLogObject(getLogObject());
            requestMap.insert(std::make_pair(httpRequest->getId(), httpRequest));
          
            // start the request
            mg_connection *connection = mg_connect_http(&mongoose_mgr, &HttpClient::mongoose_handler, httpRequest->getRequestUrl().c_str(), httpRequest->getHeaderVarsString().c_str(), httpRequest->getPostVarsString().c_str());   
            httpRequest->setConnection(connection);
            
            logDebug("Request '" + httpRequest->getId() + "' (" + httpRequest->getRequestUrl() + ") started", CURRENT_POSITION);                                   
        }


        std::shared_ptr<HttpRequest> HttpClient::getRequest(std::string _requestId)
        {
            if (!requestMap.count(_requestId))
                return nullptr;
            return requestMap.at(_requestId);
        }


        void HttpClient::startRequestPollingThread()
        {
            threadRequestPolling = std::thread(&HttpClient::requestPollingThread, this);
        }


        void HttpClient::lockRequestMap()
        {
            mutexRequestMap.lock();
        }


        void HttpClient::unlockRequestMap()
        {
            mutexRequestMap.unlock();
        }


        void HttpClient::requestPollingThread()
        {
            while (!abortPollingThread)
            {
                // do the mongoose stuff and  let the client handle the returns of our request
                // this poll will call the static "mongoose_handler" method
                mg_mgr_poll(&mongoose_mgr, 1000);

                // of course we have to lock the request map again because we may delete some itmes and we do
                // a read of the HttpRequest object
                lockRequestMap();

                // next step is to check if a request is finished. if so we emit the callback assigned to the request
                // and then after this is finished we do delete the now finished request from the list
                try
                {
                    for (auto it = requestMap.cbegin(); it != requestMap.cend();)
                    {
                        if (it->second->isRequestFinished())
                        {
                            it->second->emitRequestFinishCallback();
                            it = requestMap.erase(it);
                        }
                        else
                        {
                            ++it;
                        }

                    }
                }
                catch (Raumkernel::Exception::RaumkernelException &e)
                {
                    if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                        throw e;
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::exception &e)
                {
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::string &e)
                {
                    logError(e, CURRENT_FUNCTION);
                }
                catch (...)
                {
                    logError("Unknown Exception", CURRENT_FUNCTION);
                }

                // unlocming has to be done after deleting and checking the reuqest map for finished requests
                unlockRequestMap();

                //  TODO: @@@ Sleep


            }
        }


        std::unordered_map<std::string, std::string> HttpClient::getHeaders(std::string _string)        
        {
            std::unordered_map<std::string, std::string> headerVars;
            std::int32_t headerEnd = _string.find("\r\n\r\n");
            if (headerEnd > 0)
            {
                _string.resize(headerEnd);

                auto headers = Tools::StringUtil::explodeString(_string, "\r\n");
                bool statusLineProcessed = false;

                headerVars.clear();

                for (auto headerLine : headers)
                {
                    if (!headerLine.empty())
                    {
                        if (statusLineProcessed)
                        {
                            auto headerPair = Tools::StringUtil::explodeString(headerLine, ":", 1);
                            if (headerPair.size() > 1)
                            {
                                std::string key = headerPair[0];
                                std::string value = headerPair[1];
                                // we do tolower the key values so we do not have any problem getting the values when the 
                                // getHeaderValue is not matching the case
                                std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                                headerVars.insert(std::make_pair(key, value));
                            }
                        }
                        else
                        {
                            headerVars.insert(std::make_pair("status", headerLine));
                        }
                        statusLineProcessed = true;
                    }                    
                }
            }

            return headerVars;
        }   


        void HttpClient::mongoose_handler(struct mg_connection *nc, int ev, void *ev_data)
        {        
             struct http_message *hm = (struct http_message *) ev_data;
             HttpClient *httpClient = (HttpClient*)nc->mgr->user_data;
             std::shared_ptr<HttpResponse> httpResponse;             
             std::string response = "", responseHeader = "", responseData = "", send = "", sendHeader = "";

             if (httpClient == nullptr)
                 return;   
          
             // find correct request object for the given connection. 
             // for this we do have a request id in the header vars in the connection send buffer
             send = nc->send_mbuf.buf;
             send.resize(nc->send_mbuf.len);
             auto requestHeaders = getHeaders(send); 
             if (!requestHeaders.count("requestid"))
                 return;
             std::string requestId = requestHeaders.at("requestid");

             // lock the request map on the client 
             httpClient->lockRequestMap();

             try
             {

                 // now that we have the request id we can search for the appropiate request object in the client request map       
                 auto httpRequest = httpClient->getRequest(requestId);
                 if (httpRequest)
                 {

                     switch (ev)
                     {
                     case MG_EV_CONNECT:
                         if (*(int *)ev_data != 0)
                         {
                             // there was a problem to connect to the response url
                             httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
                             httpResponse->setErrorCode(1);
                             httpRequest->setResponse(httpResponse);
                         }
                         break;
                     case MG_EV_HTTP_REPLY:
                         nc->flags |= MG_F_CLOSE_IMMEDIATELY;

                         httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
                         httpResponse->setErrorCode(0);


                         if (nc->recv_mbuf.len)
                         {
                             response = nc->recv_mbuf.buf;
                             responseHeader.resize(nc->recv_mbuf.len);

                             // the header stops wher there are the first "\r\n\r\n" chars
                             std::int32_t headerEnd = response.find("\r\n\r\n");
                             responseHeader = response.substr(0, headerEnd ? headerEnd : nc->recv_mbuf.len);
                             httpResponse->createHeaderFromResponseStr(responseHeader);

                             // responseData is the rest                        
                             responseData = response.substr(headerEnd + 4, nc->recv_mbuf.len - headerEnd + 4);
                             httpResponse->setData(responseData);

                         }
                         httpRequest->setResponse(httpResponse);

                         // TODO: handle redirection

                         break;
                     case MG_EV_POLL:
                         break;
                     default:
                         // Error???
                         break;
                     }

                 }

             }
             catch (Raumkernel::Exception::RaumkernelException &e)
             {
                 if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                     throw e;     
                 httpClient->logError(e.what(), CURRENT_FUNCTION);
             }
             catch (std::exception &e)
             {
                 httpClient->logError(e.what(), CURRENT_FUNCTION);
             }
             catch (std::string &e)
             {
                 httpClient->logError(e, CURRENT_FUNCTION);
             }            
             catch (...)
             {
                 httpClient->logError("Unknown Exception", CURRENT_FUNCTION);
             }

             // lock the request map on the client 
             httpClient->unlockRequestMap();
                        
        }

      
    }
}