
#include <httpclient/httpRequest.h>

namespace RaumserverInstaller
{
    namespace HttpClient
    {

        HttpRequest::HttpRequest() : RaumserverInstallerBase()
        {     
        }
       
              
        HttpRequest::HttpRequest(const std::string _requestId, const std::string _requestUrl, std::shared_ptr<std::unordered_map<std::string, std::string>> _headerVars, std::shared_ptr<std::unordered_map<std::string, std::string>> _postVars, void *_userData, std::function<void(HttpRequest*)> _callback) : RaumserverInstallerBase()
        {   
            httpResponse = nullptr;
            setRequestUrl(_requestUrl);
            requestId = _requestId;
            userData = _userData; 
            requestFinishedUserCallback = _callback;
            finished = false;
            deleteable = false;
            
            redirection = false;
            redirectionLocation = "";

            stopRequestThread = false;

            headerVars = _headerVars;
            postVars = _postVars;      
            
            sleepTimeRequestPump = 20;


            createHeadersAndPostStringVars();
        }


        HttpRequest::~HttpRequest()
        {       
            abort();
        }


        void HttpRequest::abort()
        {
            stopRequestThread = true;
            if (threadRequestRun.joinable())
                threadRequestRun.join();
            deleteable = true;
        }


        bool HttpRequest::isRedirection()
        {
            return redirection;
        }
       
        bool HttpRequest::isFinished()
        {
            return finished;
        }


        bool HttpRequest::isDeleteable()
        {
            return deleteable;
        }


        void HttpRequest::setFinished(bool _finished)
        {
            finished = _finished;
        }


        void HttpRequest::setDeleteable(bool _deletable)
        {
            deleteable = _deletable;
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


        void HttpRequest::setSleepTimeRequestPump(std::uint32_t _sleepTime)
        {
            sleepTimeRequestPump = _sleepTime;
        }


        void HttpRequest::setGotResponse(bool _gotResponse)
        {
            gotResponse = _gotResponse;
        }


        void HttpRequest::setRequestUrl(std::string _requestUrl)
        {
            requestUrl = _requestUrl;
        }


        std::string HttpRequest::getRedirectionLocation()
        {
            return redirectionLocation;
        }


        std::string HttpRequest::getRedirectionUrl()
        {
            LUrlParser::clParseURL parsedUrl = LUrlParser::clParseURL::ParseURL(getRequestUrl());
            return parsedUrl.m_Scheme + "://" + parsedUrl.m_Host + (parsedUrl.m_Port.empty() ? "" : ":") + parsedUrl.m_Port + getRedirectionLocation();
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


        void HttpRequest::doRequest()
        {
            stopRequestThread = false;
            redirection = false;
            finished = false;
            deleteable = false;
            redirectionLocation = "";

            // add posting urls            
            threadRequestRun = std::thread(&HttpRequest::runRequestPumpThread, this);
        }


                
        void HttpRequest::runRequestPumpThread()
        {
            // http://10.0.0.1:47365/0092409d-13a7-4471-9a1c-52e2f992fa5e/getZones?updateid=1869126996

            LUrlParser::clParseURL parsedUrl = LUrlParser::clParseURL::ParseURL(getRequestUrl());      
            happyhttp::Connection conn(parsedUrl.m_Host.c_str(), std::stoi(parsedUrl.m_Port));
            conn.setcallbacks(&HttpRequest::onBeginCallback, &HttpRequest::onDataCallback, &HttpRequest::onCompleteCallback, this);
            
           // std::string query = (!parsedUrl.m_Query.empty() ? "?" + parsedUrl.m_Query : "");
            std::string query;

            // Post vars
            if (postVars)
            {
                for (auto it = postVars->begin(); it != postVars->end(); ++it)
                {
                    // TODO: encode?!
                    query += query.empty() ? "?" : "&";
                    query += it->first + "=" + it->second;
                }
            }


            const char** headerCharPtrArray = (const char**)0;            
            std::uint16_t index = 0;            

            if (headerVars)
            {    
                //auto inta = headerVars->size();
                //headerCharPtrArray = new const char*[headerVars->size() + 1];                
                /*
                for (auto it = headerVars->begin(); it != headerVars->end(); ++it)
                {
                    headerCharPtrArray[index] = it->first.c_str();
                    index++;
                    headerCharPtrArray[index] = it->second.c_str();
                    index++;                  
                }   */
                /*
                for (auto it = headerVars->begin(); it != headerVars->end(); ++it)
                {
                    char *dummy;
                    
                    dummy = new char[it->first.length() + 1];
                    strncpy(dummy, it->first.c_str(), it->first.length());
                    dummy[it->first.length()] = 0;

                    headerCharPtrArray[index] = dummy;
                    index++;

                    dummy = new char[it->second.length() + 1];
                    strncpy(dummy, it->second.c_str(), it->second.length());
                    dummy[it->second.length()] = 0;

                    headerCharPtrArray[index] = dummy; // ####
                    index++;
                }
                headerCharPtrArray[index] = 0;  // ###
                */             
            }               

            std::unordered_map<std::string, std::string> header;
            if (headerVars != nullptr)
                header = *headerVars;

            std::string pathAndQuery = "/" + parsedUrl.m_Path + query;

            try
            {
                conn.request("GET", pathAndQuery.c_str(), header);            

                while (conn.outstanding() && !stopRequestThread)
                {
                    conn.pump();
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeRequestPump));
                }
            }
            catch (happyhttp::Wobbly _ex)
            {
                // something went wrong (maybe a access denied or something like that)
                // due we will get not callbacls now we have to finish the request and set an error              
                httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
                httpResponse->setData(_ex.what());                
                httpResponse->setErrorCode(999);
                setResponse(httpResponse);                
                finished = true;
            }
            catch ( ... )
            { 
                httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
                httpResponse->setData("unknown Error");
                httpResponse->setErrorCode(998);
                setResponse(httpResponse);
                finished = true;
            }

            // TODO: @@@ will make crash but without we have a memory leak :(
            /*if (index > 0)
            {
                for (int i = 0; i < sizeof(headerCharPtrArray); i++)
                {
                    delete headerCharPtrArray[i];                    
                }
                delete headerCharPtrArray;
            }
            */

            if (headerCharPtrArray)
            {
                //const char** h = headerCharPtrArray;
                while (*headerCharPtrArray)
                {
                    const char* name = *headerCharPtrArray++;
                    const char* value = *headerCharPtrArray++;
                    delete [] name;
                    delete [] value;
                }
                //delete [] headerCharPtrArray;
                // TODO: @@@ headerCharPtrArray has to be deleted, but it crashes.
            }

        }


