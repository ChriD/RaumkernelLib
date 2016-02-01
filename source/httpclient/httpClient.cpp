
#include <raumkernel/httpclient/httpClient.h>

namespace Raumkernel
{
    namespace HttpClient
    {
        HttpClient::HttpClient() : RaumkernelBase()
        {
        
        }


        HttpClient::~HttpClient()
        {
            killAllRequests();
        }


        void HttpClient::killAllRequests()
        {
            mutexRequestMap.lock();
            for each (auto mapitem in requestMap)
            {
                std::string requestId = mapitem.second->getId();
                logDebug("Aborting Request: " + requestId + " / " + mapitem.second->getRequestUrl(), CURRENT_POSITION);
                mapitem.second->abort();
                logDebug("Request aborted: " + requestId, CURRENT_POSITION);
            }
            mutexRequestMap.unlock();
            cleanupRequests();
        }


        void HttpClient::cleanupRequests()
        {
            std::lock_guard<std::mutex> lock(mutexRequestMap);    
            std::int32_t cleanUpCount = 0;

            for (auto it = requestMap.cbegin(); it != requestMap.cend() /* not hoisted */; /* no increment */)
            {
                if (it->second->isRequestFinished())
                {
                    requestMap.erase(it->second->getId());
                    cleanUpCount++;
                }
                else
                {
                    ++it;
                }
                
            }            
            
            logDebug("Requests cleaned up! Count: " + std::to_string(cleanUpCount), CURRENT_POSITION);
        }


        void HttpClient::request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback)
        {
            std::shared_ptr<Raumkernel::HttpClient::HttpRequest> httpRequest = std::shared_ptr<HttpRequest>(new HttpRequest(std::to_string(Tools::CommonUtil::randomUInt32()), _requestUrl, _headerVars, _postVars, _userData, _callback));
            
            // try to clean up pending requests
            cleanupRequests();

            mutexRequestMap.lock();
            try
            {
                requestMap.insert(std::make_pair(httpRequest->getId(), httpRequest));
            }
            catch ( ... )
            {
                // we should never get here!
            }

            mutexRequestMap.unlock();
   
            logDebug("Request '" + httpRequest->getId() + "(" + httpRequest->getRequestUrl() + ") started", CURRENT_POSITION);                       
            httpRequest->run();
        }

      
    }
}