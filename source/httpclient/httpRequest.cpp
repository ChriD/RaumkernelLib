
#include <raumkernel/httpclient/httpRequest.h>

namespace Raumkernel
{
    namespace HttpClient
    {

        HttpRequest::HttpRequest() : RaumkernelBase()
        {
            httpResponse = nullptr;
            requestFinishedUserCallback = nullptr;
            requestFinishedCallback = nullptr;
        }
       
              
        HttpRequest::HttpRequest(const std::string _requestId, const std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback) : RaumkernelBase()
        {   
            httpResponse = nullptr;
            requestUrl = _requestUrl;
            requestId = _requestId;
            userData = _userData;   
            requestFinishedUserCallback = _callback;
            
            mg_mgr_init(&mongoose_mgr, this);
        }


        HttpRequest::~HttpRequest()
        {
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


        void HttpRequest::setGotResponse(bool _gotResponse)
        {
            gotResponse = _gotResponse;
        }


        void HttpRequest::setResponse(std::shared_ptr<HttpResponse> _httpResponse)
        {
            httpResponse = _httpResponse;
            if (_httpResponse != nullptr)
                this->setGotResponse(true);
        }


        void HttpRequest::setFinishedCallback(std::function<void(HttpRequest*)> _callback)
        {
            requestFinishedCallback = _callback;
        }


        void HttpRequest::doRequest(std::string _url)
        {
            gotResponse = false;
            mg_connect_http(&mongoose_mgr, &HttpRequest::mongoose_handler, _url.c_str(), NULL, NULL);

            while (!gotResponse) {
                mg_mgr_poll(&mongoose_mgr, 1000);
            }
        }


        void HttpRequest::run()
        {
            bool isRedirected = false;

            // start the request with the given url. there may be a redirection which will be handled here too
            do
            {
                doRequest(requestUrl.c_str());
                if (gotResponse)
                {
                    // check if response is a redirection. if so we use the redirection url ans do the Reqzest again with the new url
                    // the post and header var will stay the same from the original request
                    // TODO: @@@
                }

            } 
            while (isRedirected && gotResponse);

                
            // call callback method if we got a response, but not if we killed the response
            if (gotResponse && requestFinishedUserCallback)
                requestFinishedUserCallback(this);            

            mg_mgr_free(&mongoose_mgr); 

            // TODO: call method on client so he can throw away this request from the map
            requestFinishedCallback(this);
        }



        void HttpRequest::mongoose_handler(struct mg_connection *nc, int ev, void *ev_data) 
        {
            struct http_message *hm = (struct http_message *) ev_data;
            HttpRequest *httpRequest = (HttpRequest*)nc->mgr->user_data;
            std::string responseHeader = "";

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

                    //if (s_show_headers) {
                    //    fwrite(hm->message.p, 1, hm->message.len, stdout);
                    // }
                    // else {
                    //fwrite(hm->body.p, 1, hm->body.len, stdout);
                    //}
                    //putchar('\n');

                    /*                        
                        HTTP/1.1 307 Temporary Redirect
                        Date: Sun, 12 Dec 1999 21:57:19 GMT
                        LOCATION: /201269c1-d844-4a25-93d9-c3bac23bfb91/getZones
                        Content-Length: 0
                    */
                   

                    httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
                    httpResponse->setErrorCode(0);

                   
                    if (nc->recv_mbuf.len)
                    {
                        responseHeader = nc->recv_mbuf.buf;
                        responseHeader.resize(nc->recv_mbuf.len);
                    }

                    httpResponse->createHeaderFromResponseStr(responseHeader);
                    httpRequest->setResponse(httpResponse);
                    break;
                default:
                    break;
            }
        }
    }
}