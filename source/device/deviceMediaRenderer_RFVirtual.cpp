
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>


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
            avTransportProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp(*cpDevice));
        }


        void MediaRenderer_RaumfeldVirtual::createProxyConnectionManager()
        {
            connectionManagerProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(*cpDevice));
        }


        void MediaRenderer_RaumfeldVirtual::createProxyRenderingControl()
        {
            renderingControlProxy = std::shared_ptr<OpenHome::Net::CpProxy>(new OpenHome::Net::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(*cpDevice));
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

      
    }

}