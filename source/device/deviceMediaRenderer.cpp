
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


        void MediaRenderer::seek(MediaRenderer_Seek _seekType, std::uint32_t _seekToMsOrTrack, bool _sync)
        {
            std::string seekUnit, seekTarget;
         
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'seek' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'seek' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            switch (_seekType)
            {
                case MediaRenderer_Seek::MRSEEK_ABS_TIME: seekUnit = "ABS_TIME"; break;
                case MediaRenderer_Seek::MRSEEK_REL_TIME: seekUnit = "REL_TIME"; break;
                case MediaRenderer_Seek::MRSEEK_TRACK_NR: seekUnit = "TRACK_NR"; break;
                default: logError("Wrong seek type!", CURRENT_POSITION); return;
            }


            if (_seekType == MediaRenderer_Seek::MRSEEK_TRACK_NR)
            {
                seekTarget = std::to_string(_seekToMsOrTrack);
            }
            else
            {
                char buffer[30];
                time_t timeToSeek(_seekToMsOrTrack / 1000);
                tm *timeStruct = gmtime(&timeToSeek);
                if (strftime(buffer, sizeof(buffer), "%H:%M:%S", timeStruct) == 0)
                {
                    logError("'seek' for renderer '" + getDeviceDescription() + "' Time: '" + std::to_string(_seekToMsOrTrack) + "' failed!", CURRENT_POSITION);
                    return;
                }
                seekTarget = buffer;
            }

            try
            {
                seekProxy(seekUnit, seekTarget, _sync);
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


        void MediaRenderer::seekProxy(std::string _unit, std::string _target, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
           
            if (_sync)
                proxy->SyncSeek(instance, _unit, _target);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onSeekExecuted);
                proxy->BeginSeek(instance, _unit, _target, functorAsync);
            }
        }


        void MediaRenderer::onSeekExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndSeek(_aAsync);
        }


        void MediaRenderer::setPlayMode(MediaRenderer_PlayMode _playMode, bool _sync)
        {
            std::string playMode;

            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'setPlayMode' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'setPlayMode' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            playMode = ConversionTool::playModeToString(_playMode);
          
            try
            {
                setPlayModeProxy(playMode, _sync);
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


        void MediaRenderer::setPlayModeProxy(std::string _playMode, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncSetPlayMode(instance, _playMode);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onSetPlayModeExecuted);
                proxy->BeginSetPlayMode(instance, _playMode, functorAsync);
            }
        }


        void MediaRenderer::onSetPlayModeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndSetPlayMode(_aAsync);
        }


        AvTransportMediaInfo MediaRenderer::getMediaInfo(bool _sync)
        {         
            AvTransportMediaInfo        mediaInfo;

            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'getMediaInfo' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return mediaInfo;
            }

            logDebug("Calling 'getMediaInfo' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);
           

            try
            {
                mediaInfo = getMediaInfoProxy(_sync);
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

            return mediaInfo;

        }


        AvTransportMediaInfo MediaRenderer::getMediaInfoProxy(bool _sync)
        {
            AvTransportMediaInfo mediaInfo;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
            {
                proxy->SyncGetMediaInfo(instance, mediaInfo.nrTracks, mediaInfo.mediaDuration, mediaInfo.currentUri, mediaInfo.currentUriMetaData, mediaInfo.nextUri, mediaInfo.nextUriMetaData, mediaInfo.playMedium, mediaInfo.recordMedium, mediaInfo.writeStatus);
                if (mediaInfo.mediaDuration == MEDIARENDERER_NOT_IMPLEMENTED)
                    mediaInfo.mediaDurationMS = 0;
                else
                    mediaInfo.mediaDurationMS = Tools::StringUtil::toTimeMs(mediaInfo.mediaDuration);
            }
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onGetMediaInfoExecuted);
                proxy->BeginGetMediaInfo(instance, functorAsync);
            }
            return mediaInfo;
        }


        void MediaRenderer::onGetMediaInfoExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportMediaInfo mediaInfo;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());            
            proxy->EndGetMediaInfo(_aAsync, mediaInfo.nrTracks, mediaInfo.mediaDuration, mediaInfo.currentUri, mediaInfo.currentUriMetaData, mediaInfo.nextUri, mediaInfo.nextUriMetaData, mediaInfo.playMedium, mediaInfo.recordMedium, mediaInfo.writeStatus);
            if (mediaInfo.mediaDuration == MEDIARENDERER_NOT_IMPLEMENTED)
                mediaInfo.mediaDurationMS = 0;
            else
                mediaInfo.mediaDurationMS = Tools::StringUtil::toTimeMs(mediaInfo.mediaDuration);
            sigGetMediaInfoExecuted.fire(mediaInfo);
        }



        AvTransportPositionInfo MediaRenderer::getPositionInfo(bool _sync)
        {
            AvTransportPositionInfo        positionInfo;

            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'getPositionInfo' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return positionInfo;
            }

            logDebug("Calling 'getPositionInfo' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);


            try
            {
                positionInfo = getPositionInfoProxy(_sync);
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

            return positionInfo;

        }


        AvTransportPositionInfo MediaRenderer::getPositionInfoProxy(bool _sync)
        {
            AvTransportPositionInfo positionInfo;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());

            if (_sync)
            {
                proxy->SyncGetPositionInfo(instance, positionInfo.track, positionInfo.trackDuration, positionInfo.trackMetaData, positionInfo.trackUri, positionInfo.relTime, positionInfo.absTime, positionInfo.relCount, positionInfo.absCount);                
                positionInfo.absTimeMS = Tools::StringUtil::toTimeMs(positionInfo.absTime);
                positionInfo.relTimeMS = Tools::StringUtil::toTimeMs(positionInfo.relTime);
                positionInfo.trackDurationMS = Tools::StringUtil::toTimeMs(positionInfo.trackDuration);

                if (positionInfo.absTime == MEDIARENDERER_NOT_IMPLEMENTED)
                    positionInfo.absTimeMS = 0;
                if (positionInfo.relTime == MEDIARENDERER_NOT_IMPLEMENTED)
                    positionInfo.relTimeMS = 0;
                if (positionInfo.trackDuration == MEDIARENDERER_NOT_IMPLEMENTED)
                    positionInfo.trackDurationMS = 0;
               
            }
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer::onGetPositionInfoExecuted);
                proxy->BeginGetMediaInfo(instance, functorAsync);
            }
            return positionInfo;
        }


        void MediaRenderer::onGetPositionInfoExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportPositionInfo positionInfo;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndGetPositionInfo(_aAsync, positionInfo.track, positionInfo.trackDuration, positionInfo.trackMetaData, positionInfo.trackUri, positionInfo.relTime, positionInfo.absTime, positionInfo.relCount, positionInfo.absCount);
            positionInfo.absTimeMS = Tools::StringUtil::toTimeMs(positionInfo.absTime);
            positionInfo.relTimeMS = Tools::StringUtil::toTimeMs(positionInfo.relTime);
            positionInfo.trackDurationMS = Tools::StringUtil::toTimeMs(positionInfo.trackDuration);

            if (positionInfo.absTime == MEDIARENDERER_NOT_IMPLEMENTED)
                positionInfo.absTimeMS = 0;
            if (positionInfo.relTime == MEDIARENDERER_NOT_IMPLEMENTED)
                positionInfo.relTimeMS = 0;
            if (positionInfo.trackDuration == MEDIARENDERER_NOT_IMPLEMENTED)
                positionInfo.trackDurationMS = 0;

            sigGetPositionInfoExecuted.fire(positionInfo);
        }
       
    }

}