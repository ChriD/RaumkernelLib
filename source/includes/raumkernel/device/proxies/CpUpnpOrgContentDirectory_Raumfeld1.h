#ifndef HEADER_UPNPORGCONTENTDIRECTORY_RAUMFELD1CPP
#define HEADER_UPNPORGCONTENTDIRECTORY_RAUMFELD1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Net/Core/CpProxy.h>

#include <string>

namespace OpenHome {
namespace Net {

class CpDeviceCpp;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;
class CpProxy;
class ICpProxyUpnpOrgContentDirectory_Raumfeld1Cpp : public ICpProxy
{
public:
    virtual ~ICpProxyUpnpOrgContentDirectory_Raumfeld1Cpp() {}
    virtual void SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID) = 0;
    virtual void BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor) = 0;
    virtual void EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID) = 0;
    virtual void SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID) = 0;
    virtual void BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor) = 0;
    virtual void EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID) = 0;
    virtual void SyncShuffle(const std::string& aContainerID, const std::string& aSelection, std::string& aPlaylistID, std::string& aPlaylistMetadata) = 0;
    virtual void BeginShuffle(const std::string& aContainerID, const std::string& aSelection, FunctorAsync& aFunctor) = 0;
    virtual void EndShuffle(IAsync& aAsync, std::string& aPlaylistID, std::string& aPlaylistMetadata) = 0;
    virtual void SyncGetSearchCapabilities(std::string& aSearchCaps) = 0;
    virtual void BeginGetSearchCapabilities(FunctorAsync& aFunctor) = 0;
    virtual void EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps) = 0;
    virtual void SyncGetSortCapabilities(std::string& aSortCaps) = 0;
    virtual void BeginGetSortCapabilities(FunctorAsync& aFunctor) = 0;
    virtual void EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps) = 0;
    virtual void SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID) = 0;
    virtual void BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor) = 0;
    virtual void EndCreateReference(IAsync& aAsync, std::string& aNewID) = 0;
    virtual void SyncAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition) = 0;
    virtual void BeginAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition, FunctorAsync& aFunctor) = 0;
    virtual void EndAddContainerToQueue(IAsync& aAsync) = 0;
    virtual void SyncAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition) = 0;
    virtual void BeginAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition, FunctorAsync& aFunctor) = 0;
    virtual void EndAddItemToQueue(IAsync& aAsync) = 0;
    virtual void SyncRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, uint32_t& aContainerUpdateID) = 0;
    virtual void BeginRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, FunctorAsync& aFunctor) = 0;
    virtual void EndRemoveFromQueue(IAsync& aAsync, uint32_t& aContainerUpdateID) = 0;
    virtual void SyncCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData) = 0;
    virtual void BeginCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, FunctorAsync& aFunctor) = 0;
    virtual void EndCreateQueue(IAsync& aAsync, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData) = 0;
    virtual void SyncRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, std::string& aGivenName) = 0;
    virtual void BeginRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, FunctorAsync& aFunctor) = 0;
    virtual void EndRenameQueue(IAsync& aAsync, std::string& aGivenName) = 0;
    virtual void SyncMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, uint32_t& aContainerUpdateID) = 0;
    virtual void BeginMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, FunctorAsync& aFunctor) = 0;
    virtual void EndMoveInQueue(IAsync& aAsync, uint32_t& aContainerUpdateID) = 0;
    virtual void SyncDestroyObject(const std::string& aObjectID) = 0;
    virtual void BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor) = 0;
    virtual void EndDestroyObject(IAsync& aAsync) = 0;
    virtual void SyncResetDatabase(const std::string& aScope) = 0;
    virtual void BeginResetDatabase(const std::string& aScope, FunctorAsync& aFunctor) = 0;
    virtual void EndResetDatabase(IAsync& aAsync) = 0;
    virtual void SyncGetSystemUpdateID(uint32_t& aId) = 0;
    virtual void BeginGetSystemUpdateID(FunctorAsync& aFunctor) = 0;
    virtual void EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId) = 0;
    virtual void SyncGetIndexerStatus(std::string& aStatus) = 0;
    virtual void BeginGetIndexerStatus(FunctorAsync& aFunctor) = 0;
    virtual void EndGetIndexerStatus(IAsync& aAsync, std::string& aStatus) = 0;
    virtual void SyncGetSourceInfo(const std::string& aSourceID, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult) = 0;
    virtual void BeginGetSourceInfo(const std::string& aSourceID, FunctorAsync& aFunctor) = 0;
    virtual void EndGetSourceInfo(IAsync& aAsync, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult) = 0;
    virtual void SyncRescanSource(const std::string& aSourceID, const std::string& aRescanMode) = 0;
    virtual void BeginRescanSource(const std::string& aSourceID, const std::string& aRescanMode, FunctorAsync& aFunctor) = 0;
    virtual void EndRescanSource(IAsync& aAsync) = 0;
    virtual void SyncQueryDatabaseState(uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage) = 0;
    virtual void BeginQueryDatabaseState(FunctorAsync& aFunctor) = 0;
    virtual void EndQueryDatabaseState(IAsync& aAsync, uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage) = 0;
    virtual void SyncAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID) = 0;
    virtual void BeginAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID, FunctorAsync& aFunctor) = 0;
    virtual void EndAssignStationButton(IAsync& aAsync) = 0;
    virtual void SyncGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, std::string& aObjectID) = 0;
    virtual void BeginGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, FunctorAsync& aFunctor) = 0;
    virtual void EndGetStationButtonAssignment(IAsync& aAsync, std::string& aObjectID) = 0;
    virtual void SetPropertySystemUpdateIDChanged(Functor& aSystemUpdateIDChanged) = 0;
    virtual void PropertySystemUpdateID(uint32_t& aSystemUpdateID) const = 0;
    virtual void SetPropertyContainerUpdateIDsChanged(Functor& aContainerUpdateIDsChanged) = 0;
    virtual void PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const = 0;
    virtual void SetPropertyIndexerStatusChanged(Functor& aIndexerStatusChanged) = 0;
    virtual void PropertyIndexerStatus(std::string& aIndexerStatus) const = 0;
    virtual void SetPropertyA_ARG_TYPE_ScopeChanged(Functor& aA_ARG_TYPE_ScopeChanged) = 0;
    virtual void PropertyA_ARG_TYPE_Scope(std::string& aA_ARG_TYPE_Scope) const = 0;
};

