//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_DEVICEMEDIARENDERER_H
#define RAUMKERNEL_DEVICEMEDIARENDERER_H

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpProxy.h>
#include <raumkernel/device/device.h>
#include <raumkernel/device/proxies/CpUpnpOrgAVTransport1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager1.h>
#include <raumkernel/device/proxies/CpUpnpOrgRenderingControl1.h>


namespace Raumkernel
{
    namespace Devices
    {
        enum class MediaRendererPlayMode { MRPLAYMODE_NORMAL = 0, MRPLAYMODE_SHUFFLE = 1, MRPLAYMODE_REPEAT_ONE = 2, MRPLAYMODE_REPEAT_ALL = 3, MRPLAYMODE_RANDOM = 4, MRPLAYMODE_DIRECT_1 = 5, MRPLAYMODE_INTRO = 6 };
        enum class MediaRendererMuteState { MRPMUTE_NONE, MRPMUTE_ALL, MRPMUTE_PARTIAL };
        enum class MediaRendererTransportState { MRTS_STOPPED, MRTS_PLAYING, MRTS_TRANSITIONING };


        struct AvTransportMediaInfo
        {
            std::uint32_t nrTracks;
            std::string mediaDuration;
            std::uint32_t mediaDurationMS;
            std::string currentUri;
            std::string currentUriMetaData;
            std::string nextUri;
            std::string nextUriMetaData;
            std::string playMedium;
            std::string recordMedium;
            std::string writeStatus;
        };


        struct AvTransportPositionInfo
        {
            std::uint32_t track;
            std::string trackDuration;
            std::uint32_t trackDurationMS;
            std::string trackMetaData;
            std::string trackUri;
            std::string relTime;
            std::uint32_t relTimeMS;
            std::string absTime;
            std::uint32_t absTimeMS;
            std::uint32_t relCount;
            std::uint32_t absCount;
        };


        struct MediaRendererState
        {
            MediaRendererMuteState muteState;
            MediaRendererTransportState transportState;
            std::uint8_t volume;
            std::uint32_t currentTrack;
            std::uint32_t numberOfTracks;
            std::string aVTransportURI;
            std::string aVTransportURIMetaData;
            std::string currentTrackURI;
            std::string currentTrackMetaData;
            std::string containerId;
            std::string currentTrackDuration;
            std::uint32_t currentTrackDurationMS;
            std::string contentType;
            std::uint32_t bitrate;
        };


        class MediaRenderer : public Device
        {
            public:
                MediaRenderer();
                virtual ~MediaRenderer();

                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                virtual void play(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                virtual void stop(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                virtual void pause(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                virtual void next(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                virtual void previous(bool _sync = true);

                /*
                EXPORT virtual void seek(boost::int32_t _seekToMs, bool _sync = true);
                EXPORT virtual void setPlayMode(MediaRendererPlayMode _playMode, bool _sync = true);
                EXPORT virtual AvTransportMediaInfo getMediaInfo();
                EXPORT virtual AvTransportPositionInfo getPositionInfo();

                // basic media renderer functions
                EXPORT virtual void setMute(bool _mute, bool _sync = true);
                EXPORT virtual void setVolume(boost::uint8_t _volume, bool _sync = true);
                EXPORT virtual void setRoomMute(std::string _roomUDN, bool _mute, bool _sync = true);
                EXPORT virtual void setRoomVolume(std::string _roomUDN, boost::uint8_t _volume, bool _sync = true);
                EXPORT virtual void changeVolume(boost::int8_t _amount, bool _sync = true);

                EXPORT virtual bool getMute();
                EXPORT virtual boost::uint8_t getVolume();
                EXPORT virtual bool getRoomMute(std::string _roomUDN);
                EXPORT virtual boost::uint8_t  getRoomVolume(std::string _roomUDN);
                */

                EXPORT bool isRenderingProxyAvailable();
                EXPORT bool isConnectionManagerProxyAvailable();
                EXPORT bool isAvTransportProxyAvailable();

                EXPORT std::shared_ptr<OpenHome::Net::CpProxy> getAvTransportProxy();
                EXPORT std::shared_ptr<OpenHome::Net::CpProxy> getConnectionManagerProxy();
                EXPORT std::shared_ptr<OpenHome::Net::CpProxy> getRenderingControlProxy();

            protected:
                // proxies of the media renderer device
                std::shared_ptr<OpenHome::Net::CpProxy> avTransportProxy;
                std::shared_ptr<OpenHome::Net::CpProxy>	renderingControlProxy;
                std::shared_ptr<OpenHome::Net::CpProxy>	connectionManagerProxy;

                std::uint32_t instance = 0;

                virtual void deleteProxies() override;
                virtual void createProxies() override;

                virtual void createProxyAvTransport();
                virtual void createProxyConnectionManager();
                virtual void createProxyRenderingControl();

                virtual void callAvTransportProxyAction(std::string _action, bool _sync = true);

                virtual void playProxy(bool _sync = true);
                virtual void stopProxy(bool _sync = true);
                virtual void pauseProxy(bool _sync = true);
                virtual void nextProxy(bool _sync = true);
                virtual void previousProxy(bool _sync = true);

                virtual void onPlayExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onStopExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPauseExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onNextExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPreviousExecuted(OpenHome::Net::IAsync& _aAsync);
           

                void logRendererError(std::string _error, std::string _location);
        };

    }

}


#endif
