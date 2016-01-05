#include <raumkernel/device/proxies/CpUpnpOrgAVTransport_RaumfeldVirtual1.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBendAVTransportURI(aAsync);
}


class SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetResourceForCurrentStream(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    uint32_t& iNrTracks;
    std::string& iMediaDuration;
    std::string& iCurrentURI;
    std::string& iCurrentURIMetaData;
    std::string& iNextURI;
    std::string& iNextURIMetaData;
    std::string& iPlayMedium;
    std::string& iRecordMedium;
    std::string& iWriteStatus;
};

SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
: iService(aProxy)
, iNrTracks(aNrTracks)
, iMediaDuration(aMediaDuration)
, iCurrentURI(aCurrentURI)
, iCurrentURIMetaData(aCurrentURIMetaData)
, iNextURI(aNextURI)
, iNextURIMetaData(aNextURIMetaData)
, iPlayMedium(aPlayMedium)
, iRecordMedium(aRecordMedium)
, iWriteStatus(aWriteStatus)
{
}

void SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    std::string& iCurrentTransportState;
    std::string& iCurrentTransportStatus;
    std::string& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
: iService(aProxy)
, iCurrentTransportState(aCurrentTransportState)
, iCurrentTransportStatus(aCurrentTransportStatus)
, iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    uint32_t& iTrack;
    std::string& iTrackDuration;
    std::string& iTrackMetaData;
    std::string& iTrackURI;
    std::string& iRelTime;
    std::string& iAbsTime;
    int32_t& iRelCount;
    int32_t& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
: iService(aProxy)
, iTrack(aTrack)
, iTrackDuration(aTrackDuration)
, iTrackMetaData(aTrackMetaData)
, iTrackURI(aTrackURI)
, iRelTime(aRelTime)
, iAbsTime(aAbsTime)
, iRelCount(aRelCount)
, iAbsCount(aAbsCount)
{
}

void SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    std::string& iPlayMedia;
    std::string& iRecMedia;
    std::string& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
: iService(aProxy)
, iPlayMedia(aPlayMedia)
, iRecMedia(aRecMedia)
, iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aPlayMode, std::string& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    std::string& iPlayMode;
    std::string& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aPlayMode, std::string& aRecQualityMode)
: iService(aProxy)
, iPlayMode(aPlayMode)
, iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartSleepTimer(aAsync);
}


class SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
};

SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy)
: iService(aProxy)
{
}

void SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aCurrentContentType, uint32_t& aCurrentBitrate);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    std::string& iCurrentContentType;
    uint32_t& iCurrentBitrate;
};

SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aCurrentContentType, uint32_t& aCurrentBitrate)
: iService(aProxy)
, iCurrentContentType(aCurrentContentType)
, iCurrentBitrate(aCurrentBitrate)
{
}

void SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStreamProperties(aAsync, iCurrentContentType, iCurrentBitrate);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& iService;
    std::string& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp& aProxy, std::string& aActions)
