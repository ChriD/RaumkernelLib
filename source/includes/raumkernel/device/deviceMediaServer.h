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
#ifndef RAUMKERNEL_DEVICEMEDIARSERVER_H
#define RAUMKERNEL_DEVICEMEDIARSERVER_H


#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpProxy.h>
#include <raumkernel/signals/signals.hpp>
#include <raumkernel/device/device.h>
#include <raumkernel/device/proxies/CpUpnpOrgContentDirectory1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager1.h>


namespace Raumkernel
{
    namespace Devices
    {
        class MediaServer : public Device
        {
            public:
                MediaServer();
                virtual ~MediaServer();

            protected:
                // proxies of the media server device                
                std::shared_ptr<OpenHome::Net::CpProxy>	contentDirectoryProxy;
                std::shared_ptr<OpenHome::Net::CpProxy>	connectionManagerProxy;

                virtual void deleteProxies() override;
                virtual void createProxies() override;

                virtual void createProxyContentDirectory();
                virtual void createProxyConnectionManager(); 

                bool isContentDirectoryProxyAvailable();
                bool isConnectionManagerProxyAvailable();

                std::shared_ptr<OpenHome::Net::CpProxy> getContentDirectoryProxy();
                std::shared_ptr<OpenHome::Net::CpProxy> getConnectionManagerProxy();

                void logServerError(std::string _error, std::string _location);

                virtual void onContentDirectoryProxyPropertyChanged();
                virtual void onContentDirectoryProxyContainerUpdateIdsChanged();
                virtual void oConnectionManagerProxyPropertyChanged();                

        };

    }
}
#endif