
#include <raumkernel/device/deviceMediaRenderer.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaRenderer::MediaRenderer() : Device()
        {
            avTransportProxy = nullptr;
            renderingControlProxy = nullptr;
            connectionManagerProxy = nullptr;
        }

        
        MediaRenderer::~MediaRenderer()
        {
            // no need to remove subscriptions! delete of proxies will handle this correct!
            this->deleteProxies();
        }


        void MediaRenderer::deleteProxies()
        {
            // due the proxies are shared pointers we can set them to nullptr instead of deleteing them first
            // n fact its not best practice to force shared pointers to 'nullptr' but in our case the MediaRenderer 
            // class may be existent without the proxies (for a short time)
            avTransportProxy = nullptr;
            renderingControlProxy = nullptr;
            connectionManagerProxy = nullptr;
        }


        void MediaRenderer::createProxies()
        {
            if (!cpDevice)
            {
                logWarning("Calling 'createProxies' on renderer " + this->getDeviceDescription() + " without cpDevice!", CURRENT_POSITION);
                this->deleteProxies();
                return;
            }

            // create standard proxies for the common media renderes
            if (!avTransportProxy)
            {
                logDebug("Create AVTransport-Proxy for media renderer " + this->getDeviceDescription(), CURRENT_POSITION);
                createProxyAvTransport();
            }
   
            if (!renderingControlProxy)
            {
                logDebug("Create RenderingControl-Proxy for media renderer " + this->getDeviceDescription(), CURRENT_POSITION);
                createProxyRenderingControl();
            }

            if (!connectionManagerProxy)	
            {
                logDebug("Create ConnectionManager-Proxy for media renderer " + this->getDeviceDescription(), CURRENT_POSITION);
                createProxyConnectionManager();
            }

        }


        void MediaRenderer::createProxyAvTransport()
        {
            avTransportProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp(*cpDevice));
        }


        void MediaRenderer::createProxyConnectionManager()
        {
            connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager1Cpp(*cpDevice));
        }


        void MediaRenderer::createProxyRenderingControl()
        {
            renderingControlProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgRenderingControl1Cpp(*cpDevice));
        }


        bool MediaRenderer::isRenderingProxyAvailable()
        {
            if (!cpDevice)            
                return false;            
            if (!renderingControlProxy)
                return false;
            return true;
        }


        bool MediaRenderer::isConnectionManagerProxyAvailable()
        {
            if (!cpDevice)
                return false;
            if (!connectionManagerProxy)
                return false;
            return true;
        }


        bool MediaRenderer::isAvTransportProxyAvailable()
        {
            if (!cpDevice)
                return false;
            if (!avTransportProxy)
                return false;
            return true;
        }


        std::shared_ptr<OpenHome::Net::CpProxy> MediaRenderer::getAvTransportProxy()
        {      
            return avTransportProxy;
        }


        std::shared_ptr<OpenHome::Net::CpProxy> MediaRenderer::getConnectionManagerProxy()
        {
            return connectionManagerProxy;
        }


        std::shared_ptr<OpenHome::Net::CpProxy> MediaRenderer::getRenderingControlProxy()
        {
            return renderingControlProxy;
        }


        void MediaRenderer::logRendererError(std::string _error, std::string _location)
        {
            logError("Renderer '" + getDeviceDescription() + "': " + _error, _location);
        }


        void MediaRenderer::callAvTransportProxyAction(std::string _action, bool _sync)
        {
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling '" + _action  + "' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling '" + _action + "' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                if (_action == "play") playProxy(_sync);
                if (_action == "pause") pauseProxy(_sync);
                if (_action == "stop") stopProxy(_sync);
                if (_action == "next") nextProxy(_sync);
                if (_action == "previous") previousProxy(_sync);
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logRendererError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logRendererError("Unknown Exception", CURRENT_FUNCTION);
            }
        }


        void MediaRenderer::play(bool _sync)
        {                         
            callAvTransportProxyAction("play", _sync);
        }


        void MediaRenderer::playProxy(bool _sync)
        {     
            std::string	playSpeed = "1";
          
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncPlay(instance, playSpeed);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onPlayExecuted);
                proxy->BeginPlay(instance, playSpeed, functorAsync);
            }
        }


        void MediaRenderer::onPlayExecuted(OpenHome::Net::IAsync& _aAsync)
        {      
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndPlay(_aAsync);
        }


        void MediaRenderer::stop(bool _sync)
        {

            callAvTransportProxyAction("stop", _sync);
        }


        void MediaRenderer::stopProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            
            if (_sync)
                proxy->SyncStop(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onStopExecuted);
                proxy->BeginStop(instance, functorAsync);
            }
        }


        void MediaRenderer::onStopExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndStop(_aAsync);
        }


        void MediaRenderer::pause(bool _sync)
        {
            callAvTransportProxyAction("pause", _sync);
        }

        void MediaRenderer::pauseProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncPause(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onPauseExecuted);
                proxy->BeginPause(instance, functorAsync);
            }
        }


        void MediaRenderer::onPauseExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndPause(_aAsync);
        }


        void MediaRenderer::next(bool _sync)
        {
            callAvTransportProxyAction("next", _sync);
        }


        void MediaRenderer::nextProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncNext(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onNextExecuted);
                proxy->BeginNext(instance, functorAsync);
            }
        }


        void MediaRenderer::onNextExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndNext(_aAsync);
        }


        void MediaRenderer::previous(bool _sync)
        {
            callAvTransportProxyAction("previous", _sync);
        }


        void MediaRenderer::previousProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncPrevious(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onPreviousExecuted);
                proxy->BeginPrevious(instance, functorAsync);
            }
        }


        void MediaRenderer::onPreviousExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndPrevious(_aAsync);
        }
       
    }

}