        void HttpRequest::onBegin(const happyhttp::Response* _r)
        {                 
            httpResponse = std::shared_ptr<HttpResponse>(new HttpResponse());
            httpResponse->setData("");

            // check if response is a redirection. if so mark the request as redirection and set the "finished" marker so that the 
            // httClient will create a new request for the redirection and will not signal the request creator that the request is finished
            // the httpClient will also close the connectioon the this request when it's a redirection
            // HTTP / 1.1 307 Temporary Redirect
            if (_r->getstatus() == 307)
            {
                redirectionLocation = _r->getheader("LOCATION");                
                redirection = true;
                //requestFinished = true;
            }
        }


        void HttpRequest::onData(const happyhttp::Response* _r, const unsigned char* _data, int _n)
        {          
            
            std::string responseData = std::string(reinterpret_cast<const char*>(_data));            
            responseData.resize(_n);

            // 200 = HTTP-OK      
            httpResponse->setErrorCode((_r->getstatus() == 200) ? 0 : _r->getstatus());                     
            httpResponse->setHeaders(_r->getHeaders());
            
            // we get chunked data so we have to add the chunks together!            
            httpResponse->setData(httpResponse->getData() + responseData);
            setResponse(httpResponse);           
        }
        
        void HttpRequest::onComplete(const happyhttp::Response* _r)
        {
            finished = true;
        }



        void HttpRequest::onBeginCallback(const happyhttp::Response* _r, void* _userdata)
        {        
            HttpRequest* httpRequest = (HttpRequest*)_userdata;
            httpRequest->onBegin(_r);
        }


        void HttpRequest::onDataCallback(const happyhttp::Response* _r, void* _userdata, const unsigned char* _data, int _n)
        {
            HttpRequest* httpRequest = (HttpRequest*)_userdata;
            httpRequest->onData(_r, _data, _n);
        }
        
        void HttpRequest::onCompleteCallback(const happyhttp::Response* _r, void* _userdata)
        {
            HttpRequest* httpRequest = (HttpRequest*)_userdata;
            httpRequest->onComplete(_r);
        }
        
    }
}