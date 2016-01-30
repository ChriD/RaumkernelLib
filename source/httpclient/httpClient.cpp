
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
        }


        void HttpClient::requestFinished(HttpRequest *_request)
        {
            if (_request == nullptr)
                return;

            std::lock_guard<std::mutex> lock(mutexRequestMap);


            if (requestMap.find(_request->getId()) != requestMap.end())
            {
                requestMap.erase(_request->getId());                
                logDebug("Request '" + _request->getId()  + "(" + _request->getRequestUrl() + ") finished with code '" + std::to_string(_request->getResponse()->getErrorCode()) + "'", CURRENT_POSITION);
            }
            else
            {
                logWarning("Could not find request with id '" + _request->getId() + "' in request list!", CURRENT_POSITION);
            }
        }


        void HttpClient::request(std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback)
        {
            std::shared_ptr<Raumkernel::HttpClient::HttpRequest> httpRequest = std::shared_ptr<HttpRequest>(new HttpRequest(std::to_string(Tools::CommonUtil::randomUInt32()), _requestUrl, _headerVars, _postVars, _userData, _callback));
            

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

            httpRequest->setFinishedCallback(std::bind(&HttpClient::requestFinished, this, std::placeholders::_1));

            // TODO: create thread
            logDebug("Request '" + httpRequest->getId() + "(" + httpRequest->getRequestUrl() + ") started", CURRENT_POSITION);
            httpRequest->run();
        }

      
    }
}