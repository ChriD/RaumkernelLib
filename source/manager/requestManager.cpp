
#include <raumkernel/manager/requestManager.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        RequestManager::RequestManager() : ManagerBase()
        {           
        }


        RequestManager::~RequestManager()
        {         
        }


        void RequestManager::init(const std::string _raumfeldHostUrl, const std::uint16_t _raumfeldHostPort)
        {           
        }


        void RequestManager::onBeginRequest(const happyhttp::Response* _response, void* _userdata)
        {
            // TODO: redirects?!?!
            /*
            if redirect url
            if (userdata.context == Context Zone Long Polling Request)
            userdata.requestSettin
            */
        }


        void RequestManager::onDataRequest(const happyhttp::Response* _response, void* _userdata, const unsigned char* _data, int _dataCount)
        {

        }


        void RequestManager::onCompleteRequest(const happyhttp::Response* _response, void* _userdata)
        {
        }


        void RequestManager::requestZoneConfiguration()
        {
            std::string raumfeldHostIP = getManagerEngineer()->getDeviceManager()->getRaumfeldHostIP();
            if (raumfeldHostIP.empty())
            {
                logWarning("Calling requestZoneConfiguration without having host IP", CURRENT_POSITION);
                return;
            }

            // TODO: @@@
        }

        void RequestManager::request(std::string _request, std::unordered_map<std::string, std::string> *_headerVars, std::unordered_map<std::string, std::string> *_postVars, void* _userdata)
        {      
            std::string urlQueryPostVars = "";

            // get port and adress

            happyhttp::Connection conn("10.0.0.5", 47365);
            //happyhttp::Connection conn("google.com", 80);
            conn.setcallbacks(&RequestManager::onBeginRequest, &RequestManager::onDataRequest, &RequestManager::onCompleteRequest, _userdata);


            // if we got some '_postVars' we use this. For this we have to add the post values
            if (_postVars)
            {
                for (auto &mapItem : *_postVars)
                {
                    if (!urlQueryPostVars.empty())
                        urlQueryPostVars += "&";
                    urlQueryPostVars += Raumkernel::Tools::UriUtil::encodeUriPart(mapItem.first) + "=" + Raumkernel::Tools::UriUtil::encodeUriPart(mapItem.second);
                }      
            }

            const char* headers[] =
            {
                "Connection", "close",
                "Content-type", "application/x-www-form-urlencoded",
                "Accept", "text/plain",
                0
            };

            try
            {


                //conn.request("POST", "/getZones", nullptr, (unsigned const char *)urlQueryPostVars.c_str());
                //conn.request("GET", "/4b433d42-d747-4524-93c7-95ff5048710e/getZones", headers, (unsigned const char *)urlQueryPostVars.c_str());
                conn.request("GET", "/getZones", headers, (unsigned const char *)urlQueryPostVars.c_str());
                

                while (conn.outstanding())
                {
                    conn.pump();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    // TODO: add timeout
                }

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_POSITION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_POSITION);
            }
            catch (happyhttp::Wobbly &e)
            {
                logError(e.what(), CURRENT_POSITION);;
            }
            catch (...)
            {
                logError("Unknown exception!", CURRENT_POSITION);
            }
                
            /*
            std::string		longPollingUpdateId, ipAndPort, pathAndQuery;
            std::string		requestUrlAction, urlPostVars;
            boost::uint16_t cycles = 0;
            std::map<std::string, std::string> headerVars;

            if (_useHostPrefix)
                requestUrlAction = requestUrl + _request;
            else
                requestUrlAction = _request;

            boost::network::uri::uri instance(requestUrlAction);
            ipAndPort = instance.host();
            ipAndPort += !instance.port().empty() ? ":" + instance.port() : "";
            pathAndQuery = instance.path();
            //pathAndQuery += !instance.query().empty() ? "?" + instance.query() : "";

            this->Log(LogType::LOGDEBUG, "Doing request: '" + requestUrlAction + "'", __FUNCTION__);

            // if we got some '_postVars' we use this. For this we have to add the post values
            if (_postVars)
            {
                for (auto &mapItem : *_postVars)
                {
                    if (!urlPostVars.empty())
                        urlPostVars += "&";
                    urlPostVars += Utils::EncodeUriPart(mapItem.first) + "=" + Utils::EncodeUriPart(mapItem.second);
                }
                pathAndQuery += "?" + urlPostVars;
            }

            // if we got some '_headerVars' we use this
            if (_headerVars)
            {
                for (auto &mapItem : *_headerVars)
                {
                    headerVars.insert(std::make_pair(mapItem.first, mapItem.second));
                }
            }


            SimpleWeb::Client<SimpleWeb::HTTP> client(ipAndPort);
            this->Sleep(500);


            try
            {

                curRequestSocket = client.socket.get();
                auto httpResponse = client.request("GET", pathAndQuery, headerVars);
                this->Log(LogType::LOGDEBUG, "Request: '" + requestUrlAction + "' done...", __FUNCTION__);
                curRequestSocket = nullptr; // only valid while getting request!
                return httpResponse;

            }
            catch (boost::thread_interrupted const&)
            {
                this->Log(LogType::LOGDEBUG, "Request: '" + requestUrlAction + "' interrupted...", __FUNCTION__);
            }
            catch (std::exception &ex)
            {
                this->Log(LogType::LOGERROR, ex.what(), __FUNCTION__);
            }
            catch (...)
            {
                this->Log(LogType::LOGERROR, "Unknown error!", __FUNCTION__);
            }

            curRequestSocket = nullptr;
            return nullptr;
            */
        }
    }
}
