
#include <raumkernel/httpclient/httpRequest.h>

namespace Raumkernel
{
    namespace HttpClient
    {

        HttpRequest::HttpRequest() : RaumkernelBase()
        {
            httpResponse = nullptr;
            requestFinishedUserCallback = nullptr;
            requestFinished = false;
        }
       
              
        HttpRequest::HttpRequest(const std::string _requestId, const std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback) : RaumkernelBase()
        {   
            httpResponse = nullptr;
            setRequestUrl(_requestUrl);
            requestId = _requestId;
            userData = _userData; 
            requestFinishedUserCallback = _callback;
            requestFinished = false;

            headerVars = _headerVars;
            postVars = _postVars;      

            createHeadersAndPostStringVars();
        }


        HttpRequest::~HttpRequest()
        {                
        }


        bool HttpRequest::isRequestFinished()
        {
            return requestFinished;
        }


        std::string HttpRequest::getId()
        {
            return requestId;
        }


        std::string HttpRequest::getRequestUrl()
        {
            return requestUrl;
        }


        std::shared_ptr<HttpResponse> HttpRequest::getResponse()
        {
            return httpResponse;
        }


        std::string HttpRequest::getPostVarsString()
        {
            return postVarsString;
        }


        std::string HttpRequest::getHeaderVarsString()
        {
            return headerVarsString;
        }


        void HttpRequest::setGotResponse(bool _gotResponse)
        {
            gotResponse = _gotResponse;
        }


        void HttpRequest::setRequestUrl(std::string _requestUrl)
        {
            requestUrl = _requestUrl;
        }


        void HttpRequest::setConnection(mg_connection *_connection)
        {
            connection = _connection;
        }


        void HttpRequest::setResponse(std::shared_ptr<HttpResponse> _httpResponse)
        {
            httpResponse = _httpResponse;
            if (_httpResponse != nullptr)
                this->setGotResponse(true);
        }


        void HttpRequest::emitRequestFinishCallback()
        {
            requestFinishedUserCallback(this);
        }
       


        void HttpRequest::createHeadersAndPostStringVars()
        {         
            if (headerVars != nullptr && !headerVars->empty())
            {
                for (auto iterator = headerVars->begin(); iterator != headerVars->end(); iterator++)
                {
                    headerVarsString += iterator->first + ": " + iterator->second;
                    headerVarsString += "\r\n";
                }
            }

            // add request information (unique id) to header
            headerVarsString += "RequestId: " + getId();
            headerVarsString += "\r\n";


            if (postVars != nullptr && !postVars->empty())
            {
                for (auto iterator = postVars->begin(); iterator != postVars->end(); iterator++)
                {
                    // TODO: uriencode?!
                    postVarsString += iterator->first + "=" + iterator->second;
                    postVarsString += "&";
                }
            }
        }



        /*
        
        void HttpRequest::runThread()
        {
            bool isRedirected;

            logDebug("Request thread started (" + getRequestUrl() + ")", CURRENT_POSITION);
            // start the request with the given url. there may be a redirection which will be handled here too
            do
            {
                isRedirected = false;
                doRequest(requestUrl.c_str());
                while (!gotResponse)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                if (gotResponse)
                {                  
                    // Handle HTTP Redirection
                    // the post and header var will stay the same from the original request, onl the url will be changed and the request wil lbe sent again
                    // HTTP / 1.1 307 Temporary Redirect
                    if (getResponse()->getStatusCode() == 307)
                    {                        
                        std::string redirectionUrl = getResponse()->getHeaderVar("LOCATION");
                        LUrlParser::clParseURL parsedUrl = LUrlParser::clParseURL::ParseURL(getRequestUrl());
                        setRequestUrl(parsedUrl.m_Scheme + "://" + parsedUrl.m_Host + (parsedUrl.m_Port.empty() ? "" : ":") + parsedUrl.m_Port + redirectionUrl);
                        isRedirected = true;
                        logDebug("Found request redirection to: " + redirectionUrl, CURRENT_POSITION);
                    }
                }

            } 
            while (isRedirected && gotResponse);    

            // call callback method if we got a response, but not if we killed the response
            // TODO: well thats a problem here...
            if (gotResponse && requestFinishedUserCallback)
                requestFinishedUserCallback(this);

            //mg_mgr_free(&mongoose_mgr);             

            logDebug("Request thread ended (" + getRequestUrl() + ")", CURRENT_POSITION);

            // we set the request that it is finished. the cleanup will be done by the client
            requestFinished = true;
        }
        */

        /*

        void HttpRequest::mongoose_handler(struct mg_connection *nc, int ev, void *ev_data) 
        {
            // TODO: lock

            struct http_message *hm = (struct http_message *) ev_data;
            HttpRequest *httpRequest = (HttpRequest*)nc->mgr->user_data;
            std::string response = "", responseHeader = "", responseData = "";

            if (httpRequest == nullptr)
                return;

            std::shared_ptr<HttpResponse> httpResponse;

            switch (ev) 
            { 
                case MG_EV_CONNECT:
                    if (*(int *)ev_data != 0) 
                    {
                        fprintf(stderr, "connect() failed: %s\n", strerror(*(int *)ev_data));
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
                    break;
                case MG_EV_POLL:
                    break;
                default:
                    // Error???
                    break;
            }
        }
        */
    }
}