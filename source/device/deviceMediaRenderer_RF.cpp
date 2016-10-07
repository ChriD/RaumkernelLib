
#include <raumkernel/device/deviceMediaRenderer_RF.h>


namespace Raumkernel
{
    namespace Devices
    {

        MediaRenderer_Raumfeld::MediaRenderer_Raumfeld() : MediaRenderer()
        {
        }


        MediaRenderer_Raumfeld::~MediaRenderer_Raumfeld()
        {
        }


        void MediaRenderer_Raumfeld::enterAutomaticStandby(bool _sync)
        {
            enterAutomaticStandbyProxy(_sync);
        }


        void MediaRenderer_Raumfeld::enterAutomaticStandbyProxy(bool _sync)
        {            
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            if (_sync)
                proxy->SyncEnterAutomaticStandby(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_Raumfeld::onEnterAutomaticStandbyExecuted);
                proxy->BeginEnterAutomaticStandby(instance, functorAsync);
            }
        }


        void MediaRenderer_Raumfeld::onEnterAutomaticStandbyExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndEnterAutomaticStandby(_aAsync);
        }



        void MediaRenderer_Raumfeld::enterManualStandby(bool _sync)
        {
            enterManualStandbyProxy(_sync);
        }


        void MediaRenderer_Raumfeld::enterManualStandbyProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            if (_sync)
                proxy->SyncEnterManualStandby(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_Raumfeld::onEnterManualStandbyExecuted);
                proxy->BeginEnterManualStandby(instance, functorAsync);
            }
        }


        void MediaRenderer_Raumfeld::onEnterManualStandbyExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndEnterManualStandby(_aAsync);
        }



        void MediaRenderer_Raumfeld::leaveStandby(bool _sync)
        {
            leaveStandbyStandbyProxy(_sync);
        }


        void MediaRenderer_Raumfeld::leaveStandbyStandbyProxy(bool _sync)
        {
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            if (_sync)
                proxy->SyncLeaveStandby(instance);
            else
            {
                OpenHome::Net::FunctorAsync functorAsync = OpenHome::Net::MakeFunctorAsync(*this, &MediaRenderer_Raumfeld::onLeaveStandbyStandbyExecuted);
                proxy->BeginLeaveStandby(instance, functorAsync);
            }
        }


        void MediaRenderer_Raumfeld::onLeaveStandbyStandbyExecuted(OpenHome::Net::IAsync& _aAsync)
        {
            if (!isAvTransportProxyAvailable())
                return;
            auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
            proxy->EndLeaveStandby(_aAsync);
        }


    }

}