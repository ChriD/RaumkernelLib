#include <raumkernel/device/deviceMediaServer.h>
#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaServer::MediaServer() : Device()
        {
            contentDirectoryProxy = nullptr;            
            connectionManagerProxy = nullptr;
        }


        MediaServer::~MediaServer()
        {
            // no need to remove subscriptions! delete of proxies will handle this correct!
            this->deleteProxies();
        }


        bool MediaServer::isRaumfeldMediaServer()
        {
            return false;
        }


        void MediaServer::deleteProxies()
        {
            // due the proxies are shared pointers we can set them to nullptr instead of deleteing them first
            // n fact its not best practice to force shared pointers to 'nullptr' but in our case the MediaServer 
            // class may be existent without the proxies (for a short time)            
            contentDirectoryProxy = nullptr;
            connectionManagerProxy = nullptr;
        }


        void MediaServer::createProxies()
        {
            if (!cpDevice)
            {
                logWarning("Calling 'createProxies' on server " + this->getDeviceDescription() + " without cpDevice!", CURRENT_POSITION);
                this->deleteProxies();
                return;
            }

            // create standard proxies for the common media servers
            if (!contentDirectoryProxy)
            {
                logDebug("Create ContentDirectory-Proxy for media server " + this->getDeviceDescription(), CURRENT_POSITION);
                createProxyContentDirectory();
            }

            if (!connectionManagerProxy)
            {
                logDebug("Create ConnectionManager-Proxy for media server " + this->getDeviceDescription(), CURRENT_POSITION);
                createProxyConnectionManager();
            }

        }


        void MediaServer::createProxyContentDirectory()
        {            
            contentDirectoryProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(new OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp(*cpDevice));
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer::onContentDirectoryProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(getContentDirectoryProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);            
            proxy->Subscribe();

        }


        void MediaServer::createProxyConnectionManager()
        {
            connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp(*cpDevice));
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer::oConnectionManagerProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(getConnectionManagerProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->Subscribe();
        }


        bool MediaServer::isContentDirectoryProxyAvailable()
        {
            if (!cpDevice)
                return false;
            if (!contentDirectoryProxy)
                return false;
            return true;
        }


        bool MediaServer::isConnectionManagerProxyAvailable()
        {
            if (!cpDevice)
                return false;
            if (!connectionManagerProxy)
                return false;
            return true;
        }


        std::shared_ptr<OpenHome::Net::ICpProxy> MediaServer::getContentDirectoryProxy()
        {
            return contentDirectoryProxy;
        }


        std::shared_ptr<OpenHome::Net::ICpProxy> MediaServer::getConnectionManagerProxy()
        {
            return connectionManagerProxy;
        }


        void MediaServer::logServerError(std::string _error, std::string _location)
        {
            logError("MediaServer '" + getDeviceDescription() + "': " + _error, _location);
        }


        void MediaServer::onContentDirectoryProxyPropertyChanged()
        {            
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(getContentDirectoryProxy());
            // not needed
        }


        void MediaServer::oConnectionManagerProxyPropertyChanged()
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(getConnectionManagerProxy());
            // not needed
        }


        void MediaServer::onContentDirectoryProxyContainerUpdateIdsChanged()
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(getContentDirectoryProxy());
            // not needed
        }        

        
        // due to the fact that the UPNP Stack doesnt support lamdas and we ot no idea which sink called the callbak we do make a thread with async action		
        void MediaServer::search(std::string _containerId, std::string _searchCriteria, std::string _extraData, bool _sync)
        {            
            std::lock_guard<std::mutex> lock(mutexThreadList);         
            std::shared_ptr<std::thread> newThread;
            newThread = std::shared_ptr<std::thread>(new std::thread(&MediaServer::searchThread, this, _containerId, _searchCriteria, _extraData));
            threadList.emplace_back(newThread);
            if (_sync)
                newThread->join();    
        }

    
        void MediaServer::searchThread(std::string _containerId, std::string _searchCriteria, std::string _extraData)
        {          
            if (!isContentDirectoryProxyAvailable())
                return;

            try
            {
                logDebug("Search contentDirectory for " + _containerId + ": " + _searchCriteria + " on device " + UDN, CURRENT_FUNCTION);                
                searchThreadProxy(_containerId, _searchCriteria, _extraData);
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logServerError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logServerError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logServerError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logServerError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logServerError("Unknown Exception", CURRENT_FUNCTION);
            }

        }


        void MediaServer::searchThreadProxy(std::string _containerId, std::string _searchCriteria, std::string _extraData)
        {
            std::string	result = "";
            std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(getContentDirectoryProxy());        
            proxy->SyncSearch(_containerId, _searchCriteria, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
            searchThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
        }
        

        // due to the fact that the UPNP Stack doesnt support lamdas and i got no idea which sink called the callbak we do make a thread with async action
        void MediaServer::browse(std::string _containerId, MediaServer_BrowseFlag _browseFlag, std::string _extraData, bool _sync)
        {            
            std::lock_guard<std::mutex> lock(mutexThreadList);
            std::shared_ptr<std::thread> newThread;            
            newThread = std::shared_ptr<std::thread>(new std::thread(&MediaServer::browseThread, this, _containerId, _browseFlag, _extraData));
            threadList.emplace_back(newThread);
            if (_sync)
                newThread->join();
        }


        void MediaServer::browseThread(std::string _containerId, MediaServer_BrowseFlag _browseFlag, std::string _extraData)
        {
            std::string	browseFlag = "BrowseDirectChildren";            

            if (!isContentDirectoryProxyAvailable())
                return;

            try
            {
                if (_browseFlag == MediaServer_BrowseFlag::MSBF_BrowseMetadata)
                    browseFlag = "BrowseMetadata";
                logDebug("Browse contentDirectory for " + _containerId + ": " + browseFlag + " on device " + UDN, CURRENT_FUNCTION);       
                browseThreadProxy(_containerId, browseFlag, _extraData);
              
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logServerError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logServerError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logServerError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logServerError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logServerError("Unknown Exception", CURRENT_FUNCTION);
            }

        }


        void MediaServer::browseThreadProxy(std::string _containerId, std::string _browseFlag, std::string _extraData)
        {
            std::string	result = "";
            std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory1Cpp>(getContentDirectoryProxy());
            proxy->SyncBrowse(_containerId, _browseFlag, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
            browseThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
        }


        void MediaServer::searchThreadExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData)
        {
            sigSearchExecuted.fire(_result, _numberReturned, _totalMatches, _updateId, _extraData);
        }


        void MediaServer::browseThreadExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData)
        {
            sigBrowseExecuted.fire(_result, _numberReturned, _totalMatches, _updateId, _extraData);
        }


        std::string MediaServer::createAVTransportUri_Container(std::string _containerId, std::int32_t _trackIndex)
        {
            std::string uri;
            std::string containerIdUri = _containerId;

            uri = Raumkernel::Tools::UriUtil::encodeUriPart(UDN) + "?sid=" + Raumkernel::Tools::UriUtil::encodeUriPart("urn:upnp-org:serviceId:ContentDirectory") + "&cid=" + Raumkernel::Tools::UriUtil::encodeUriPart(containerIdUri) + "&md=0";
            if (_trackIndex >= 0)
                uri += "&fii=" + Raumkernel::Tools::UriUtil::encodeUriPart(std::to_string(_trackIndex));
            uri = "dlna-playcontainer://" + uri;
            // a valid transport uri looks like this!
            //dlna-playcontainer://uuid%3Aed3bd3db-17b1-4dbe-82df-5201c78e632c?sid=urn%3Aupnp-org%3AserviceId%3AContentDirectory&cid=0%2FPlaylists%2FMyPlaylists%2FTest&md=0	
            return uri;
        }


        std::string MediaServer::createAVTransportUri_Single(std::string _singleId)
        {
            std::string uri;
            std::string singleIdUri = _singleId;

            uri = Raumkernel::Tools::UriUtil::encodeUriPart(UDN) + "?sid=" + Raumkernel::Tools::UriUtil::encodeUriPart("urn:upnp-org:serviceId:ContentDirectory") + "&iid=" + Raumkernel::Tools::UriUtil::encodeUriPart(_singleId);
            uri = "dlna-playsingle://" + uri;
            // a valid transport uri looks like this!
            //dlna-playsingle://uuid%3Aed3bd3db-17b1-4dbe-82df-5201c78e632c?sid=urn%3Aupnp-org%3AserviceId%3AContentDirectory&iid=0%2FRadioTime%2FLocalRadio%2Fs-s68932
            return uri;
        }



    }
}