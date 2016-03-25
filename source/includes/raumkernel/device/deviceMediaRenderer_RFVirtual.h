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
#ifndef RAUMKERNEL_DEVICEMEDIARENDERER_RFVIRTUAL_H
#define RAUMKERNEL_DEVICEMEDIARENDERER_RFVIRTUAL_H

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpProxy.h>
#include <raumkernel/device/deviceMediaRenderer_RF.h>

#include <raumkernel/device/proxies/CpUpnpOrgAVTransport_RaumfeldVirtual1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager_RaumfeldVirtual1.h>
#include <raumkernel/device/proxies/CpUpnpOrgRenderingControl_RaumfeldVirtual1.h>


namespace Raumkernel
{
    namespace Devices
    {       
        class MediaRenderer_RaumfeldVirtual : public MediaRenderer_Raumfeld
        {
            public:
                MediaRenderer_RaumfeldVirtual();
                virtual ~MediaRenderer_RaumfeldVirtual();

                /**               
                * use this to change the uri while playing instead of setAvTransportUri 
                * (set will lead to stop the current track/link from playing)
                */
                EXPORT virtual void bendAvTransportUri(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync = true);
                /**
                * function not used/tested in raumfeld firmware until now (20160114)
                */
                EXPORT virtual void startSleepTimer(std::int16_t _instanceId, std::uint16_t _secondsUntilSleep, std::int16_t _secondsForVolumeRamp, bool _sync = true);

                /**
                * use this to set the mute state of a room
                */
                EXPORT virtual void setRoomMute(std::string _roomUDN, bool _mute, bool _sync = true);
                /**
                * use this to get the mute state of a room
                */
                EXPORT virtual bool getRoomMute(std::string _roomUDN, bool _sync = true);
                /**
                * use this to set the volume value of a room
                */
                EXPORT virtual void setRoomVolume(std::string _roomUDN, std::uint32_t _volume, bool _sync = true);
                /**
                * use this to get the volume value of a room
                */
                EXPORT virtual std::uint32_t getRoomVolume(std::string _roomUDN, bool _sync = true);
                /**
                * use this to change the volume value
                */
                EXPORT virtual void changeVolume(std::uint32_t _volumeDifference, bool _sync = true);
                /**
                * use this to load the container into the zone renderer
                */
                EXPORT virtual void loadContainer(const std::string &_containerId, const std::uint32_t &_trackIndex = 0, bool _sync = true);
                /**
                * use this to load a playlist into the zone renderer
                */
                EXPORT virtual void loadPlaylist(const std::string &_playlistName, const std::uint32_t &_trackIndex = 0, bool _sync = true);
                /**
                * use this to load a single item into the zone renderer
                */
                EXPORT virtual void loadSingle(const std::string &_singleId, bool _sync = true);
                /**
                * use this to load a uri into the zone renderer
                */
                EXPORT virtual void loadUri(const std::string &_uri, bool _sync = true);               
                /**
                * this method fades the volume to a specific value in a specific time
                */
                EXPORT virtual void fadeToVolume(const std::uint32_t _volume, std::uint32_t _duration, bool sync);
                             
            protected:                
                virtual void createProxyAvTransport() override;
                virtual void createProxyConnectionManager() override;
                virtual void createProxyRenderingControl() override;

                virtual void playProxy(bool _sync = true) override;
                virtual void stopProxy(bool _sync = true) override;
                virtual void pauseProxy(bool _sync = true) override;
                virtual void nextProxy(bool _sync = true) override;
                virtual void previousProxy(bool _sync = true) override;
                virtual void seekProxy(std::string _unit, std::string _target, bool _sync = true) override;
                virtual void setPlayModeProxy(std::string _playMode, bool _sync = true) override;
                virtual AvTransportMediaInfo getMediaInfoProxy(bool _sync = true) override;
                virtual AvTransportPositionInfo getPositionInfoProxy(bool _sync = true) override;
                virtual AvTransportInfo getTransportInfoProxy(bool _sync = true) override;
                virtual AvTransportSettings getTransportSettingsProxy(bool _sync = true) override;
                virtual void setAvTransportUriProxy(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync = true) override;

                virtual void bendAvTransportUriProxy(std::string _avTransportUri, std::string _avTransportUriMetaData, bool _sync = true);
                virtual void startSleepTimerProxy(std::int16_t _instanceId, std::uint16_t _secondsUntilSleep, std::int16_t _secondsForVolumeRamp, bool _sync = true);                

                virtual void setMuteProxy(bool _mute, bool _sync = true) override;
                virtual void setVolumeProxy(std::uint32_t _volume, bool _sync = true) override;
                virtual bool getMuteProxy(bool _sync = true) override;
                virtual std::uint32_t getVolumeProxy(bool _sync = true) override;

                virtual void setRoomMuteProxy(std::string _roomUDN, bool _mute, bool _sync = true);
                virtual bool getRoomMuteProxy(std::string _roomUDN, bool _sync = true);
                virtual void setRoomVolumeProxy(std::string _roomUDN, std::uint32_t, bool _sync = true);
                virtual std::uint32_t getRoomVolumeProxy(std::string _roomUDN, bool _sync = true);
                virtual void changeVolumeProxy(std::uint32_t _volumeDifference, bool _sync = true);

                virtual void onPlayExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onStopExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onPauseExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onNextExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onPreviousExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onSeekExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onSetPlayModeExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetMediaInfoExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetPositionInfoExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onSetAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetTransportInfoExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetTransportSettingsExecuted(OpenHome::Net::IAsync& _aAsync) override;

                virtual void onBendAvTransportUriExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onStartSleepTimerExecuted(OpenHome::Net::IAsync& _aAsync);

                virtual void onSetMuteExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onSetVolumeExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetMuteExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onGetVolumeExecuted(OpenHome::Net::IAsync& _aAsync) override;

                virtual void onSetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetRoomMuteExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onSetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onGetRoomVolumeExecuted(OpenHome::Net::IAsync& _aAsync);
                virtual void onChangeVolumeExecuted(OpenHome::Net::IAsync& _aAsync);

                virtual void onAvTransportProxyPropertyChanged();
                virtual void onRenderingControlProxyPropertyChanged();
                virtual void oConnectionManagerProxyPropertyChanged();

                sigs::signal<void(bool)> sigGetRoomMuteExecuted;
                sigs::signal<void(std::int32_t)> sigGetRoomVolumeExecuted;

        };

    }

}


#endif
