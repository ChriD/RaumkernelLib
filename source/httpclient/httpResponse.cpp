
#include <raumkernel/httpclient/httpResponse.h>

namespace Raumkernel
{
    namespace HttpClient
    {

        HttpResponse::HttpResponse() : RaumkernelBase()
        {
            errorCode = 0;
        }
       


        HttpResponse::~HttpResponse()
        {
        }


        void HttpResponse::setErrorCode(std::uint16_t _errorCode)
        {
            errorCode = _errorCode;
        }


        std::uint16_t HttpResponse::getErrorCode()
        {
            return errorCode;
        }


        void HttpResponse::createHeaderFromResponseStr(std::string _headerString)
        {
            auto headers = Tools::StringUtil::explodeString(_headerString, "\r\n");
            bool statusLineProcessed = false;

            for (auto headerLine : headers)
            {
                if (!headerLine.empty() && statusLineProcessed)
                {
                    auto headerPair = Tools::StringUtil::explodeString(headerLine, ":", 1);
                    if (headerPair.size() > 1)
                        headerVars.insert(std::make_pair(headerPair[0], headerPair[1]));
                }
                statusLineProcessed = true;
            }

            // TODO:  get Status code from the first line  Explode " "
            if (headers.size() > 0)
            {
                auto statusInfo = Tools::StringUtil::explodeString(headers[0], " ");
            }
            

        }


        /*
       - 1xx: Informational - Request received, continuing process

      - 2xx: Success - The action was successfully received,
        understood, and accepted

      - 3xx: Redirection - Further action must be taken in order to
        complete the request

      - 4xx: Client Error - The request contains bad syntax or cannot
        be fulfilled

      - 5xx: Server Error - The server failed to fulfill an apparently
        valid request

        */

        /*
        HTTP / 1.1 307 Temporary Redirect
        Date : Sun, 12 Dec 1999 21 : 57 : 19 GMT
        LOCATION : / 201269c1 - d844 - 4a25 - 93d9 - c3bac23bfb91 / getZones
        Content - Length : 0
        */

       
    }
}