: iService(aProxy)
, iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp(CpDeviceCpp& aDevice)
: CpProxy("schemas-upnp-org", "AVTransport", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionSetAVTransportURI = new Action("SetAVTransportURI");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionSetAVTransportURI->AddInputParameter(param);

    iActionBendAVTransportURI = new Action("BendAVTransportURI");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionBendAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionBendAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionBendAVTransportURI->AddInputParameter(param);

    iActionSetResourceForCurrentStream = new Action("SetResourceForCurrentStream");
    param = new OpenHome::Net::ParameterString("ResourceURI");
    iActionSetResourceForCurrentStream->AddInputParameter(param);

    iActionGetMediaInfo = new Action("GetMediaInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetMediaInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NrTracks", 0, 2147483648);
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("MediaDuration");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NETWORK";
    param = new OpenHome::Net::ParameterString("PlayMedium", allowedValues, 1);
    iActionGetMediaInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"NONE";
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    param = new OpenHome::Net::ParameterString("RecordMedium", allowedValues, 2);
    iActionGetMediaInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    param = new OpenHome::Net::ParameterString("WriteStatus", allowedValues, 1);
    iActionGetMediaInfo->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetTransportInfo = new Action("GetTransportInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetTransportInfo->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"STOPPED";
    allowedValues[index++] = (TChar*)"PAUSED_PLAYBACK";
    allowedValues[index++] = (TChar*)"PAUSED_RECORDING";
    allowedValues[index++] = (TChar*)"PLAYING";
    allowedValues[index++] = (TChar*)"RECORDING";
    allowedValues[index++] = (TChar*)"TRANSITIONING";
    allowedValues[index++] = (TChar*)"NO_MEDIA_PRESENT";
    param = new OpenHome::Net::ParameterString("CurrentTransportState", allowedValues, 7);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ERROR_OCCURRED";
    param = new OpenHome::Net::ParameterString("CurrentTransportStatus", allowedValues, 2);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    param = new OpenHome::Net::ParameterString("CurrentSpeed", allowedValues, 1);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetPositionInfo = new Action("GetPositionInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetPositionInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Track", 0, 2147483648, 1);
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackDuration");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackMetaData");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackURI");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RelTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("AbsTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("RelCount");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("AbsCount");
    iActionGetPositionInfo->AddOutputParameter(param);

    iActionGetDeviceCapabilities = new Action("GetDeviceCapabilities");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetDeviceCapabilities->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PlayMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecQualityModes");
    iActionGetDeviceCapabilities->AddOutputParameter(param);

    iActionGetTransportSettings = new Action("GetTransportSettings");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetTransportSettings->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    param = new OpenHome::Net::ParameterString("PlayMode", allowedValues, 7);
    iActionGetTransportSettings->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    param = new OpenHome::Net::ParameterString("RecQualityMode", allowedValues, 1);
    iActionGetTransportSettings->AddOutputParameter(param);
    delete[] allowedValues;

    iActionStop = new Action("Stop");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionStop->AddInputParameter(param);

    iActionPlay = new Action("Play");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPlay->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    param = new OpenHome::Net::ParameterString("Speed", allowedValues, 1);
    iActionPlay->AddInputParameter(param);
    delete[] allowedValues;

    iActionPause = new Action("Pause");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPause->AddInputParameter(param);

    iActionStartSleepTimer = new Action("StartSleepTimer");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionStartSleepTimer->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("SecondsUntilSleep");
    iActionStartSleepTimer->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("SecondsForVolumeRamp");
    iActionStartSleepTimer->AddInputParameter(param);

    iActionSeek = new Action("Seek");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSeek->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"ABS_TIME";
    allowedValues[index++] = (TChar*)"REL_TIME";
    allowedValues[index++] = (TChar*)"TRACK_NR";
    param = new OpenHome::Net::ParameterString("Unit", allowedValues, 3);
    iActionSeek->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Target");
    iActionSeek->AddInputParameter(param);

    iActionNext = new Action("Next");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionNext->AddInputParameter(param);

    iActionPrevious = new Action("Previous");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPrevious->AddInputParameter(param);

    iActionSetPlayMode = new Action("SetPlayMode");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetPlayMode->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    param = new OpenHome::Net::ParameterString("NewPlayMode", allowedValues, 7);
    iActionSetPlayMode->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetStreamProperties = new Action("GetStreamProperties");
    param = new OpenHome::Net::ParameterString("CurrentContentType");
    iActionGetStreamProperties->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBitrate");
    iActionGetStreamProperties->AddOutputParameter(param);

    iActionGetCurrentTransportActions = new Action("GetCurrentTransportActions");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetCurrentTransportActions->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Actions");
    iActionGetCurrentTransportActions->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::~CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp()
{
    DestroyService();
    delete iActionSetAVTransportURI;
    delete iActionBendAVTransportURI;
    delete iActionSetResourceForCurrentStream;
    delete iActionGetMediaInfo;
    delete iActionGetTransportInfo;
    delete iActionGetPositionInfo;
    delete iActionGetDeviceCapabilities;
    delete iActionGetTransportSettings;
    delete iActionStop;
    delete iActionPlay;
    delete iActionPause;
    delete iActionStartSleepTimer;
    delete iActionSeek;    
    delete iActionNext;
    delete iActionPrevious;
    delete iActionSetPlayMode;
    delete iActionGetStreamProperties;
    delete iActionGetCurrentTransportActions;
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aCurrentURI.c_str(), (TUint)aCurrentURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentURIMetaData.c_str(), (TUint)aCurrentURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncBendAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData)
{
    SyncBendAVTransportURIUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginBendAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginBendAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBendAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBendAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aCurrentURI.c_str(), (TUint)aCurrentURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentURIMetaData.c_str(), (TUint)aCurrentURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndBendAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BendAVTransportURI"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetResourceForCurrentStream(const std::string& aResourceURI)
{
    SyncSetResourceForCurrentStreamUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginSetResourceForCurrentStream(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginSetResourceForCurrentStream(const std::string& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetResourceForCurrentStream, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetResourceForCurrentStream->InputParameters();
    {
        Brn buf((const TByte*)aResourceURI.c_str(), (TUint)aResourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndSetResourceForCurrentStream(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetResourceForCurrentStream"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetMediaInfo(uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetMediaInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMediaInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMediaInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMediaInfo->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetMediaInfo(IAsync& aAsync, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNrTracks = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMediaDuration.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentURIMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNextURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNextURIMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMedium.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecordMedium.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aWriteStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetTransportInfo(uint32_t aInstanceID, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetTransportInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransportInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetTransportInfo(IAsync& aAsync, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentTransportState.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentTransportStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentSpeed.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetPositionInfo(uint32_t aInstanceID, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetPositionInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPositionInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPositionInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPositionInfo->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetPositionInfo(IAsync& aAsync, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPositionInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTrack = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackDuration.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRelTime.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aAbsTime.assign((const char*)val.Ptr(), val.Bytes());
    }
    aRelCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAbsCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetDeviceCapabilities(uint32_t aInstanceID, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetDeviceCapabilities(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetDeviceCapabilities, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetDeviceCapabilities->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetDeviceCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetDeviceCapabilities(IAsync& aAsync, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDeviceCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMedia.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecMedia.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecQualityModes.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetTransportSettings(uint32_t aInstanceID, std::string& aPlayMode, std::string& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetTransportSettings(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransportSettings, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportSettings->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportSettings->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetTransportSettings(IAsync& aAsync, std::string& aPlayMode, std::string& aRecQualityMode)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportSettings"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMode.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecQualityMode.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncStop(uint32_t aInstanceID)
{
    SyncStopUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginStop(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPlay(uint32_t aInstanceID, const std::string& aSpeed)
{
    SyncPlayUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginPlay(uint32_t aInstanceID, const std::string& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aSpeed.c_str(), (TUint)aSpeed.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPause(uint32_t aInstanceID)
{
    SyncPauseUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginPause(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncStartSleepTimer(uint32_t aInstanceID, uint32_t aSecondsUntilSleep, uint32_t aSecondsForVolumeRamp)
{
    SyncStartSleepTimerUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginStartSleepTimer(aInstanceID, aSecondsUntilSleep, aSecondsForVolumeRamp, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginStartSleepTimer(uint32_t aInstanceID, uint32_t aSecondsUntilSleep, uint32_t aSecondsForVolumeRamp, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartSleepTimer, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStartSleepTimer->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aSecondsUntilSleep));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aSecondsForVolumeRamp));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndStartSleepTimer(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartSleepTimer"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget)
{
    SyncSeekUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aUnit.c_str(), (TUint)aUnit.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aTarget.c_str(), (TUint)aTarget.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncNext(uint32_t aInstanceID)
{
    SyncNextUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginNext(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncPrevious(uint32_t aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginPrevious(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aNewPlayMode.c_str(), (TUint)aNewPlayMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetStreamProperties(std::string& aCurrentContentType, uint32_t& aCurrentBitrate)
{
    SyncGetStreamPropertiesUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aCurrentContentType, aCurrentBitrate);
    BeginGetStreamProperties(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetStreamProperties(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStreamProperties, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStreamProperties->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetStreamProperties(IAsync& aAsync, std::string& aCurrentContentType, uint32_t& aCurrentBitrate)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStreamProperties"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentContentType.assign((const char*)val.Ptr(), val.Bytes());
    }
    aCurrentBitrate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SyncGetCurrentTransportActions(uint32_t aInstanceID, std::string& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport_RaumfeldVirtual1Cpp sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::BeginGetCurrentTransportActions(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCurrentTransportActions, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetCurrentTransportActions->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentTransportActions->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::EndGetCurrentTransportActions(IAsync& aAsync, std::string& aActions)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentTransportActions"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aActions.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgAVTransport_RaumfeldVirtual1Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

