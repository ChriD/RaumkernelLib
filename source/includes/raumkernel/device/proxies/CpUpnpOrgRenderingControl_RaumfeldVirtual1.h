#ifndef HEADER_UPNPORGRENDERINGCONTROL_RAUMFELDVIRTUAL1CPP
#define HEADER_UPNPORGRENDERINGCONTROL_RAUMFELDVIRTUAL1CPP

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

/**
 * Proxy for upnp.org:RenderingControl_RaumfeldVirtual:1
 * @ingroup Proxies
 */
class CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public CpProxy
{
public:
    /**
     * Constructor.
     *
     * Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentMute
     */
    void SyncGetMute(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetMute().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetMute(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentMute
     */
    void EndGetMute(IAsync& aAsync, bool& aCurrentMute);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredMute
     */
    void SyncSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetMute().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredMute
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetMute(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aRoom
     * @param[out] aCurrentVolume
     */
    void SyncGetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t& aCurrentVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetRoomVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aRoom
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentVolume
     */
    void EndGetRoomVolume(IAsync& aAsync, uint32_t& aCurrentVolume);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aRoom
     * @param[in]  aDesiredVolume
     */
    void SyncSetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t aDesiredVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRoomVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aRoom
     * @param[in] aDesiredVolume
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t aDesiredVolume, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRoomVolume(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aRoom
     * @param[out] aCurrentMute
     */
    void SyncGetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool& aCurrentMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetRoomMute().
     *
     * @param[in] aInstanceID
     * @param[in] aRoom
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetRoomMute(uint32_t aInstanceID, const std::string& aRoom, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentMute
     */
    void EndGetRoomMute(IAsync& aAsync, bool& aCurrentMute);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aRoom
     * @param[in]  aDesiredMute
     */
    void SyncSetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool aDesiredMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRoomMute().
     *
     * @param[in] aInstanceID
     * @param[in] aRoom
     * @param[in] aDesiredMute
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool aDesiredMute, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRoomMute(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aAmount
     */
    void SyncChangeVolume(uint32_t aInstanceID, int32_t aAmount);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndChangeVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aAmount
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginChangeVolume(uint32_t aInstanceID, int32_t aAmount, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndChangeVolume(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentVolume
     */
    void SyncGetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetVolume(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentVolume
     */
    void EndGetVolume(IAsync& aAsync, uint32_t& aCurrentVolume);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredVolume
     */
    void SyncSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredVolume
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetVolume(IAsync& aAsync);

    /**
     * Set a callback to be run when the LastChange state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyLastChangeChanged(Functor& aFunctor);

    /**
     * Query the value of the LastChange property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aLastChange
     */
    void PropertyLastChange(std::string& aLastChange) const;
private:
    void LastChangePropertyChanged();
private:
    Action* iActionGetMute;
    Action* iActionSetMute;
    Action* iActionGetRoomVolume;
    Action* iActionSetRoomVolume;
    Action* iActionGetRoomMute;
    Action* iActionSetRoomMute;
    Action* iActionChangeVolume;
    Action* iActionGetVolume;
    Action* iActionSetVolume;
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGRENDERINGCONTROL_RAUMFELDVIRTUAL1CPP

