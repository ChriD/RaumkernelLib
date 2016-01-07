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
        enum class MediaRenderer_PlayMode { MRPLAYMODE_NORMAL = 0, MRPLAYMODE_SHUFFLE = 1, MRPLAYMODE_REPEAT_ONE = 2, MRPLAYMODE_REPEAT_ALL = 3, MRPLAYMODE_RANDOM = 4, MRPLAYMODE_DIRECT_1 = 5, MRPLAYMODE_INTRO = 6 };
        enum class MediaRenderer_MuteState { MRPMUTE_NONE, MRPMUTE_ALL, MRPMUTE_PARTIAL };
        enum class MediaRenderer_TransportState { MRTS_STOPPED, MRTS_PLAYING, MRTS_TRANSITIONING };
        enum class MediaRenderer_Seek { MRSEEK_ABS_TIME, MRSEEK_REL_TIME, MRSEEK_TRACK_NR };


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
            MediaRenderer_MuteState muteState;
            MediaRenderer_TransportState transportState;
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


        class ConversionTool
        {
            public:
                static std::string playModeToString(MediaRenderer_PlayMode _playMode)
                {
                    switch (_playMode)
                    {
                    case MediaRenderer_PlayMode::MRPLAYMODE_NORMAL:
                        return "NORMAL";
                    case MediaRenderer_PlayMode::MRPLAYMODE_SHUFFLE:
                        return "SHUFFLE";
                    case MediaRenderer_PlayMode::MRPLAYMODE_RANDOM:
                        return "RANDOM";
                    case MediaRenderer_PlayMode::MRPLAYMODE_REPEAT_ONE:
                        return "REPEAT_ONE";
                    case MediaRenderer_PlayMode::MRPLAYMODE_REPEAT_ALL:
                        return "REPEAT_ALL";
                    case MediaRenderer_PlayMode::MRPLAYMODE_DIRECT_1:
                        return "DIRECT_1";
                    case MediaRenderer_PlayMode::MRPLAYMODE_INTRO:
                        return "INTRO";
                    }
                    return "NORMAL";
                }

                static MediaRenderer_PlayMode stringToPlayMode(std::string _playModeString)
                {
                    if (_playModeString == "NORMAL")
                        return MediaRenderer_PlayMode::MRPLAYMODE_NORMAL;
                    if (_playModeString == "SHUFFLE")
                        return MediaRenderer_PlayMode::MRPLAYMODE_SHUFFLE;
                    if (_playModeString == "RANDOM")
                        return MediaRenderer_PlayMode::MRPLAYMODE_RANDOM;
                    if (_playModeString == "REPEAT_ONE")
                        return MediaRenderer_PlayMode::MRPLAYMODE_REPEAT_ONE;
                    if (_playModeString == "REPEAT_ALL")
                        return MediaRenderer_PlayMode::MRPLAYMODE_REPEAT_ALL;
                    if (_playModeString == "DIRECT_1")
                        return MediaRenderer_PlayMode::MRPLAYMODE_DIRECT_1;
                    if (_playModeString == "INTRO")
                        return MediaRenderer_PlayMode::MRPLAYMODE_INTRO;
                    return MediaRenderer_PlayMode::MRPLAYMODE_NORMAL;
                }

                static MediaRenderer_TransportState stringToTransportState(std::string _transportState)
                {
                    if (_transportState == "PLAYING")
                        return MediaRenderer_TransportState::MRTS_PLAYING;
                    if (_transportState == "STOPPED")
                        return MediaRenderer_TransportState::MRTS_STOPPED;
                    if (_transportState == "TRANSITIONING")
                        return MediaRenderer_TransportState::MRTS_TRANSITIONING;
                    return MediaRenderer_TransportState::MRTS_STOPPED;
                }


                static std::string transportStateToString(MediaRenderer_TransportState _transportState)
                {
                    if (_transportState == MediaRenderer_TransportState::MRTS_PLAYING)
                        return "PLAYING";
                    if (_transportState == MediaRenderer_TransportState::MRTS_STOPPED)
                        return "STOPPED";
                    if (_transportState == MediaRenderer_TransportState::MRTS_TRANSITIONING)
                        return "TRANSITIONING";
                    return "STOPPED";
                }


                static std::string muteStateToString(MediaRenderer_MuteState _muteState)
                {
                    if (_muteState == MediaRenderer_MuteState::MRPMUTE_ALL)
                        return "ALL";
                    if (_muteState == MediaRenderer_MuteState::MRPMUTE_NONE)
                        return "NONE";
                    if (_muteState == MediaRenderer_MuteState::MRPMUTE_PARTIAL)
                        return "PARTIAL";
                    return "NONE";
                }
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
                EXPORT virtual void play(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void stop(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void pause(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void next(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void previous(bool _sync = true);           
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void seek(MediaRenderer_Seek _seekType, std::uint32_t _seekToMsOrTrack, bool _sync = true);
                /*
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void setPlayMode(MediaRenderer_PlayMode _playMode, bool _sync = true);
                
                /*                
                SetAvTransportUri
                EXPORT virtual AvTransportMediaInfo getMediaInfo();
                EXPORT virtual AvTransportPositionInfo getPositionInfo();
                getTransportInfo()
                getTransportSettings()

                // basic media renderer functions
                EXPORT virtual void setMute(bool _mute, bool _sync = true);
                EXPORT virtual void setVolume(boost::uint8_t _volume, bool _sync = true);
                

                EXPORT virtual bool getMute();
                EXPORT virtual boost::uint8_t getVolume();
              
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
                virtual void seekProxy(std::string _unit, std::string _target, bool _sync = true);
                virtual void setPlayModeProxy(std::string _playMode, bool _sync = true);

                //virtual void setMuteProxy(bool _sync = true);
                //virtual void setVolumeProxy(bool _sync = true);

                virtual void onPlayExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onStopExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPauseExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onNextExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPreviousExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSeekExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSetPlayModeExecuted(OpenHome::Net::IAsync& _aAsync);
           

                void logRendererError(std::string _error, std::string _location);
        };

    }

}


#endif
