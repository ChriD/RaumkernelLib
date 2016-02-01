
#include <raumkernel/httpclient/httpResponse.h>

namespace Raumkernel
{
    namespace HttpClient
    {

        HttpResponse::HttpResponse() : RaumkernelBase()
        {
            errorCode = 0;
            statusCode = 0;
            statusText = "";
            protocol = "";
            data = "";
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


        std::string HttpResponse::getData()
        {
            return data;
        }


        void HttpResponse::setData(std::string _data)
        {
            data = _data;
        }


        void HttpResponse::createHeaderFromResponseStr(std::string _headerString)
        {
            auto headers = Tools::StringUtil::explodeString(_headerString, "\r\n");
            bool statusLineProcessed = false;
            
            headerVars.clear();

            for (auto headerLine : headers)
            {
                if (!headerLine.empty() && statusLineProcessed)
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
                statusLineProcessed = true;
            }

            if (headers.size() > 0)
            {
                auto statusInfo = Tools::StringUtil::explodeString(headers[0], " ", 2);
                if (statusInfo.size() >= 3)
                {
                    protocol = statusInfo[0];
                    statusCode = std::stoi(statusInfo[1]);
                    statusText = statusInfo[2];
                }
            }


        }


        std::uint16_t HttpResponse::getStatusCode()
        {
            return statusCode;
        }


        std::string HttpResponse::getProtocolInfo()
        {
            return protocol;
        }


        std::string HttpResponse::getStatusText()
        {
            return statusText;
        }


        std::string HttpResponse::getHeaderVar(std::string _varId)
        {
            std::string varId = _varId;
            std::transform(varId.begin(), varId.end(), varId.begin(), ::tolower);

            if (headerVars.find(varId) != headerVars.end())
            {
                return headerVars[varId];
            }
            return "";            
        }

       
    }
}