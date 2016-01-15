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


        std::shared_ptr<OpenHome::Net::CpProxy> MediaServer::getContentDirectoryProxy()
        {
            return contentDirectoryProxy;
        }


        std::shared_ptr<OpenHome::Net::CpProxy> MediaServer::getConnectionManagerProxy()
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


    }
}