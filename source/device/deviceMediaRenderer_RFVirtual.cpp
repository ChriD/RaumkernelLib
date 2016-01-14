
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaRenderer_RaumfeldVirtual::MediaRenderer_RaumfeldVirtual() : MediaRenderer_Raumfeld()
        {          
        }

        
        MediaRenderer_RaumfeldVirtual::~MediaRenderer_RaumfeldVirtual()
        {
        }

 
        void MediaRenderer_RaumfeldVirtual::createProxyAvTransport()
        {
            avTransportProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp(*cpDevice));            
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::onAvTransportProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->SetPropertyLastChangeChanged(functor);
            proxy->Subscribe();
        }


        void MediaRenderer_RaumfeldVirtual::createProxyConnectionManager()
        {
            connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(*cpDevice));
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::oConnectionManagerProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(getConnectionManagerProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->Subscribe();
        }


        void MediaRenderer_RaumfeldVirtual::createProxyRenderingControl()
        {
            renderingControlProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(*cpDevice));
            OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::onRenderingControlProxyPropertyChanged);
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->SetPropertyInitialEvent(functor);
            proxy->SetPropertyChanged(functor);
            proxy->SetPropertyLastChangeChanged(functor);
            proxy->Subscribe();
        }


        void MediaRenderer_RaumfeldVirtual::playProxy(bool _sync)
        {         
            std::string	playSpeed = "1";

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());            

            if (_sync)
                proxy->SyncPlay(instance, playSpeed);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onPlayExecuted);
                proxy->BeginPlay(instance, playSpeed, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onPlayExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());            
            proxy->EndPlay(_aAsync);
        }
              

        void MediaRenderer_RaumfeldVirtual::stopProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncStop(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onStopExecuted);
                proxy->BeginStop(instance, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onStopExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndStop(_aAsync);
        }

       
        void MediaRenderer_RaumfeldVirtual::pauseProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncPause(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onPauseExecuted);
                proxy->BeginPause(instance, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onPauseExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndPause(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::nextProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncNext(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onNextExecuted);
                proxy->BeginNext(instance, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onNextExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndNext(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::previousProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncPrevious(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onPreviousExecuted);
                proxy->BeginPrevious(instance, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onPreviousExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndPrevious(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::seekProxy(std::string _unit, std::string _target, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncSeek(instance, _unit, _target);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSeekExecuted);
                proxy->BeginSeek(instance, _unit, _target, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSeekExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndSeek(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::setPlayModeProxy(std::string _playMode, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncSetPlayMode(instance, _playMode);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetPlayModeExecuted);
                proxy->BeginSetPlayMode(instance, _playMode, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetPlayModeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndSetPlayMode(_aAsync);
        }


        AvTransportMediaInfo MediaRenderer_RaumfeldVirtual::getMediaInfoProxy(bool _sync)
        {
            AvTransportMediaInfo mediaInfo;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

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
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetMediaInfoExecuted);
                proxy->BeginGetMediaInfo(instance, functorAsync);
            }
            return mediaInfo;
        }


        void MediaRenderer_RaumfeldVirtual::onGetMediaInfoExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportMediaInfo mediaInfo;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndGetMediaInfo(_aAsync, mediaInfo.nrTracks, mediaInfo.mediaDuration, mediaInfo.currentUri, mediaInfo.currentUriMetaData, mediaInfo.nextUri, mediaInfo.nextUriMetaData, mediaInfo.playMedium, mediaInfo.recordMedium, mediaInfo.writeStatus);
            if (mediaInfo.mediaDuration == MEDIARENDERER_NOT_IMPLEMENTED)
                mediaInfo.mediaDurationMS = 0;
            else
                mediaInfo.mediaDurationMS = Tools::StringUtil::toTimeMs(mediaInfo.mediaDuration);
            sigGetMediaInfoExecuted.fire(mediaInfo);
        }


        AvTransportPositionInfo MediaRenderer_RaumfeldVirtual::getPositionInfoProxy(bool _sync)
        {
            AvTransportPositionInfo positionInfo;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

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
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetPositionInfoExecuted);
                proxy->BeginGetMediaInfo(instance, functorAsync);
            }
            return positionInfo;
        }


        void MediaRenderer_RaumfeldVirtual::onGetPositionInfoExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportPositionInfo positionInfo;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
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


        void MediaRenderer_RaumfeldVirtual::setAvTransportUriProxy(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncSetAVTransportURI(instance, _avTransportUri, _avTransportUriMetaData);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetAvTransportUriExecuted);
                proxy->BeginSetAVTransportURI(instance, _avTransportUri, _avTransportUriMetaData, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndSetAVTransportURI(_aAsync);
        }


        AvTransportInfo MediaRenderer_RaumfeldVirtual::getTransportInfoProxy(bool _sync)
        {
            AvTransportInfo transportInfo;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
            {
                proxy->SyncGetTransportInfo(instance, transportInfo.currentTransportState, transportInfo.currentTransportStatus, transportInfo.currentSpeed);
            }
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetTransportInfoExecuted);
                proxy->BeginGetMediaInfo(instance, functorAsync);
            }
            return transportInfo;
        }


        void MediaRenderer_RaumfeldVirtual::onGetTransportInfoExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportInfo transportInfo;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndGetTransportInfo(_aAsync, transportInfo.currentTransportState, transportInfo.currentTransportStatus, transportInfo.currentSpeed);
            sigGetTransportInfoExecuted.fire(transportInfo);
        }


        AvTransportSettings MediaRenderer_RaumfeldVirtual::getTransportSettingsProxy(bool _sync)
        {
            AvTransportSettings transportSettings;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
            {
                proxy->SyncGetTransportSettings(instance, transportSettings.playMode, transportSettings.recQualityMode);
            }
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetTransportSettingsExecuted);
                proxy->BeginGetTransportInfo(instance, functorAsync);
            }
            return transportSettings;
        }


        void MediaRenderer_RaumfeldVirtual::onGetTransportSettingsExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            AvTransportSettings transportSettings;

            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndGetTransportSettings(_aAsync, transportSettings.playMode, transportSettings.recQualityMode);
            sigGetTransportSettingsExecuted.fire(transportSettings);
        }


        void MediaRenderer_RaumfeldVirtual::setMuteProxy(bool _mute, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());

            if (_sync)
                proxy->SyncSetMute(instance, MEDIARENDERER_MASTER_CHANNEL, _mute);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetMuteExecuted);
                proxy->BeginSetMute(instance, MEDIARENDERER_MASTER_CHANNEL, _mute, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndSetMute(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::setVolumeProxy(std::uint32_t _volume, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());

            if (_sync)
                proxy->SyncSetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, _volume);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetVolumeExecuted);
                proxy->BeginSetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, _volume, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndSetVolume(_aAsync);
        }


        bool MediaRenderer_RaumfeldVirtual::getMuteProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());
            bool mute = false;

            if (_sync)
                proxy->SyncGetMute(instance, MEDIARENDERER_MASTER_CHANNEL, mute);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetMuteExecuted);
                proxy->BeginGetMute(instance, MEDIARENDERER_MASTER_CHANNEL, functorAsync);
            }
            return mute;
        }


        void MediaRenderer_RaumfeldVirtual::onGetMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            bool mute;

            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndGetMute(_aAsync, mute);
            sigGetMuteExecuted.fire(mute);
        }


        std::uint32_t MediaRenderer_RaumfeldVirtual::getVolumeProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());
            std::uint32_t volume = 0;

            if (_sync)
                proxy->SyncGetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, volume);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetVolumeExecuted);
                proxy->BeginGetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, functorAsync);
            }
            return volume;
        }


        void MediaRenderer_RaumfeldVirtual::onGetVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            std::uint32_t volume = 0;

            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndGetVolume(_aAsync, volume);
            sigGetVolumeExecuted.fire(volume);
        }


        void MediaRenderer_RaumfeldVirtual::onAvTransportProxyPropertyChanged()
        {
            std::string propertyXML = "";
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->PropertyLastChange(propertyXML);
            getManagerEngineer()->getSubscriptionReceiverManager()->propertyChangedAvTransportProxy(UDN, propertyXML);
        }


        void MediaRenderer_RaumfeldVirtual::onRenderingControlProxyPropertyChanged()
        {
            std::string propertyXML = "";
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());            
            proxy->PropertyLastChange(propertyXML);
            getManagerEngineer()->getSubscriptionReceiverManager()->propertyChangedRenderingControlProxy(UDN, propertyXML);
        }


        void MediaRenderer_RaumfeldVirtual::oConnectionManagerProxyPropertyChanged()
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(getConnectionManagerProxy());
            // not needed
        }


        void MediaRenderer_RaumfeldVirtual::bendAvTransportUri(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync)
        {            
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'bendAvTransportUri' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'bendAvTransportUri' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                bendAvTransportUriProxy(_avTransportUri, _avTransportUriMetaData, _sync);
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


        void MediaRenderer_RaumfeldVirtual::bendAvTransportUriProxy(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncBendAVTransportURI(instance, _avTransportUri, _avTransportUriMetaData);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onBendAvTransportUriExecuted);
                proxy->BeginBendAVTransportURI(instance, _avTransportUri, _avTransportUriMetaData, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onBendAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndBendAVTransportURI(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::startSleepTimer(std::int16_t _instanceId, std::uint16_t _secondsUntilSleep, std::int16_t _secondsForVolumeRamp, bool _sync)
        {            
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'startSleepTimer' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'startSleepTimer' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                startSleepTimerProxy(_instanceId, _secondsUntilSleep, _secondsForVolumeRamp, _sync);
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


        void MediaRenderer_RaumfeldVirtual::startSleepTimerProxy(std::int16_t _instanceId, std::uint16_t _secondsUntilSleep, std::int16_t _secondsForVolumeRamp, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

            if (_sync)
                proxy->SyncStartSleepTimer(_instanceId, _secondsUntilSleep, _secondsForVolumeRamp);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onStartSleepTimerExecuted);
                proxy->BeginStartSleepTimer(_instanceId, _secondsUntilSleep, _secondsForVolumeRamp, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onStartSleepTimerExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
            proxy->EndStartSleepTimer(_aAsync);
        }


        void MediaRenderer_RaumfeldVirtual::setRoomMute(std::string _roomUDN, bool _mute, bool _sync)
        {            
            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'setRoomMute' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'setRoomMute' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                setRoomMuteProxy(_roomUDN, _mute, _sync);
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


        void MediaRenderer_RaumfeldVirtual::setRoomMuteProxy(std::string _roomUDN, bool _mute, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());

            if (_sync)
                proxy->SyncSetRoomMute(instance, _roomUDN, _mute);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetRoomMuteExecuted);
                proxy->BeginSetRoomMute(instance, _roomUDN, _mute, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndSetRoomMute(_aAsync);
        }


        bool MediaRenderer_RaumfeldVirtual::getRoomMute(std::string _roomUDN, bool _sync)
        {
            bool mute = false;

            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'getRoomMute' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return mute;
            }

            logDebug("Calling 'getRoomMute' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                mute = getRoomMuteProxy(_roomUDN, _sync);
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

            return mute;
        }


        bool MediaRenderer_RaumfeldVirtual::getRoomMuteProxy(std::string _roomUDN, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            bool mute = false;

            if (_sync)
                proxy->SyncGetRoomMute(instance, _roomUDN, mute);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetRoomMuteExecuted);
                proxy->BeginGetRoomMute(instance, _roomUDN, functorAsync);
            }

            return mute;
        }


        void MediaRenderer_RaumfeldVirtual::onGetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            bool mute = false;

            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndGetRoomMute(_aAsync, mute);
            sigGetRoomMuteExecuted.fire(mute);
        }


        void MediaRenderer_RaumfeldVirtual::setRoomVolume(std::string _roomUDN, std::uint32_t _volume, bool _sync)
        {
            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'setRoomVolume' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'setRoomVolume' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                setRoomVolumeProxy(_roomUDN, _volume, _sync);
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


        void MediaRenderer_RaumfeldVirtual::setRoomVolumeProxy(std::string _roomUDN, std::uint32_t _volume, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());

            if (_sync)
                proxy->SyncSetRoomVolume(instance, _roomUDN, _volume);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onSetRoomVolumeExecuted);
                proxy->BeginSetRoomVolume(instance, _roomUDN, _volume, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndSetRoomVolume(_aAsync);
        }


        std::uint32_t MediaRenderer_RaumfeldVirtual::getRoomVolume(std::string _roomUDN, bool _sync)
        {
            std::uint32_t volume;

            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'getRoomVolume' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return 0;
            }

            logDebug("Calling 'getRoomVolume' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                volume = getVolumeProxy(_sync);
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

            return volume;
        }


        std::uint32_t MediaRenderer_RaumfeldVirtual::getRoomVolumeProxy(std::string _roomUDN, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());
            std::uint32_t volume = 0;

            if (_sync)
                proxy->SyncGetRoomVolume(instance, _roomUDN, volume);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetRoomVolumeExecuted);
                proxy->BeginGetRoomVolume(instance, _roomUDN, functorAsync);
            }
            return volume;
        }


        void MediaRenderer_RaumfeldVirtual::onGetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            std::uint32_t volume = 0;

            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndGetRoomVolume(_aAsync, volume);
            sigGetRoomVolumeExecuted.fire(volume);
        }


        void MediaRenderer_RaumfeldVirtual::changeVolume(std::uint32_t _volumeDifference, bool _sync)
        {
            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'changeVolume' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'changeVolume' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                changeVolumeProxy(_volumeDifference, _sync);
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


        void MediaRenderer_RaumfeldVirtual::changeVolumeProxy(std::uint32_t _volumeDifference, bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());

            if (_sync)
                proxy->SyncChangeVolume(instance, _volumeDifference);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onChangeVolumeExecuted);
                proxy->BeginChangeVolume(instance, _volumeDifference, functorAsync);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onChangeVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isRenderingControlProxyAvailable())
                return;

            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
            proxy->EndChangeVolume(_aAsync);
        }
      
    }

}