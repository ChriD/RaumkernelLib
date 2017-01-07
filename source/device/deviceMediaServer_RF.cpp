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


        bool MediaServer_Raumfeld::isRaumfeldMediaServer()
        {
            return true;
        }


        void MediaServer_Raumfeld::createProxyContentDirectory()
        {
            // INFO: If the subscription fails in the OhNet Stack you may have to check the generated proxies for wrong string parameter in the constructor. eg:
            /* ProxyFile(CPP):
                CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice):CpProxy("schemas-upnp-org", "ContentDirectory_Raumfeld", 1, aDevice.Device())
                ... should be ->
                CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice):CpProxy("schemas-upnp-org", "ContentDirectory", 1, aDevice.Device())
                */
            try
            {
                contentDirectoryProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(new OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(*cpDevice));
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
                OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::onContentDirectoryProxyPropertyChanged);
                OpenHome::Functor functorCUID = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::onContentDirectoryProxyContainerUpdateIdsChanged);
                proxy->SetPropertyInitialEvent(functor);
                proxy->SetPropertyChanged(functor);
                proxy->SetPropertyContainerUpdateIDsChanged(functorCUID);
                proxy->Subscribe();
            }          
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logError("Unknown Exception", CURRENT_FUNCTION);
            }
        }


        void MediaServer_Raumfeld::createProxyConnectionManager()
        {
            try
            {
                connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp(*cpDevice));
                OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaServer_Raumfeld::oConnectionManagerProxyPropertyChanged);
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp>(getConnectionManagerProxy());
                proxy->SetPropertyInitialEvent(functor);
                proxy->SetPropertyChanged(functor);
                proxy->Subscribe();
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logError("Unknown Exception", CURRENT_FUNCTION);
            }
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

            // Be sure the device itself will not be emoved when doing something, so we hae to lock the devive manager list
            getManagerEngineer()->getDeviceManager()->lock();

            try
            {            
                // TODO: @@@
                std::string updateIds = "";

                logDebug("Container updated id's changed on " + getDeviceDescription(), CURRENT_POSITION);
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
                proxy->PropertyContainerUpdateIDs(updateIds);
                getManagerEngineer()->getMediaListManager()->loadMediaItemListsByContainerUpdateIds(updateIds);                                       

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logError("Unknown Exception", CURRENT_FUNCTION);
            }

            getManagerEngineer()->getDeviceManager()->unlock();

        }


        void MediaServer_Raumfeld::searchThreadProxy(std::string _containerId, std::string _searchCriteria, std::string _extraData)
        {
            // TODO:  lock device manager
            try
            {
                std::string	result = "";
                std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
                proxy->SyncSearch(_containerId, _searchCriteria, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
                searchThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
            }
            catch (OpenHome::Exception &e)
            {
                logServerError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logServerError("Unknown exception!", CURRENT_POSITION);
        }
        }


        void MediaServer_Raumfeld::browseThreadProxy(std::string _containerId, std::string _browseFlag, std::string _extraData)
        {
                // TODO:  lock device manager
            try
            {
                std::string	result = "";
                std::uint32_t numberReturned = 0, totalMatches = 0, updateId = 0;
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
                proxy->SyncBrowse(_containerId, _browseFlag, "*", 0, 0, "", result, numberReturned, totalMatches, updateId);
                browseThreadExecuted(result, numberReturned, totalMatches, updateId, _extraData);
            }
            catch (OpenHome::Exception &e)
            {
                logServerError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logServerError("Unknown exception!", CURRENT_POSITION);
            }
        }


        std::string MediaServer_Raumfeld::getShufflePlaylistId(const std::string &_shuffleContainerId, const std::string &_shuffleSelection)
        {
            std::string	playlistId, playlistMetaData;

            // TODO:  lock device manager

            try
            {                            
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp>(getContentDirectoryProxy());
                proxy->SyncShuffle(_shuffleContainerId, _shuffleSelection, playlistId, playlistMetaData);               
            }
            catch (OpenHome::Exception &e)
            {
                logServerError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logServerError("Unknown exception!", CURRENT_POSITION);
            }
            return playlistId;
        }

    }
}