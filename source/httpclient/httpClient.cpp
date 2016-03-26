#include <raumkernel/httpclient/httpClient.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/manager/settingsManager.h>

namespace Raumkernel
{
    namespace HttpClient
    {
        HttpClient::HttpClient() : RaumkernelBaseMgr()
        {            
            sleepTimeRequestHandler = 20;
            sleepTimeRequestPump = 20;
        }


        HttpClient::~HttpClient()
        {
            stopRequestHandlerThread();         
        }


        void HttpClient::init()
        {
            sleepTimeRequestHandler = (std::uint32_t)std::stoi(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_HTTPREQUESTHANDLERSLEEP, "20"));
            sleepTimeRequestPump = (std::uint32_t)std::stoi(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_HTTPREQUESTPUMPSLEEP, "20"));
            startRequestHandlerThread();
        }
        
      
        void HttpClient::abortAllRequests()
        {            
            mutexRequestMap.lock();
            try
            {
                for (auto mapitem : requestMap)
                {
                    std::string requestId = mapitem.second->getId();
                    logDebug("Aborting Request: " + requestId + " / " + mapitem.second->getRequestUrl(), CURRENT_POSITION);
                    // the abortion is a sync call and waits till the abortion of the request is done
                    // aborted requests will be deleted from the request map from the request handler thread
                    mapitem.second->abort();
                    logDebug("Request aborted: " + requestId, CURRENT_POSITION);
                }
            }
            catch (...)
            {
                // due the abortion should not call any exceptions we do not closer specify the error
                logError("Abortion of requests failed!", CURRENT_POSITION);
            }
            mutexRequestMap.unlock();            
        }

        
        void HttpClient::cleanupRequests()
        {
            std::unique_lock<std::mutex> lock(mutexRequestMap);    
            std::int32_t cleanUpCount = 0;

            for (auto it = requestMap.cbegin(); it != requestMap.cend();)
            {               
                // check if a request is deletable (finished reports will stay until they are marked as deletable which
                // will be done by the request handler thread)
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
            // getting a random number does not mean that the number is unique,  so we have to check if this number is present in the 
            // map and if its the case we change the number until its unqiue
            std::uint32_t newId = Tools::CommonUtil::randomUInt32();            
            while (requestMap.count(std::to_string(newId)))
            {
                newId += 1;
            }
            return std::to_string(newId);
        }
        
        
        void HttpClient::request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback)
        {                                 
            // be sure threads don't interfere each others
            std::unique_lock<std::mutex> lock(mutexRequestMap);

            // create a new request object which will be stored in a map. Those requet object holds the headers and post vars and some other
            // useful data as the callback function when the request is finished
            std::shared_ptr<Raumkernel::HttpClient::HttpRequest> httpRequest = std::shared_ptr<HttpRequest>(new HttpRequest(getNextRequestId(), _requestUrl, _headerVars, _postVars, _userData, _callback));
            httpRequest->setLogObject(getLogObject());
            httpRequest->setSleepTimeRequestPump(sleepTimeRequestPump);

            // provide the requestId as header variable
            if (!_headerVars)
                _headerVars = std::shared_ptr<std::unordered_map<std::string, std::string>>(new std::unordered_map<std::string, std::string>());
            _headerVars->insert(std::make_pair("RequestID", httpRequest->getId()));

            // insert the request to the "pending requests" map and start it
            requestMap.insert(std::make_pair(httpRequest->getId(), httpRequest));                                 
            httpRequest->doRequest();
            
            logDebug("Request '" + httpRequest->getId() + "' (" + httpRequest->getRequestUrl() + ") started", CURRENT_POSITION);                                   
        }


        std::shared_ptr<HttpRequest> HttpClient::getRequest(std::string _requestId)
        {
            if (!requestMap.count(_requestId))
                return nullptr;
            return requestMap.at(_requestId);
        }


        void HttpClient::startRequestHandlerThread()
        {
            abortRequestHandlerThread = false;
            threadRequestHandler = std::thread(&HttpClient::requestHandlerThread, this);
        }


        void HttpClient::stopRequestHandlerThread()
        {
            abortAllRequests();

            abortRequestHandlerThread = true;
            if (threadRequestHandler.joinable())
                threadRequestHandler.join();
        }


        void HttpClient::lockRequestMap()
        {
            mutexRequestMap.lock();
        }


        void HttpClient::unlockRequestMap()
        {
            mutexRequestMap.unlock();
        }


        void HttpClient::requestHandlerThread()
        {
            std::vector<std::shared_ptr<Raumkernel::HttpClient::HttpRequest>> finishedRequests;
            bool unlockedList = false;

            // perform an endless loop until the abortion of the thread is called
            // this might be if the client will be destroyed or on a user specific call
            while (!abortRequestHandlerThread)
            {                            
                try
                {
                    unlockedList = false;
                    mutexRequestMap.lock();

                    for (auto it = requestMap.cbegin(); it != requestMap.cend();)
                    {
                        // when the request is finished we have to emit the callback attached to the request
                        // after the callback method has finished we set the request ready for deletion
                        if (it->second->isFinished() && !it->second->isDeleteable() && !it->second->isRedirection())
                        {            
                            finishedRequests.emplace_back(it->second);                                         
                        }
                        // when the request is a redirection we abort the current request (it will never finish) and 
                        // update the url of the request to the new redirection url. Then we start the request again.
                        else if (it->second->isRedirection())
                        {
                            logDebug("Redirection to url '" + it->second->getRedirectionUrl() + "' found! Do redirect request " + it->second->getId(), CURRENT_POSITION);
                            it->second->abort();  
                            it->second->setDeleteable(false);
                            it->second->setRequestUrl(it->second->getRedirectionUrl());                            
                            it->second->doRequest();
                            ++it;
                        }
                        // if request is pending, then do nothing...
                        else
                        {
                            ++it;
                        }
                    }

                    mutexRequestMap.unlock();
                    unlockedList = true;

                    // after unlocking the map we may emit the request finished signals
                    // we have to do this after the unlock because they signal receiver may create another request
                    for (auto request : finishedRequests)
                    {
                        request->emitRequestFinishCallback();
                        request->setDeleteable(true);
                    }
                    finishedRequests.clear();                        

                }
                // the emited callback method may throw errors, so we have to catch all kind of exceptions
                // to be sure the client does not
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

                // we may get here when a error throws and we might not have unlocked the map mutex yet
                if (!unlockedList)
                    mutexRequestMap.unlock();

                // remove deletable requests from the "pending request" map
                cleanupRequests();

                // sleep for some time to reduce CPU load.
                // the handler thread is not critical. Only the responses of the requests will be delayed for the maximum of this sleep value                               
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeRequestHandler));

            }
            
        }       
      
    }
}