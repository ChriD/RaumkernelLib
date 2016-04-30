#include "raumkernel/device/proxies/CpUpnpOrgConnectionManager_RaumfeldVirtual1.h"
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


class SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, std::string& aSource, std::string& aSink);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& iService;
    std::string& iSource;
    std::string& iSink;
};

SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, std::string& aSource, std::string& aSink)
    : iService(aProxy)
    , iSource(aSource)
    , iSink(aSink)
{
}

void SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetProtocolInfo(aAsync, iSource, iSink);
}


class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, std::string& aConnectionIDs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& iService;
    std::string& iConnectionIDs;
};

SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, std::string& aConnectionIDs)
    : iService(aProxy)
    , iConnectionIDs(aConnectionIDs)
{
}

void SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionIDs(aAsync, iConnectionIDs);
}


class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& iService;
    int32_t& iRcsID;
    int32_t& iAVTransportID;
    std::string& iProtocolInfo;
    std::string& iPeerConnectionManager;
    int32_t& iPeerConnectionID;
    std::string& iDirection;
    std::string& iStatus;
};

SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp& aProxy, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
    : iService(aProxy)
    , iRcsID(aRcsID)
    , iAVTransportID(aAVTransportID)
    , iProtocolInfo(aProtocolInfo)
    , iPeerConnectionManager(aPeerConnectionManager)
    , iPeerConnectionID(aPeerConnectionID)
    , iDirection(aDirection)
    , iStatus(aStatus)
{
}

void SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionInfo(aAsync, iRcsID, iAVTransportID, iProtocolInfo, iPeerConnectionManager, iPeerConnectionID, iDirection, iStatus);
}


CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp(CpDeviceCpp& aDevice)
    : iCpProxy("schemas-upnp-org", "ConnectionManager", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetProtocolInfo = new Action("GetProtocolInfo");
    param = new OpenHome::Net::ParameterString("Source");
    iActionGetProtocolInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Sink");
    iActionGetProtocolInfo->AddOutputParameter(param);

    iActionGetCurrentConnectionIDs = new Action("GetCurrentConnectionIDs");
    param = new OpenHome::Net::ParameterString("ConnectionIDs");
    iActionGetCurrentConnectionIDs->AddOutputParameter(param);

    iActionGetCurrentConnectionInfo = new Action("GetCurrentConnectionInfo");
    param = new OpenHome::Net::ParameterInt("ConnectionID");
    iActionGetCurrentConnectionInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("RcsID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("AVTransportID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ProtocolInfo");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("PeerConnectionManager");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("PeerConnectionID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    param = new OpenHome::Net::ParameterString("Direction", allowedValues, 2);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ContentFormatMismatch";
    allowedValues[index++] = (TChar*)"InsufficientBandwidth";
    allowedValues[index++] = (TChar*)"UnreliableChannel";
    allowedValues[index++] = (TChar*)"Unknown";
    param = new OpenHome::Net::ParameterString("Status", allowedValues, 5);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SourceProtocolInfoPropertyChanged);
    iSourceProtocolInfo = new PropertyString("SourceProtocolInfo", functor);
    AddProperty(iSourceProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SinkProtocolInfoPropertyChanged);
    iSinkProtocolInfo = new PropertyString("SinkProtocolInfo", functor);
    AddProperty(iSinkProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CurrentConnectionIDsPropertyChanged);
    iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs", functor);
    AddProperty(iCurrentConnectionIDs);
}

CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::~CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp()
{
    DestroyService();
    delete iActionGetProtocolInfo;
    delete iActionGetCurrentConnectionIDs;
    delete iActionGetCurrentConnectionInfo;
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetProtocolInfo(std::string& aSource, std::string& aSink)
{
    SyncGetProtocolInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp sync(*this, aSource, aSink);
    BeginGetProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::BeginGetProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::EndGetProtocolInfo(IAsync& aAsync, std::string& aSource, std::string& aSink)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetProtocolInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSource.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSink.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetCurrentConnectionIDs(std::string& aConnectionIDs)
{
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager_RaumfeldVirtual1Cpp sync(*this, aConnectionIDs);
    BeginGetCurrentConnectionIDs(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetCurrentConnectionIDs, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionIDs->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::EndGetCurrentConnectionIDs(IAsync& aAsync, std::string& aConnectionIDs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionIDs"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aConnectionIDs.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SyncGetCurrentConnectionInfo(int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
{
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager_RaumfeldVirtual1Cpp sync(*this, aRcsID, aAVTransportID, aProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, aStatus);
    BeginGetCurrentConnectionInfo(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::BeginGetCurrentConnectionInfo(int32_t aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetCurrentConnectionInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetCurrentConnectionInfo->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionInfo->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::EndGetCurrentConnectionInfo(IAsync& aAsync, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aRcsID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAVTransportID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPeerConnectionManager.assign((const char*)val.Ptr(), val.Bytes());
    }
    aPeerConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aDirection.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SetPropertySourceProtocolInfoChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iSourceProtocolInfoChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SetPropertySinkProtocolInfoChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iSinkProtocolInfoChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor)
{
    iCpProxy.GetLock().Wait();
    iCurrentConnectionIDsChanged = aFunctor;
    iCpProxy.GetLock().Signal();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::PropertySourceProtocolInfo(std::string& aSourceProtocolInfo) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iSourceProtocolInfo->Value();
    aSourceProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::PropertySinkProtocolInfo(std::string& aSinkProtocolInfo) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iSinkProtocolInfo->Value();
    aSinkProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::PropertyCurrentConnectionIDs(std::string& aCurrentConnectionIDs) const
{
    AutoMutex a(iCpProxy.PropertyReadLock());
    ASSERT(iCpProxy.GetSubscriptionStatus() == CpProxy::eSubscribed);
    const Brx& val = iCurrentConnectionIDs->Value();
    aCurrentConnectionIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SourceProtocolInfoPropertyChanged()
{
    ReportEvent(iSourceProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SinkProtocolInfoPropertyChanged()
{
    ReportEvent(iSinkProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::CurrentConnectionIDsPropertyChanged()
{
    ReportEvent(iCurrentConnectionIDsChanged);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::Subscribe()
{
  iCpProxy.Subscribe();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::Unsubscribe()
{
 iCpProxy.Unsubscribe();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SetPropertyChanged(Functor& aFunctor)
{
  iCpProxy.SetPropertyChanged(aFunctor);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::SetPropertyInitialEvent(Functor& aFunctor)
{
  iCpProxy.SetPropertyInitialEvent(aFunctor);
}
void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::AddProperty(Property* aProperty)
{
  iCpProxy.AddProperty(aProperty);
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::DestroyService()
{
  iCpProxy.DestroyService();
}

void CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::ReportEvent(Functor aFunctor)
{
  iCpProxy.ReportEvent(aFunctor);
}

TUint CpProxyUpnpOrgConnectionManager_RaumfeldVirtual1Cpp::Version() const
{
  return iCpProxy.Version();
}

