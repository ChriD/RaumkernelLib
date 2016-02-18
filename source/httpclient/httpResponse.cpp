
#include <raumkernel/httpclient/httpResponse.h>
#include <raumkernel/httpclient/httpClient.h>

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
            headerVars = HttpClient::getHeaders(_headerString);
            
            if (headerVars.size() > 0 && headerVars.count("status"))
            {
                auto statusInfoHeader = headerVars.at("status");
                auto statusInfo = Tools::StringUtil::explodeString(statusInfoHeader, " ", 2);
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