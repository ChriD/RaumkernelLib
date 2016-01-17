#include <raumkernel/device/deviceMediaServer_RF.h>
#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaServer_Raumfeld::MediaServer_Raumfeld() : MediaServer()
        {
        }


        MediaServer_Raumfeld::~MediaServer_Raumfeld()
        {      
        }


        void MediaServer_Raumfeld::createProxyContentDirectory()
        {
            // INFO: If the subscription fails in the OhNet Stack you may have to check the generated proxies for wrong string parameter in the constructor. eg:
            /* ProxyFile(CPP):
                    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice):CpProxy("schemas-upnp-org", "ContentDirectory_Raumfeld", 1, aDevice.Device())
                    ... should be ->
                    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice):CpProxy("schemas-upnp-org", "ContentDirectory", 1, aDevice.Device())
            */
            contentDirectoryProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(new OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(*cpDevice));
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());           
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::onContentDirectoryProxyPropertyChanged);
            OpenHome::Functor functorCUID = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::onContentDirectoryProxyContainerUpdateIdsChanged);
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->SetPropertyContainerUpdateIDsChanged(functorCUID);
            proxy->Subscribe();
        }


        void MediaServer_Raumfeld::createProxyConnectionManager()
        {
            connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp(*cpDevice));
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::oConnectionManagerProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(getConnectionManagerProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->Subscribe();
        }


        void MediaServer_Raumfeld::onContentDirectoryProxyPropertyChanged()
        {
            //auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
            // not needed
        }


        void MediaServer_Raumfeld::oConnectionManagerProxyPropertyChanged()
        {
            //auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getConnectionManagerProxy());
            // not needed
        }


        void MediaServer_Raumfeld::onContentDirectoryProxyContainerUpdateIdsChanged()
        {
            //auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
            
            /*
            // TODO: @@@
            std::string updateIds = "";

            this->Log(LogType::LOGDEBUG, "ContentDirectory on '" + this->GetIdentificationString() + "': Container Id's changed!", __FUNCTION__);

            this->GetContentDirectoryProxy()->PropertyContainerUpdateIDs(updateIds);

            managerList.contentManager->StartGetMediaItemListsByContainerUpdateIds(updateIds);
            */
        }


        void MediaServer_Raumfeld::searchThreadProxy(std::string _containerId, std::string _searchCriteria, std::string _extraData)
        {
            std::string	result = "";
            std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
            proxy->SyncSearch(_containerId, _searchCriteria, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
            searchThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
        }


        void MediaServer_Raumfeld::browseThreadProxy(std::string _containerId, std::string _browseFlag, std::string _extraData)
        {
            std::string	result = "";
            std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
            proxy->SyncBrowse(_containerId, _browseFlag, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
            browseThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
        }

    }
}