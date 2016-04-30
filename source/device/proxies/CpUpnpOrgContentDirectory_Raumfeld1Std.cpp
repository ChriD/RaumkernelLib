#include "raumkernel/device/proxies/CpUpnpOrgContentDirectory_Raumfeld1.h"
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


class SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp::SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp::SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aPlaylistID, std::string& aPlaylistMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iPlaylistID;
    std::string& iPlaylistMetadata;
};

SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp::SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aPlaylistID, std::string& aPlaylistMetadata)
    : iService(aProxy)
    , iPlaylistID(aPlaylistID)
    , iPlaylistMetadata(aPlaylistMetadata)
{
}

void SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iPlaylistID, iPlaylistMetadata);
}


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp::SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


class SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAddContainerToQueue(aAsync);
}


class SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAddItemToQueue(aAsync);
}


class SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aContainerUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    uint32_t& iContainerUpdateID;
};

SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aContainerUpdateID)
    : iService(aProxy)
    , iContainerUpdateID(aContainerUpdateID)
{
}

void SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRemoveFromQueue(aAsync, iContainerUpdateID);
}


class SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iGivenName;
    std::string& iQueueID;
    std::string& iMetaData;
};

SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData)
    : iService(aProxy)
    , iGivenName(aGivenName)
    , iQueueID(aQueueID)
    , iMetaData(aMetaData)
{
}

void SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateQueue(aAsync, iGivenName, iQueueID, iMetaData);
}


class SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aGivenName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iGivenName;
};

SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aGivenName)
    : iService(aProxy)
    , iGivenName(aGivenName)
{
}

void SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRenameQueue(aAsync, iGivenName);
}


class SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aContainerUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    uint32_t& iContainerUpdateID;
};

SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp::SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aContainerUpdateID)
    : iService(aProxy)
    , iContainerUpdateID(aContainerUpdateID)
{
}

void SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMoveInQueue(aAsync, iContainerUpdateID);
}


class SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp::SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp::SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetDatabase(aAsync);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    uint32_t& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iStatus;
};

SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aStatus)
    : iService(aProxy)
    , iStatus(aStatus)
{
}

void SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetIndexerStatus(aAsync, iStatus);
}


class SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    uint32_t& iNumTracks;
    uint32_t& iTotalSize;
    uint32_t& iTotalDuration;
    uint32_t& iScanProgress;
    std::string& iIndexerResult;
};

SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult)
    : iService(aProxy)
    , iNumTracks(aNumTracks)
    , iTotalSize(aTotalSize)
    , iTotalDuration(aTotalDuration)
    , iScanProgress(aScanProgress)
    , iIndexerResult(aIndexerResult)
{
}

void SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSourceInfo(aAsync, iNumTracks, iTotalSize, iTotalDuration, iScanProgress, iIndexerResult);
}


class SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRescanSource(aAsync);
}


class SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    uint32_t& iCurrentNumResources;
    uint32_t& iCriticalNumResources;
    uint32_t& iCurrentDiskUsage;
    uint32_t& iMaxDiskUsage;
};

SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp::SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage)
    : iService(aProxy)
    , iCurrentNumResources(aCurrentNumResources)
    , iCriticalNumResources(aCriticalNumResources)
    , iCurrentDiskUsage(aCurrentDiskUsage)
    , iMaxDiskUsage(aMaxDiskUsage)
{
}

void SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndQueryDatabaseState(aAsync, iCurrentNumResources, iCriticalNumResources, iCurrentDiskUsage, iMaxDiskUsage);
}


class SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
};

SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAssignStationButton(aAsync);
}


class SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp : public SyncProxyAction
{
public:
    SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aObjectID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& iService;
    std::string& iObjectID;
};

SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp(CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp& aProxy, std::string& aObjectID)
    : iService(aProxy)
    , iObjectID(aObjectID)
{
}

void SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStationButtonAssignment(aAsync, iObjectID);
}


CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice)
    : iCpProxy("schemas-upnp-org", "ContentDirectory", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionBrowse = new Action("Browse");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionBrowse->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    param = new OpenHome::Net::ParameterString("BrowseFlag", allowedValues, 2);
    iActionBrowse->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowse->AddOutputParameter(param);

    iActionSearch = new Action("Search");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SearchCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionSearch->AddOutputParameter(param);

    iActionShuffle = new Action("Shuffle");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionShuffle->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Selection");
    iActionShuffle->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PlaylistID");
    iActionShuffle->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("PlaylistMetadata");
    iActionShuffle->AddOutputParameter(param);

    iActionGetSearchCapabilities = new Action("GetSearchCapabilities");
    param = new OpenHome::Net::ParameterString("SearchCaps");
    iActionGetSearchCapabilities->AddOutputParameter(param);

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new OpenHome::Net::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionCreateReference = new Action("CreateReference");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewID");
    iActionCreateReference->AddOutputParameter(param);

    iActionAddContainerToQueue = new Action("AddContainerToQueue");
    param = new OpenHome::Net::ParameterString("QueueID");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SourceID");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SearchCriteria");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartIndex");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("EndIndex");
    iActionAddContainerToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Position");
    iActionAddContainerToQueue->AddInputParameter(param);

    iActionAddItemToQueue = new Action("AddItemToQueue");
    param = new OpenHome::Net::ParameterString("QueueID");
    iActionAddItemToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionAddItemToQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Position");
    iActionAddItemToQueue->AddInputParameter(param);

    iActionRemoveFromQueue = new Action("RemoveFromQueue");
    param = new OpenHome::Net::ParameterString("QueueID");
    iActionRemoveFromQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("FromPosition");
    iActionRemoveFromQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ToPosition");
    iActionRemoveFromQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ContainerUpdateID");
    iActionRemoveFromQueue->AddOutputParameter(param);

    iActionCreateQueue = new Action("CreateQueue");
    param = new OpenHome::Net::ParameterString("DesiredName");
    iActionCreateQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("GivenName");
    iActionCreateQueue->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("QueueID");
    iActionCreateQueue->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("MetaData");
    iActionCreateQueue->AddOutputParameter(param);

    iActionRenameQueue = new Action("RenameQueue");
    param = new OpenHome::Net::ParameterString("QueueID");
    iActionRenameQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("DesiredName");
    iActionRenameQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("GivenName");
    iActionRenameQueue->AddOutputParameter(param);

    iActionMoveInQueue = new Action("MoveInQueue");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionMoveInQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewPosition");
    iActionMoveInQueue->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ContainerUpdateID");
    iActionMoveInQueue->AddOutputParameter(param);

    iActionDestroyObject = new Action("DestroyObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionDestroyObject->AddInputParameter(param);

    iActionResetDatabase = new Action("ResetDatabase");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"RESET_ALL";
    allowedValues[index++] = (TChar*)"RESET_USERDATA";
    allowedValues[index++] = (TChar*)"RESET_INDEX";
    param = new OpenHome::Net::ParameterString("Scope", allowedValues, 3);
    iActionResetDatabase->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetSystemUpdateID = new Action("GetSystemUpdateID");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionGetSystemUpdateID->AddOutputParameter(param);

    iActionGetIndexerStatus = new Action("GetIndexerStatus");
    param = new OpenHome::Net::ParameterString("Status");
    iActionGetIndexerStatus->AddOutputParameter(param);

    iActionGetSourceInfo = new Action("GetSourceInfo");
    param = new OpenHome::Net::ParameterString("SourceID");
    iActionGetSourceInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumTracks");
    iActionGetSourceInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalSize");
    iActionGetSourceInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalDuration");
    iActionGetSourceInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("ScanProgress");
    iActionGetSourceInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"NONE";
    allowedValues[index++] = (TChar*)"SUCCESS";
    allowedValues[index++] = (TChar*)"MOUNTING_FAILED";
    allowedValues[index++] = (TChar*)"UNREACHABLE";
    param = new OpenHome::Net::ParameterString("IndexerResult", allowedValues, 4);
    iActionGetSourceInfo->AddOutputParameter(param);
    delete[] allowedValues;

    iActionRescanSource = new Action("RescanSource");
    param = new OpenHome::Net::ParameterString("SourceID");
    iActionRescanSource->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"FindNewTracks";
    allowedValues[index++] = (TChar*)"DoFullRescan";
    param = new OpenHome::Net::ParameterString("RescanMode", allowedValues, 2);
    iActionRescanSource->AddInputParameter(param);
    delete[] allowedValues;

    iActionQueryDatabaseState = new Action("QueryDatabaseState");
    param = new OpenHome::Net::ParameterUint("CurrentNumResources");
    iActionQueryDatabaseState->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("CriticalNumResources");
    iActionQueryDatabaseState->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentDiskUsage");
    iActionQueryDatabaseState->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("MaxDiskUsage");
    iActionQueryDatabaseState->AddOutputParameter(param);

    iActionAssignStationButton = new Action("AssignStationButton");
    param = new OpenHome::Net::ParameterString("Renderer");
    iActionAssignStationButton->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Button");
    iActionAssignStationButton->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionAssignStationButton->AddInputParameter(param);

    iActionGetStationButtonAssignment = new Action("GetStationButtonAssignment");
    param = new OpenHome::Net::ParameterString("Renderer");
    iActionGetStationButtonAssignment->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Button");
    iActionGetStationButtonAssignment->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionGetStationButtonAssignment->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint("SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString("ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::IndexerStatusPropertyChanged);
    iIndexerStatus = new PropertyString("IndexerStatus", functor);
    AddProperty(iIndexerStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::A_ARG_TYPE_ScopePropertyChanged);
    iA_ARG_TYPE_Scope = new PropertyString("A_ARG_TYPE_Scope", functor);
    AddProperty(iA_ARG_TYPE_Scope);
}

CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::~CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp()
{
    DestroyService();
    delete iActionBrowse;
    delete iActionSearch;
    delete iActionShuffle;
    delete iActionGetSearchCapabilities;
    delete iActionGetSortCapabilities;
    delete iActionCreateReference;
    delete iActionAddContainerToQueue;
    delete iActionAddItemToQueue;
    delete iActionRemoveFromQueue;
    delete iActionCreateQueue;
    delete iActionRenameQueue;
    delete iActionMoveInQueue;
    delete iActionDestroyObject;
    delete iActionResetDatabase;
    delete iActionGetSystemUpdateID;
    delete iActionGetIndexerStatus;
    delete iActionGetSourceInfo;
    delete iActionRescanSource;
    delete iActionQueryDatabaseState;
    delete iActionAssignStationButton;
    delete iActionGetStationButtonAssignment;
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionBrowse, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowse->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aBrowseFlag.c_str(), (TUint)aBrowseFlag.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Browse"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSearch, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSearch->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSearchCriteria.c_str(), (TUint)aSearchCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Search"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncShuffle(const std::string& aContainerID, const std::string& aSelection, std::string& aPlaylistID, std::string& aPlaylistMetadata)
{
    SyncShuffleUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aPlaylistID, aPlaylistMetadata);
    BeginShuffle(aContainerID, aSelection, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginShuffle(const std::string& aContainerID, const std::string& aSelection, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionShuffle->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSelection.c_str(), (TUint)aSelection.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndShuffle(IAsync& aAsync, std::string& aPlaylistID, std::string& aPlaylistMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shuffle"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlaylistID.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlaylistMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSearchCapabilities(std::string& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSearchCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSearchCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSortCapabilities(std::string& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSortCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndCreateReference(IAsync& aAsync, std::string& aNewID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateReference"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNewID.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition)
{
    SyncAddContainerToQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginAddContainerToQueue(aQueueID, aContainerID, aSourceID, aSearchCriteria, aSortCriteria, aStartIndex, aEndIndex, aPosition, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionAddContainerToQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionAddContainerToQueue->InputParameters();
    {
        Brn buf((const TByte*)aQueueID.c_str(), (TUint)aQueueID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSourceID.c_str(), (TUint)aSourceID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSearchCriteria.c_str(), (TUint)aSearchCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aEndIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aPosition));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndAddContainerToQueue(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AddContainerToQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition)
{
    SyncAddItemToQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginAddItemToQueue(aQueueID, aObjectID, aPosition, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionAddItemToQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionAddItemToQueue->InputParameters();
    {
        Brn buf((const TByte*)aQueueID.c_str(), (TUint)aQueueID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aPosition));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndAddItemToQueue(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AddItemToQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, uint32_t& aContainerUpdateID)
{
    SyncRemoveFromQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aContainerUpdateID);
    BeginRemoveFromQueue(aQueueID, aFromPosition, aToPosition, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionRemoveFromQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRemoveFromQueue->InputParameters();
    {
        Brn buf((const TByte*)aQueueID.c_str(), (TUint)aQueueID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aFromPosition));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToPosition));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRemoveFromQueue->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndRemoveFromQueue(IAsync& aAsync, uint32_t& aContainerUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RemoveFromQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aContainerUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData)
{
    SyncCreateQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aGivenName, aQueueID, aMetaData);
    BeginCreateQueue(aDesiredName, aContainerID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionCreateQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateQueue->InputParameters();
    {
        Brn buf((const TByte*)aDesiredName.c_str(), (TUint)aDesiredName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateQueue->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndCreateQueue(IAsync& aAsync, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aGivenName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aQueueID.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, std::string& aGivenName)
{
    SyncRenameQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aGivenName);
    BeginRenameQueue(aQueueID, aDesiredName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionRenameQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRenameQueue->InputParameters();
    {
        Brn buf((const TByte*)aQueueID.c_str(), (TUint)aQueueID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDesiredName.c_str(), (TUint)aDesiredName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRenameQueue->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndRenameQueue(IAsync& aAsync, std::string& aGivenName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RenameQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aGivenName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, uint32_t& aContainerUpdateID)
{
    SyncMoveInQueueUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aContainerUpdateID);
    BeginMoveInQueue(aObjectID, aNewPosition, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionMoveInQueue, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMoveInQueue->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aNewPosition));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMoveInQueue->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndMoveInQueue(IAsync& aAsync, uint32_t& aContainerUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MoveInQueue"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aContainerUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncDestroyObject(const std::string& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndDestroyObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DestroyObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncResetDatabase(const std::string& aScope)
{
    SyncResetDatabaseUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginResetDatabase(aScope, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginResetDatabase(const std::string& aScope, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionResetDatabase, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetDatabase->InputParameters();
    {
        Brn buf((const TByte*)aScope.c_str(), (TUint)aScope.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndResetDatabase(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResetDatabase"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSystemUpdateID(uint32_t& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSystemUpdateID"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetIndexerStatus(std::string& aStatus)
{
    SyncGetIndexerStatusUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aStatus);
    BeginGetIndexerStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetIndexerStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetIndexerStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetIndexerStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetIndexerStatus(IAsync& aAsync, std::string& aStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetIndexerStatus"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetSourceInfo(const std::string& aSourceID, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult)
{
    SyncGetSourceInfoUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aNumTracks, aTotalSize, aTotalDuration, aScanProgress, aIndexerResult);
    BeginGetSourceInfo(aSourceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetSourceInfo(const std::string& aSourceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetSourceInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetSourceInfo->InputParameters();
    {
        Brn buf((const TByte*)aSourceID.c_str(), (TUint)aSourceID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSourceInfo->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetSourceInfo(IAsync& aAsync, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSourceInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNumTracks = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalSize = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aScanProgress = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aIndexerResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncRescanSource(const std::string& aSourceID, const std::string& aRescanMode)
{
    SyncRescanSourceUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginRescanSource(aSourceID, aRescanMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginRescanSource(const std::string& aSourceID, const std::string& aRescanMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionRescanSource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRescanSource->InputParameters();
    {
        Brn buf((const TByte*)aSourceID.c_str(), (TUint)aSourceID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aRescanMode.c_str(), (TUint)aRescanMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndRescanSource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RescanSource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncQueryDatabaseState(uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage)
{
    SyncQueryDatabaseStateUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aCurrentNumResources, aCriticalNumResources, aCurrentDiskUsage, aMaxDiskUsage);
    BeginQueryDatabaseState(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginQueryDatabaseState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionQueryDatabaseState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionQueryDatabaseState->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndQueryDatabaseState(IAsync& aAsync, uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("QueryDatabaseState"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentNumResources = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aCriticalNumResources = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aCurrentDiskUsage = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aMaxDiskUsage = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID)
{
    SyncAssignStationButtonUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this);
    BeginAssignStationButton(aRenderer, aButton, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionAssignStationButton, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionAssignStationButton->InputParameters();
    {
        Brn buf((const TByte*)aRenderer.c_str(), (TUint)aRenderer.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aButton));
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndAssignStationButton(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AssignStationButton"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SyncGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, std::string& aObjectID)
{
    SyncGetStationButtonAssignmentUpnpOrgContentDirectory_Raumfeld1Cpp sync(*this, aObjectID);
    BeginGetStationButtonAssignment(aRenderer, aButton, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::BeginGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetStationButtonAssignment, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStationButtonAssignment->InputParameters();
    {
        Brn buf((const TByte*)aRenderer.c_str(), (TUint)aRenderer.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aButton));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStationButtonAssignment->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::EndGetStationButtonAssignment(IAsync& aAsync, std::string& aObjectID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStationButtonAssignment"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aObjectID.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iSystemUpdateIDChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertyIndexerStatusChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iIndexerStatusChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertyA_ARG_TYPE_ScopeChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iA_ARG_TYPE_ScopeChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::PropertySystemUpdateID(uint32_t& aSystemUpdateID) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iContainerUpdateIDs->Value();
    aContainerUpdateIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::PropertyIndexerStatus(std::string& aIndexerStatus) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iIndexerStatus->Value();
    aIndexerStatus.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::PropertyA_ARG_TYPE_Scope(std::string& aA_ARG_TYPE_Scope) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iA_ARG_TYPE_Scope->Value();
    aA_ARG_TYPE_Scope.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::IndexerStatusPropertyChanged()
{
    ReportEvent(iIndexerStatusChanged);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::A_ARG_TYPE_ScopePropertyChanged()
{
    ReportEvent(iA_ARG_TYPE_ScopeChanged);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::Subscribe()
{
  iCpProxy.Subscribe();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::Unsubscribe()
{
 iCpProxy.Unsubscribe();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertyChanged(Functor& aFunctor)
{
  iCpProxy.SetPropertyChanged(aFunctor);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::SetPropertyInitialEvent(Functor& aFunctor)
{
  iCpProxy.SetPropertyInitialEvent(aFunctor);
}
void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::AddProperty(Property* aProperty)
{
  iCpProxy.AddProperty(aProperty);
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::DestroyService()
{
  iCpProxy.DestroyService();
}

void CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::ReportEvent(Functor aFunctor)
{
  iCpProxy.ReportEvent(aFunctor);
}

TUint CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp::Version() const
{
  return iCpProxy.Version();
}

