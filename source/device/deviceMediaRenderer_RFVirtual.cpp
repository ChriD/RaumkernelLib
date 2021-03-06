
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaRenderer_RaumfeldVirtual::MediaRenderer_RaumfeldVirtual() : MediaRenderer_Raumfeld()
        {   
            stopFadeToVolumeThread = false;
        }


        bool MediaRenderer_RaumfeldVirtual::isZoneRenderer()
        {
            return true;
        }


        std::string MediaRenderer_RaumfeldVirtual::getName()
        {
            std::string rendererName;
            //getManagerEngineer()->getZoneManager()->lock();
            try
            {
                auto zoneInfoMap = managerEngineer->getZoneManager()->getZoneInformationMap();
                if (zoneInfoMap.find(UDN) != zoneInfoMap.end())
                {
                    rendererName = zoneInfoMap[UDN].name;
                }
            }
            catch (...)
            {
            }
            //getManagerEngineer()->getZoneManager()->unlock();
            return rendererName;
        }
        

        MediaRenderer_RaumfeldVirtual::~MediaRenderer_RaumfeldVirtual()
        {
            stopFadeToVolumeThread = true;
            if (fadeToVolumeThreadObject.joinable())
            {                
                logDebug("Waiting for fadeToVolume threads to finish (This may take some time...)", CURRENT_POSITION);
                fadeToVolumeThreadObject.join();
            }
        }

 
        void MediaRenderer_RaumfeldVirtual::createProxyAvTransport()
        {
            try
            {
                avTransportProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp(*cpDevice));            
                OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::onAvTransportProxyPropertyChanged);
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->SetPropertyInitialEvent(functor);
                proxy->SetPropertyChanged(functor);
                proxy->SetPropertyLastChangeChanged(functor);
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


        void MediaRenderer_RaumfeldVirtual::createProxyConnectionManager()
        {
            try
            {
                connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(*cpDevice));
                OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::oConnectionManagerProxyPropertyChanged);
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(getConnectionManagerProxy());
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


        void MediaRenderer_RaumfeldVirtual::createProxyRenderingControl()
        {
            try
            {
                renderingControlProxy = std::shared_ptr<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(new OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(*cpDevice));
                OpenHome::Functor functor = OpenHome::MakeFunctor(*this, &MediaRenderer_RaumfeldVirtual::onRenderingControlProxyPropertyChanged);
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->SetPropertyInitialEvent(functor);
                proxy->SetPropertyChanged(functor);
                proxy->SetPropertyLastChangeChanged(functor);
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());            
                proxy->EndPlay(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onPlayExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndStop(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onStopExecuted]", CURRENT_POSITION);
        }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndPause(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onPauseExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndNext(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onNextExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndPrevious(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onPreviousExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndSeek(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSeekExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndSetPlayMode(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetPlayModeExecuted]", CURRENT_POSITION);
            }
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetMediaInfoExecuted]", CURRENT_POSITION);
            }
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetPositionInfoExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndSetAVTransportURI(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetAvTransportUriExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                AvTransportInfo transportInfo;

                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndGetTransportInfo(_aAsync, transportInfo.currentTransportState, transportInfo.currentTransportStatus, transportInfo.currentSpeed);
                sigGetTransportInfoExecuted.fire(transportInfo);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetTransportInfoExecuted]", CURRENT_POSITION);
        }
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
            try
            {
                AvTransportSettings transportSettings;

                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndGetTransportSettings(_aAsync, transportSettings.playMode, transportSettings.recQualityMode);
                sigGetTransportSettingsExecuted.fire(transportSettings);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetTransportSettingsExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndSetMute(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetMuteExecuted]", CURRENT_POSITION);
        }
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
            try
            {
                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndSetVolume(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetVolumeExecuted]", CURRENT_POSITION);
            }
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
            try
            {
                bool mute = false;

                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndGetMute(_aAsync, mute);
                sigGetMuteExecuted.fire(mute);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetMuteExecuted]", CURRENT_POSITION);
            }
        }


        std::uint32_t MediaRenderer_RaumfeldVirtual::getVolumeProxy(bool _sync)
        {
            std::uint32_t volume = 0;
            try
            {
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp >(getRenderingControlProxy());                
                if (_sync)
                    proxy->SyncGetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, volume);
                else
                {
                    OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetVolumeExecuted);
                    proxy->BeginGetVolume(instance, MEDIARENDERER_MASTER_CHANNEL, functorAsync);
                }
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }

            return volume;
        }


        void MediaRenderer_RaumfeldVirtual::onGetVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                std::uint32_t volume = 0;

                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndGetVolume(_aAsync, volume);
                sigGetVolumeExecuted.fire(volume);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetVolumeExecuted]", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onAvTransportProxyPropertyChanged()
        {
            try
            {
                std::string propertyXML = "";
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->PropertyLastChange(propertyXML);            
            
                // lock the device list to be sure the "this" object will not be deleted while parsing event subscriptions
                getManagerEngineer()->getDeviceManager()->lock();
                getManagerEngineer()->getZoneManager()->lock();

                // parse the event subscription xml, the object will fill the appropriate structure for the given renderer object
                EventParser::DeviceEventParserMediaRenderer eventParser;
                eventParser.setLogObject(getLogObject());
                eventParser.setManagerEngineer(getManagerEngineer());
                eventParser.setDevice(this);
                eventParser.propertyChangedAvTransportProxy(propertyXML);

                getManagerEngineer()->getZoneManager()->unlock();
                getManagerEngineer()->getDeviceManager()->unlock();
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onAvTransportProxyPropertyChanged]", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onRenderingControlProxyPropertyChanged()
        {
            try
            {
                std::string propertyXML = "";
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->PropertyLastChange(propertyXML);

                // lock the device list to be sure the "this" object will not be deleted while parsing event subscriptions
                getManagerEngineer()->getDeviceManager()->lock();
                getManagerEngineer()->getZoneManager()->lock();

                // parse the event subscription xml, the object will fill the appropriate structure for the given renderer object
                EventParser::DeviceEventParserMediaRenderer eventParser;
                eventParser.setLogObject(getLogObject());
                eventParser.setManagerEngineer(getManagerEngineer());
                eventParser.setDevice(this);
                eventParser.propertyChangedRenderingControlProxy(propertyXML);

                getManagerEngineer()->getZoneManager()->unlock();
                getManagerEngineer()->getDeviceManager()->unlock();
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onRenderingControlProxyPropertyChanged]", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::oConnectionManagerProxyPropertyChanged()
        {
            try
            {
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp>(getConnectionManagerProxy());
                // not needed
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::oConnectionManagerProxyPropertyChanged]", CURRENT_POSITION);
            }
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onBendAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndBendAVTransportURI(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onBendAvTransportUriExecuted]", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::startSleepTimer(std::uint16_t _secondsUntilSleep, std::int16_t _secondsForVolumeRamp, bool _sync)
        {            
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'startSleepTimer' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'startSleepTimer' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                startSleepTimerProxy(instance, _secondsUntilSleep, _secondsForVolumeRamp, _sync);
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onStartSleepTimerExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndStartSleepTimer(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onStartSleepTimerExecuted]", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::cancelSleepTimer(bool _sync)
        {
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'cancelSleepTimer' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'cancelSleepTimer' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                cancelSleepTimerProxy(instance, _sync);
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


        void MediaRenderer_RaumfeldVirtual::cancelSleepTimerProxy(std::int16_t _instanceId, bool _sync)
        {
            try
            {
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());

                if (_sync)
                    proxy->SyncCancelSleepTimer(_instanceId);
                else
                {
                    OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onCancelSleepTimerExecuted);
                    proxy->BeginCancelSleepTimer(_instanceId, functorAsync);
                }
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onCancelSleepTimerExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp>(getAvTransportProxy());
                proxy->EndCancelSleepTimer(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onCancelSleepTimerExecuted]", CURRENT_POSITION);
            }
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }



        void MediaRenderer_RaumfeldVirtual::onSetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndSetRoomMute(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetRoomMuteExecuted]", CURRENT_POSITION);
            }
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
            bool mute = false;
            try
            {
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());                
                if (_sync)
                    proxy->SyncGetRoomMute(instance, _roomUDN, mute);
                else
                {
                    OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_RaumfeldVirtual::onGetRoomMuteExecuted);
                    proxy->BeginGetRoomMute(instance, _roomUDN, functorAsync);
                }
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }

            return mute;
        }


        void MediaRenderer_RaumfeldVirtual::onGetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                bool mute = false;

                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndGetRoomMute(_aAsync, mute);
                sigGetRoomMuteExecuted.fire(mute);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetRoomMuteExecuted]", CURRENT_POSITION);
            }
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
                if (_volume > 100)
                {
                    logWarning("Volume has reached it's upper boundaries and will be set to 100", CURRENT_FUNCTION);
                    _volume = 100;
                }       

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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onSetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndSetRoomVolume(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onSetRoomVolumeExecuted]", CURRENT_POSITION);
        }
        }


        std::uint32_t MediaRenderer_RaumfeldVirtual::getRoomVolume(std::string _roomUDN, bool _sync)
        {
            std::uint32_t volume = 0;

            if (!isRenderingControlProxyAvailable())
            {
                logWarning("Calling 'getRoomVolume' on renderer '" + getDeviceDescription() + "' without RenderingControlProxy!", CURRENT_FUNCTION);
                return 0;
            }

            logDebug("Calling 'getRoomVolume' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                volume = getRoomVolumeProxy(_roomUDN, _sync);
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
            return 0;
        }


        void MediaRenderer_RaumfeldVirtual::onGetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                std::uint32_t volume = 0;

                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndGetRoomVolume(_aAsync, volume);
                sigGetRoomVolumeExecuted.fire(volume);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onGetRoomVolumeExecuted]", CURRENT_POSITION);
            }
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
            try
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
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


        void MediaRenderer_RaumfeldVirtual::onChangeVolumeExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            try
            {
                if (!isRenderingControlProxyAvailable())
                    return;

                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp>(getRenderingControlProxy());
                proxy->EndChangeVolume(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception![MediaRenderer_RaumfeldVirtual::onChangeVolumeExecuted]", CURRENT_POSITION);
            }
        }



        void MediaRenderer_RaumfeldVirtual::loadPlaylist(const std::string &_playlistName, const std::uint32_t &_trackIndex, bool _sync)
        {
            logDebug("Calling 'loadPlaylist' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);                 
            loadContainer("0/Playlists/MyPlaylists/" + Tools::UriUtil::encodeValue(_playlistName), _trackIndex, _sync);
        }
                           

        void MediaRenderer_RaumfeldVirtual::loadContainer(const std::string &_containerId, const std::uint32_t &_trackIndex, bool _sync)
        {
            logDebug("Calling 'loadContainer' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);            
            auto mediaServer = getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer();
            auto uri = Tools::UriUtil::createAVTransportUriForContainer(mediaServer->getUDN(), _containerId, _trackIndex);
            // stop the playback on the renderer
            stop(true);
            // TODO: We do have no uri metadata, don't know if this will be a problem i have to check!         
            bendAvTransportUri(uri, "", _sync);
        }
       

        void MediaRenderer_RaumfeldVirtual::loadSingle(const std::string &_singleId, bool _sync)
        {
            logDebug("Calling 'loadSingle' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);              
            auto mediaServer = getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer();
            auto uri = Tools::UriUtil::createAVTransportUriForSingle(mediaServer->getUDN(), _singleId);
            // stop the playback on the renderer
            stop(true);
            // TODO: We do have no uri metadata, don't know if this will be a problem i have to check!         
            setAvTransportUri(uri, "", _sync);
        }
        
        
        void MediaRenderer_RaumfeldVirtual::loadUri(const std::string &_uri, bool _sync)
        {
            logDebug("Calling 'loadUri' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);            
            // stop the playback on the renderer
            stop(true);
            
            // TODO: the uri may be a *.pls file or any other file and not a direct link.
            // In the future we may support those lists

            // TODO: maybe load the metadata from the uri and provide it?!

            // TODO: We do have no uri metadata, don't know if this will be a problem i have to check!         
            setAvTransportUri(_uri, "", _sync);
        }


        std::string MediaRenderer_RaumfeldVirtual::loadShuffle(const std::string &_shuffleContainerId, const std::string &_shuffleSelection)
        {            
            auto mediaServer = getManagerEngineer()->getDeviceManager()->getRaumfeldMediaServer();
            if (mediaServer)
            {
                auto shufflePlaylistId = mediaServer->getShufflePlaylistId(_shuffleContainerId, _shuffleSelection);
                if (!shufflePlaylistId.empty())
                    loadContainer(shufflePlaylistId);          
                return shufflePlaylistId;
            }            
            return "";
        }


        void MediaRenderer_RaumfeldVirtual::fadeToVolume(const std::uint32_t _volume, std::uint32_t _duration, bool _sync)
        {
            logDebug("Calling 'fadeToVolume' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);         

            // check if the thread for fading is already running. If so we stop it an recreate a new one
            if (fadeToVolumeThreadObject.joinable())
            {
                stopFadeToVolumeThread = true;                
                fadeToVolumeThreadObject.join();
            }
            stopFadeToVolumeThread = false;

            // now after we are sure there is no fading thread anymore we can start the new one which will do our work
            logDebug("Starting fadeToVolume thread", CURRENT_POSITION);
            fadeToVolumeThreadObject = std::thread(&MediaRenderer_RaumfeldVirtual::fadeToVolumeThread, this, _volume, _duration);
            if (_sync)
                fadeToVolumeThreadObject.join();
        }


        void MediaRenderer_RaumfeldVirtual::fadeToVolumeThread(const std::uint32_t &_volume, const std::uint32_t &_duration)
        {
            std::uint32_t waitTime = 25;
            std::uint32_t currentGap = 0;            

            std::uint32_t currentVolume = getVolume(true);
            std::int32_t volumeDiff = _volume - currentVolume;

            // if there is no volume difference we have to do nothing and we skip
            if (volumeDiff == 0)
                return;
            
            // calculate the time gap when we do have to update the volume
            std::double_t volumeChangeGap = _duration / std::abs(volumeDiff);

            while (!stopFadeToVolumeThread && _volume != currentVolume)
            {
                try
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));  
                    currentGap += waitTime;
                    if (currentGap >= volumeChangeGap)
                    {
                        if (volumeDiff > 0)
                            currentVolume++;
                        else
                            currentVolume--;

                        setVolume(currentVolume, false);

                        currentGap = 0;
                    }
                }
                catch (Raumkernel::Exception::RaumkernelException &e)
                {
                    if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                        throw e;
                }
                catch (std::exception &e)
                {
                    logRendererError(e.what(), CURRENT_POSITION);
                }
                catch (std::string &e)
                {
                    logRendererError(e, CURRENT_POSITION);
                }
                catch (OpenHome::Exception &e)
                {
                    logRendererError(e.Message(), CURRENT_POSITION);;
                }
                catch (...)
                {
                    logRendererError("Unknown exception!", CURRENT_POSITION);
                }
            }
        }

      
    }


}