/**
 * Proxy for upnp.org:ContentDirectory_Raumfeld:1
 * @ingroup Proxies
 */
class CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp : public ICpProxyUpnpOrgContentDirectory_Raumfeld1Cpp
{
public:
    /**
     * Constructor.
     *
     * Use iCpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     * @param[in]  aBrowseFlag
     * @param[in]  aFilter
     * @param[in]  aStartingIndex
     * @param[in]  aRequestedCount
     * @param[in]  aSortCriteria
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndBrowse().
     *
     * @param[in] aObjectID
     * @param[in] aBrowseFlag
     * @param[in] aFilter
     * @param[in] aStartingIndex
     * @param[in] aRequestedCount
     * @param[in] aSortCriteria
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aSearchCriteria
     * @param[in]  aFilter
     * @param[in]  aStartingIndex
     * @param[in]  aRequestedCount
     * @param[in]  aSortCriteria
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSearch().
     *
     * @param[in] aContainerID
     * @param[in] aSearchCriteria
     * @param[in] aFilter
     * @param[in] aStartingIndex
     * @param[in] aRequestedCount
     * @param[in] aSortCriteria
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aSelection
     * @param[out] aPlaylistID
     * @param[out] aPlaylistMetadata
     */
    void SyncShuffle(const std::string& aContainerID, const std::string& aSelection, std::string& aPlaylistID, std::string& aPlaylistMetadata);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndShuffle().
     *
     * @param[in] aContainerID
     * @param[in] aSelection
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginShuffle(const std::string& aContainerID, const std::string& aSelection, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aPlaylistID
     * @param[out] aPlaylistMetadata
     */
    void EndShuffle(IAsync& aAsync, std::string& aPlaylistID, std::string& aPlaylistMetadata);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSearchCaps
     */
    void SyncGetSearchCapabilities(std::string& aSearchCaps);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSearchCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSearchCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSearchCaps
     */
    void EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSortCaps
     */
    void SyncGetSortCapabilities(std::string& aSortCaps);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSortCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSortCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSortCaps
     */
    void EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aObjectID
     * @param[out] aNewID
     */
    void SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndCreateReference().
     *
     * @param[in] aContainerID
     * @param[in] aObjectID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNewID
     */
    void EndCreateReference(IAsync& aAsync, std::string& aNewID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aQueueID
     * @param[in]  aContainerID
     * @param[in]  aSourceID
     * @param[in]  aSearchCriteria
     * @param[in]  aSortCriteria
     * @param[in]  aStartIndex
     * @param[in]  aEndIndex
     * @param[in]  aPosition
     */
    void SyncAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAddContainerToQueue().
     *
     * @param[in] aQueueID
     * @param[in] aContainerID
     * @param[in] aSourceID
     * @param[in] aSearchCriteria
     * @param[in] aSortCriteria
     * @param[in] aStartIndex
     * @param[in] aEndIndex
     * @param[in] aPosition
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAddContainerToQueue(const std::string& aQueueID, const std::string& aContainerID, const std::string& aSourceID, const std::string& aSearchCriteria, const std::string& aSortCriteria, uint32_t aStartIndex, uint32_t aEndIndex, uint32_t aPosition, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndAddContainerToQueue(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aQueueID
     * @param[in]  aObjectID
     * @param[in]  aPosition
     */
    void SyncAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAddItemToQueue().
     *
     * @param[in] aQueueID
     * @param[in] aObjectID
     * @param[in] aPosition
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAddItemToQueue(const std::string& aQueueID, const std::string& aObjectID, uint32_t aPosition, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndAddItemToQueue(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aQueueID
     * @param[in]  aFromPosition
     * @param[in]  aToPosition
     * @param[out] aContainerUpdateID
     */
    void SyncRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, uint32_t& aContainerUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRemoveFromQueue().
     *
     * @param[in] aQueueID
     * @param[in] aFromPosition
     * @param[in] aToPosition
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRemoveFromQueue(const std::string& aQueueID, uint32_t aFromPosition, uint32_t aToPosition, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aContainerUpdateID
     */
    void EndRemoveFromQueue(IAsync& aAsync, uint32_t& aContainerUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aDesiredName
     * @param[in]  aContainerID
     * @param[out] aGivenName
     * @param[out] aQueueID
     * @param[out] aMetaData
     */
    void SyncCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndCreateQueue().
     *
     * @param[in] aDesiredName
     * @param[in] aContainerID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginCreateQueue(const std::string& aDesiredName, const std::string& aContainerID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aGivenName
     * @param[out] aQueueID
     * @param[out] aMetaData
     */
    void EndCreateQueue(IAsync& aAsync, std::string& aGivenName, std::string& aQueueID, std::string& aMetaData);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aQueueID
     * @param[in]  aDesiredName
     * @param[out] aGivenName
     */
    void SyncRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, std::string& aGivenName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRenameQueue().
     *
     * @param[in] aQueueID
     * @param[in] aDesiredName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRenameQueue(const std::string& aQueueID, const std::string& aDesiredName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aGivenName
     */
    void EndRenameQueue(IAsync& aAsync, std::string& aGivenName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     * @param[in]  aNewPosition
     * @param[out] aContainerUpdateID
     */
    void SyncMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, uint32_t& aContainerUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndMoveInQueue().
     *
     * @param[in] aObjectID
     * @param[in] aNewPosition
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginMoveInQueue(const std::string& aObjectID, uint32_t aNewPosition, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aContainerUpdateID
     */
    void EndMoveInQueue(IAsync& aAsync, uint32_t& aContainerUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     */
    void SyncDestroyObject(const std::string& aObjectID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDestroyObject().
     *
     * @param[in] aObjectID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDestroyObject(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aScope
     */
    void SyncResetDatabase(const std::string& aScope);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndResetDatabase().
     *
     * @param[in] aScope
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginResetDatabase(const std::string& aScope, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndResetDatabase(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aId
     */
    void SyncGetSystemUpdateID(uint32_t& aId);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSystemUpdateID().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSystemUpdateID(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aId
     */
    void EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aStatus
     */
    void SyncGetIndexerStatus(std::string& aStatus);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetIndexerStatus().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetIndexerStatus(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aStatus
     */
    void EndGetIndexerStatus(IAsync& aAsync, std::string& aStatus);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceID
     * @param[out] aNumTracks
     * @param[out] aTotalSize
     * @param[out] aTotalDuration
     * @param[out] aScanProgress
     * @param[out] aIndexerResult
     */
    void SyncGetSourceInfo(const std::string& aSourceID, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSourceInfo().
     *
     * @param[in] aSourceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSourceInfo(const std::string& aSourceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNumTracks
     * @param[out] aTotalSize
     * @param[out] aTotalDuration
     * @param[out] aScanProgress
     * @param[out] aIndexerResult
     */
    void EndGetSourceInfo(IAsync& aAsync, uint32_t& aNumTracks, uint32_t& aTotalSize, uint32_t& aTotalDuration, uint32_t& aScanProgress, std::string& aIndexerResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceID
     * @param[in]  aRescanMode
     */
    void SyncRescanSource(const std::string& aSourceID, const std::string& aRescanMode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRescanSource().
     *
     * @param[in] aSourceID
     * @param[in] aRescanMode
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRescanSource(const std::string& aSourceID, const std::string& aRescanMode, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndRescanSource(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aCurrentNumResources
     * @param[out] aCriticalNumResources
     * @param[out] aCurrentDiskUsage
     * @param[out] aMaxDiskUsage
     */
    void SyncQueryDatabaseState(uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndQueryDatabaseState().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginQueryDatabaseState(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentNumResources
     * @param[out] aCriticalNumResources
     * @param[out] aCurrentDiskUsage
     * @param[out] aMaxDiskUsage
     */
    void EndQueryDatabaseState(IAsync& aAsync, uint32_t& aCurrentNumResources, uint32_t& aCriticalNumResources, uint32_t& aCurrentDiskUsage, uint32_t& aMaxDiskUsage);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aRenderer
     * @param[in]  aButton
     * @param[in]  aObjectID
     */
    void SyncAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAssignStationButton().
     *
     * @param[in] aRenderer
     * @param[in] aButton
     * @param[in] aObjectID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAssignStationButton(const std::string& aRenderer, uint32_t aButton, const std::string& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndAssignStationButton(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aRenderer
     * @param[in]  aButton
     * @param[out] aObjectID
     */
    void SyncGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, std::string& aObjectID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetStationButtonAssignment().
     *
     * @param[in] aRenderer
     * @param[in] aButton
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetStationButtonAssignment(const std::string& aRenderer, uint32_t aButton, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aObjectID
     */
    void EndGetStationButtonAssignment(IAsync& aAsync, std::string& aObjectID);

    /**
     * Set a callback to be run when the SystemUpdateID state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySystemUpdateIDChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ContainerUpdateIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyContainerUpdateIDsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the IndexerStatus state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyIndexerStatusChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the A_ARG_TYPE_Scope state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory_Raumfeld1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyA_ARG_TYPE_ScopeChanged(Functor& aFunctor);

    /**
     * Query the value of the SystemUpdateID property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSystemUpdateID
     */
    void PropertySystemUpdateID(uint32_t& aSystemUpdateID) const;
    /**
     * Query the value of the ContainerUpdateIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aContainerUpdateIDs
     */
    void PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const;
    /**
     * Query the value of the IndexerStatus property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aIndexerStatus
     */
    void PropertyIndexerStatus(std::string& aIndexerStatus) const;
    /**
     * Query the value of the A_ARG_TYPE_Scope property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aA_ARG_TYPE_Scope
     */
    void PropertyA_ARG_TYPE_Scope(std::string& aA_ARG_TYPE_Scope) const;
    /**
    * This function exposes the Subscribe() function of the iCpProxy member variable
    */
    void Subscribe();
    /**
    * This function exposes the Unsubscribe() function of the iCpProxy member variable
    */
    void Unsubscribe();
    /**
    * This function exposes the SetPropertyChanged() function of the iCpProxy member variable
    */
    void SetPropertyChanged(Functor& aFunctor);
    /**
    * This function exposes the SetPropertyInitialEvent() function of the iCpProxy member variable
    */
    void SetPropertyInitialEvent(Functor& aFunctor);
    /**
    * This function exposes the AddProperty() function of the iCpProxy member variable
    */
    void AddProperty(Property* aProperty);
    /**
    * This function exposes DestroyService() function of the iCpProxy member variable
    */
    void DestroyService();
    /**
    * This function exposes the REportEvent() function of the iCpProxy member variable
    */
    void ReportEvent(Functor aFunctor);
    /**
    * This function exposes the Version() function of the iCpProxy member variable
    */
    TUint Version() const;
private:
    CpProxy iCpProxy;
    void SystemUpdateIDPropertyChanged();
    void ContainerUpdateIDsPropertyChanged();
    void IndexerStatusPropertyChanged();
    void A_ARG_TYPE_ScopePropertyChanged();
private:
    Action* iActionBrowse;
    Action* iActionSearch;
    Action* iActionShuffle;
    Action* iActionGetSearchCapabilities;
    Action* iActionGetSortCapabilities;
    Action* iActionCreateReference;
    Action* iActionAddContainerToQueue;
    Action* iActionAddItemToQueue;
    Action* iActionRemoveFromQueue;
    Action* iActionCreateQueue;
    Action* iActionRenameQueue;
    Action* iActionMoveInQueue;
    Action* iActionDestroyObject;
    Action* iActionResetDatabase;
    Action* iActionGetSystemUpdateID;
    Action* iActionGetIndexerStatus;
    Action* iActionGetSourceInfo;
    Action* iActionRescanSource;
    Action* iActionQueryDatabaseState;
    Action* iActionAssignStationButton;
    Action* iActionGetStationButtonAssignment;
    PropertyUint* iSystemUpdateID;
    PropertyString* iContainerUpdateIDs;
    PropertyString* iIndexerStatus;
    PropertyString* iA_ARG_TYPE_Scope;
    Functor iSystemUpdateIDChanged;
    Functor iContainerUpdateIDsChanged;
    Functor iIndexerStatusChanged;
    Functor iA_ARG_TYPE_ScopeChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGCONTENTDIRECTORY_RAUMFELD1CPP

