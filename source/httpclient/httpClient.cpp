#include <raumkernel/httpclient/httpClient.h>

namespace Raumkernel
{
    namespace HttpClient
    {
        HttpClient::HttpClient() : RaumkernelBase()
        {
            abortPollingThread = false;
            //mg_mgr_init(&mongoose_mgr, this);
            startRequestPollingThread();
        }


        HttpClient::~HttpClient()
        {
            abortPollingThread = true;
            if (threadRequestPolling.joinable())
                threadRequestPolling.join();
            //mg_mgr_free(&mongoose_mgr);
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

        */

        void HttpClient::cleanupRequests()
        {
            std::unique_lock<std::mutex> lock(mutexRequestMap);    
            std::int32_t cleanUpCount = 0;

            for (auto it = requestMap.cbegin(); it != requestMap.cend();)
            {               
                if (it->second->isDeleteable())
                {
                    logDebug("Delete request '" + it->second->getId() + "' from pending list", CURRENT_POSITION);
                    it = requestMap.erase(it);
                    cleanUpCount++;
                }
                else
                {
                    ++it;
                }
                
            }            
            
            if (cleanUpCount)
                logDebug("Requests cleaned up! Count: " + std::to_string(cleanUpCount), CURRENT_POSITION);
        }


        std::string HttpClient::getNextRequestId()
        {
            std::uint32_t newId = Tools::CommonUtil::randomUInt32();
            while (requestMap.count(std::to_string(newId)))
            {
                newId += 1;
            }
            return std::to_string(newId);
        }
        
        


        void HttpClient::request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback)
        {                                 
            // be sure threads dont interfere each others
            std::unique_lock<std::mutex> lock(mutexRequestMap);

            // create a new request object which will be stored in a map. Those requet object holds the headers and post vars and some other
            // useful data as the callback function when the request is finished
            std::shared_ptr<Raumkernel::HttpClient::HttpRequest> httpRequest = std::shared_ptr<HttpRequest>(new HttpRequest(getNextRequestId(), _requestUrl, _headerVars, _postVars, _userData, _callback));
            httpRequest->setLogObject(getLogObject());
            requestMap.insert(std::make_pair(httpRequest->getId(), httpRequest));
          
            // start the request
            //mg_connection *connection = mg_connect_http(&mongoose_mgr, &HttpClient::mongoose_handler, httpRequest->getRequestUrl().c_str(), httpRequest->getHeaderVarsString().c_str(), httpRequest->getPostVarsString().c_str());   
            //httpRequest->setConnection(connection);
            httpRequest->doRequest();
            
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
                // next step is to check if a request is finished. if so we emit the callback assigned to the request             
                try
                {
                    for (auto it = requestMap.cbegin(); it != requestMap.cend();)
                    {
                        if (it->second->isFinished())
                        {
                            it->second->emitRequestFinishCallback();   
                            it->second->setDeleteable(true);
                            ++it;
                        }
                        else if (it->second->isRedirection())
                        {
                            logDebug("Redirection to url '" + it->second->getRedirectionUrl() + "' found! Do redirect request " + it->second->getId(), CURRENT_POSITION);
                            it->second->abort();  
                            it->second->setDeleteable(false);
                            it->second->setRequestUrl(it->second->getRedirectionUrl());                            
                            it->second->doRequest();
                            ++it;
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


                // clean finished requests
                cleanupRequests();

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
                                // remove trailing and beginning empty spaces
                                value = Tools::StringUtil::trim(value);
                                key = Tools::StringUtil::trim(key);
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
            /*
             struct http_message *hm = (struct http_message *) ev_data;
             HttpClient *httpClient = (HttpClient*)nc->mgr->user_data;
             std::shared_ptr<HttpResponse> httpResponse;             
             std::string response = "", responseHeader = "", responseData = "", send = "", sendHeader = "";

             if (httpClient == nullptr)
                 return;   
          
             // find correct request object for the given connection. 
             // for this we do have a request id in the header vars in the connection send buffer
             send = nc->send_mbuf.buf;
             send.resize(nc->send_mbuf.size);
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
                                 httpResponse->createHeaderFromResponseStr(response);

                                 // the header stops where there are the first "\r\n\r\n" chars. The responseData is the rest              
                                 std::int32_t headerEnd = response.find("\r\n\r\n");
                                 responseData = response.substr(headerEnd + 4, nc->recv_mbuf.len - headerEnd + 4);
                                 httpResponse->setData(responseData);                            
                             }
                             httpRequest->setResponse(httpResponse);

                             // TODO: handle redirection

                             // Handle HTTP Redirection
                             // the post and header var will stay the same from the original request, onl the url will be changed and the request wil lbe sent again
                             // HTTP / 1.1 307 Temporary Redirect
                             if (httpResponse->getStatusCode() == 307)
                             {
                                 std::string redirectionUrl = httpResponse->getHeaderVar("LOCATION");
                                 LUrlParser::clParseURL parsedUrl = LUrlParser::clParseURL::ParseURL(httpRequest->getRequestUrl());
                                 httpRequest->setRequestUrl(parsedUrl.m_Scheme + "://" + parsedUrl.m_Host + (parsedUrl.m_Port.empty() ? "" : ":") + parsedUrl.m_Port + redirectionUrl);                             
                                 //isRedirected = true; // TODO: @@@
                                 httpClient->logDebug("Found request redirection to: " + redirectionUrl, CURRENT_POSITION);
                             
                                 // DO REQUEST REDIRECTION
                                 // start the redirection
                                 mg_connection *connection = mg_connect_http(httpClient->getMongooseMgr(), &HttpClient::mongoose_handler, httpRequest->getRequestUrl().c_str(), httpRequest->getHeaderVarsString().c_str(), httpRequest->getPostVarsString().c_str());
                                 httpRequest->setConnection(connection);
                             }
                             else
                             {
                                 httpRequest->setRequestFinished(true);
                             }

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
             */
                        
        }

      
    }
}