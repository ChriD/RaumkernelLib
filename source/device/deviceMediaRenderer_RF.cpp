
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

            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'enterAutomaticStandby' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'enterAutomaticStandby' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                enterAutomaticStandbyProxy(_sync);
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logRendererError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logRendererError("Unknown Exception", CURRENT_FUNCTION);
            }

            
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
                proxy->EndEnterAutomaticStandby(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }



        void MediaRenderer_Raumfeld::enterManualStandby(bool _sync)
        {
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'enterManualStandbyProxy' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'enterManualStandbyProxy' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                enterManualStandbyProxy(_sync);
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logRendererError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logRendererError("Unknown Exception", CURRENT_FUNCTION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
                proxy->EndEnterManualStandby(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }



        void MediaRenderer_Raumfeld::leaveStandby(bool _sync)
        {            
            if (!isAvTransportProxyAvailable())
            {
                logWarning("Calling 'leaveStandbyStandbyProxy' on renderer '" + getDeviceDescription() + "' without AvTransportProxy!", CURRENT_FUNCTION);
                return;
            }

            logDebug("Calling 'leaveStandbyStandbyProxy' on renderer '" + getDeviceDescription() + "'", CURRENT_FUNCTION);

            try
            {
                leaveStandbyStandbyProxy(_sync);
            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::exception &e)
            {
                logRendererError(e.what(), CURRENT_FUNCTION);
            }
            catch (std::string &e)
            {
                logRendererError(e, CURRENT_FUNCTION);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_FUNCTION);
            }
            catch (...)
            {
                logRendererError("Unknown Exception", CURRENT_FUNCTION);
            }
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
            try
            {
                if (!isAvTransportProxyAvailable())
                    return;
                auto proxy = std::dynamic_pointer_cast<OpenHome::Net::CpProxyUpnpOrgAVTransport1Cpp>(getAvTransportProxy());
                proxy->EndLeaveStandby(_aAsync);
            }
            catch (OpenHome::Exception &e)
            {
                logRendererError(e.Message(), CURRENT_POSITION);
            }
            catch (...)
            {
                logRendererError("Unknown exception!", CURRENT_POSITION);
            }
        }


    }

}