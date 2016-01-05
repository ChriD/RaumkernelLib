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
                             
            protected:                
                virtual void createProxyAvTransport() override;
                virtual void createProxyConnectionManager() override;
                virtual void createProxyRenderingControl() override;

                virtual void playProxy(bool _sync = true) override;
                virtual void stopProxy(bool _sync = true) override;
                virtual void pauseProxy(bool _sync = true) override;
                virtual void nextProxy(bool _sync = true) override;
                virtual void previousProxy(bool _sync = true) override;

                virtual void onPlayExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onStopExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onPauseExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onNextExecuted(OpenHome::Net::IAsync& _aAsync) override;
                virtual void onPreviousExecuted(OpenHome::Net::IAsync& _aAsync) override;

        };

    }

}


#endif
