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


#include <unordered_map>
#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpProxy.h>
#include <raumkernel/signals/signals.hpp>
#include <raumkernel/device/device.h>
#include <raumkernel/device/proxies/CpUpnpOrgAVTransport1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager1.h>
#include <raumkernel/device/proxies/CpUpnpOrgRenderingControl1.h>
#include <raumkernel/device/eventParser/deviceEventParserMediaRenderer.h>


namespace Raumkernel
{
    namespace Devices
    {
        enum class MediaRenderer_PlayMode { MRPLAYMODE_NORMAL = 0, MRPLAYMODE_SHUFFLE = 1, MRPLAYMODE_REPEAT_ONE = 2, MRPLAYMODE_REPEAT_ALL = 3, MRPLAYMODE_RANDOM = 4, MRPLAYMODE_DIRECT_1 = 5, MRPLAYMODE_INTRO = 6 };
        enum class MediaRenderer_MuteState { MRPMUTE_NONE, MRPMUTE_ALL, MRPMUTE_PARTIAL };
        enum class MediaRenderer_TransportState { MRTS_STOPPED, MRTS_PLAYING, MRTS_TRANSITIONING };
        enum class MediaRenderer_Seek { MRSEEK_ABS_TIME, MRSEEK_REL_TIME, MRSEEK_TRACK_NR };
        
        const std::string MEDIARENDERER_NOT_IMPLEMENTED = "NOT_IMPLEMENTED";
        const std::string MEDIARENDERER_MASTER_CHANNEL = "Master";


        struct AvTransportMediaInfo
        {
            std::uint32_t nrTracks = 0;
            std::string mediaDuration = "00:00:00";
            std::uint32_t mediaDurationMS = 0;
            std::string currentUri = "";
            std::string currentUriMetaData = "";
            std::string nextUri = "";
            std::string nextUriMetaData = "";
            std::string playMedium = "";
            std::string recordMedium = "";
            std::string writeStatus = "";
        };


        struct AvTransportPositionInfo
        {
            std::uint32_t track = 0;
            std::string trackDuration = "00:00:00";
            std::uint32_t trackDurationMS = 0;
            std::string trackMetaData = "";
            std::string trackUri = "";
            std::string relTime = "";
            std::uint32_t relTimeMS = 0;
            std::string absTime = "";
            std::uint32_t absTimeMS = 0;
            std::int32_t relCount = 0;
            std::int32_t absCount = 0;
        };


        struct AvTransportInfo
        {        
            std::string currentTransportState = "";            
            std::string currentTransportStatus = "";
            std::string currentSpeed = "";
        };


        struct AvTransportSettings
        {
            std::string playMode = "";
            std::string recQualityMode = ""; 
        };


        struct MediaRendererRoomState
        {
            //
            bool mute = true;
            //
            std::uint8_t volume = 0;            
            std::string roomUDN = "";            
            MediaRenderer_TransportState transportState = MediaRenderer_TransportState::MRTS_STOPPED;
        };


        struct MediaRendererState
        {
            // TODO
            MediaRenderer_PlayMode playMode = MediaRenderer_PlayMode::MRPLAYMODE_NORMAL;
            // TODO
            MediaRenderer_MuteState muteState = MediaRenderer_MuteState::MRPMUTE_ALL;
            MediaRenderer_TransportState transportState = MediaRenderer_TransportState::MRTS_STOPPED;

            std::uint8_t volume = 0;
            bool mute = true;

            std::string aVTransportURI = "";
            std::string aVTransportURIMetaData = "";
            std::string currentTrackURI = "";
            std::string currentTrackMetaData = "";

            std::string contentType = "";

            std::uint32_t currentTrack = 0;    
            std::uint32_t currentTrackDuration = 0; 
            std::uint32_t numberOfTracks = 0;
            std::uint32_t bitrate = 0;

            // TODO: @@@
            std::string containerId = "";
            /* 
            std::uint8_t volume; 
            std::string containerId;              
            */

            // TODO: @@@
            // this map holds room state struct for rooms which are added to virtual media renderer		
            std::string roomTransportStatesCombined = "";
            std::string roomMuteStatesCombined = "";
            std::string roomVolumeStatesCombined = "";
            std::unordered_map<std::string, MediaRendererRoomState>	roomStates;
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
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual AvTransportMediaInfo getMediaInfo(bool _sync = true);   
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual AvTransportPositionInfo getPositionInfo(bool _sync = true);               
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void setAvTransportUri(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual AvTransportInfo getTransportInfo(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual AvTransportSettings getTransportSettings(bool _sync = true);


                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void setMute(bool _mute, bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual void setVolume(std::uint32_t _volume, bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual bool getMute(bool _sync = true);
                /**
                * Not intended for external use
                * Please use the 'virtual' media renderer!
                */
                EXPORT virtual std::uint32_t getVolume(bool _sync = true);

                /**
                * returns the current state struct for the media renderer
                * This struct will be updated when calling methods like "getTransportInfo" or "getVolume", aso... 
                * and when a subsription will change any data of the struct
                */
                EXPORT virtual MediaRendererState state();
                /**
                * sets the state structure from outside
                */
                EXPORT virtual void setState(MediaRendererState _rendererState);

                EXPORT virtual void lockRendererState();
                EXPORT virtual void unlockRendererState();

                EXPORT bool isRenderingControlProxyAvailable();
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
                
                MediaRendererState rendererState;
                std::mutex mutexRendererStateChange;

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
                virtual AvTransportMediaInfo getMediaInfoProxy(bool _sync = true);
                virtual AvTransportPositionInfo getPositionInfoProxy(bool _sync = true);
                virtual AvTransportInfo getTransportInfoProxy(bool _sync = true);
                virtual AvTransportSettings getTransportSettingsProxy(bool _sync = true);
                virtual void setAvTransportUriProxy(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync = true);


                virtual void setMuteProxy(bool _mute, bool _sync = true);
                virtual void setVolumeProxy(std::uint32_t _volume, bool _sync = true);
                virtual bool getMuteProxy(bool _sync = true);
                virtual std::uint32_t getVolumeProxy(bool _sync = true);
              

                virtual void onPlayExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onStopExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPauseExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onNextExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onPreviousExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSeekExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSetPlayModeExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetMediaInfoExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetPositionInfoExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSetAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetTransportInfoExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetTransportSettingsExecuted(OpenHome::Net::IAsync& _aAsync);

                virtual void onSetMuteExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSetVolumeExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetMuteExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetVolumeExecuted(OpenHome::Net::IAsync& _aAsync);

                virtual void onAvTransportProxyPropertyChanged();
                virtual void onRenderingControlProxyPropertyChanged();                
                virtual void oConnectionManagerProxyPropertyChanged();
           
                void logRendererError(std::string _error, std::string _location);

                sigs::signal<void(AvTransportMediaInfo)> sigGetMediaInfoExecuted;
                sigs::signal<void(AvTransportPositionInfo)> sigGetPositionInfoExecuted;
                sigs::signal<void(AvTransportInfo)> sigGetTransportInfoExecuted;
                sigs::signal<void(AvTransportSettings)> sigGetTransportSettingsExecuted;
                sigs::signal<void(bool)> sigGetMuteExecuted;
                sigs::signal<void(std::int32_t)> sigGetVolumeExecuted;
        };

    }

}


#endif
