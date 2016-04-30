#include "raumkernel/device/proxies/CpUpnpOrgRenderingControl_RaumfeldVirtual1.h"
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


class SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, bool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
    bool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, bool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
};

SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, uint32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
    uint32_t& iCurrentVolume;
};

SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, uint32_t& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoomVolume(aAsync, iCurrentVolume);
}


class SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
};

SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoomVolume(aAsync);
}


class SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, bool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
    bool& iCurrentMute;
};

SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, bool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoomMute(aAsync, iCurrentMute);
}


class SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
};

SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoomMute(aAsync);
}


class SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
};

SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndChangeVolume(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, uint32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
    uint32_t& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy, uint32_t& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& iService;
};

SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp(CpDeviceCpp& aDevice)
    : iCpProxy("schemas-upnp-org", "RenderingControl", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetMute = new Action("GetMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("CurrentMute");
    iActionGetMute->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("DesiredMute");
    iActionSetMute->AddInputParameter(param);

    iActionGetRoomVolume = new Action("GetRoomVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRoomVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Room");
    iActionGetRoomVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentVolume", 0, 100, 1);
    iActionGetRoomVolume->AddOutputParameter(param);

    iActionSetRoomVolume = new Action("SetRoomVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRoomVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Room");
    iActionSetRoomVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredVolume", 0, 100, 1);
    iActionSetRoomVolume->AddInputParameter(param);

    iActionGetRoomMute = new Action("GetRoomMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRoomMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Room");
    iActionGetRoomMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("CurrentMute");
    iActionGetRoomMute->AddOutputParameter(param);

    iActionSetRoomMute = new Action("SetRoomMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRoomMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Room");
    iActionSetRoomMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("DesiredMute");
    iActionSetRoomMute->AddInputParameter(param);

    iActionChangeVolume = new Action("ChangeVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionChangeVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("Amount", -127, 127, 1);
    iActionChangeVolume->AddInputParameter(param);

    iActionGetVolume = new Action("GetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("CurrentVolume", 0, 100, 1);
    iActionGetVolume->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("DesiredVolume", 0, 100, 1);
    iActionSetVolume->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::~CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp()
{
    DestroyService();
    delete iActionGetMute;
    delete iActionSetMute;
    delete iActionGetRoomVolume;
    delete iActionSetRoomVolume;
    delete iActionGetRoomMute;
    delete iActionSetRoomMute;
    delete iActionChangeVolume;
    delete iActionGetVolume;
    delete iActionSetVolume;
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetMute(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginGetMute(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndGetMute(IAsync& aAsync, bool& aCurrentMute)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentMute = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t& aCurrentVolume)
{
    SyncGetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this, aCurrentVolume);
    BeginGetRoomVolume(aInstanceID, aRoom, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginGetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetRoomVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRoomVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aRoom.c_str(), (TUint)aRoom.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRoomVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndGetRoomVolume(IAsync& aAsync, uint32_t& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRoomVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t aDesiredVolume)
{
    SyncSetRoomVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this);
    BeginSetRoomVolume(aInstanceID, aRoom, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginSetRoomVolume(uint32_t aInstanceID, const std::string& aRoom, uint32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSetRoomVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoomVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aRoom.c_str(), (TUint)aRoom.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndSetRoomVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoomVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool& aCurrentMute)
{
    SyncGetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this, aCurrentMute);
    BeginGetRoomMute(aInstanceID, aRoom, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginGetRoomMute(uint32_t aInstanceID, const std::string& aRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetRoomMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRoomMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aRoom.c_str(), (TUint)aRoom.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRoomMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndGetRoomMute(IAsync& aAsync, bool& aCurrentMute)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRoomMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentMute = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool aDesiredMute)
{
    SyncSetRoomMuteUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this);
    BeginSetRoomMute(aInstanceID, aRoom, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginSetRoomMute(uint32_t aInstanceID, const std::string& aRoom, bool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSetRoomMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoomMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aRoom.c_str(), (TUint)aRoom.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndSetRoomMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoomMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncChangeVolume(uint32_t aInstanceID, int32_t aAmount)
{
    SyncChangeVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this);
    BeginChangeVolume(aInstanceID, aAmount, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginChangeVolume(uint32_t aInstanceID, int32_t aAmount, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionChangeVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionChangeVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aAmount));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndChangeVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ChangeVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncGetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginGetVolume(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndGetVolume(IAsync& aAsync, uint32_t& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SyncSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl_RaumfeldVirtual1Cpp sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::BeginSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iLastChangeChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::Subscribe()
{
  iCpProxy.Subscribe();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::Unsubscribe()
{
 iCpProxy.Unsubscribe();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SetPropertyChanged(Functor& aFunctor)
{
  iCpProxy.SetPropertyChanged(aFunctor);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::SetPropertyInitialEvent(Functor& aFunctor)
{
  iCpProxy.SetPropertyInitialEvent(aFunctor);
}
void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::AddProperty(Property* aProperty)
{
  iCpProxy.AddProperty(aProperty);
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::DestroyService()
{
  iCpProxy.DestroyService();
}

void CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::ReportEvent(Functor aFunctor)
{
  iCpProxy.ReportEvent(aFunctor);
}

TUint CpProxyUpnpOrgRenderingControl_RaumfeldVirtual1Cpp::Version() const
{
  return iCpProxy.Version();
}

