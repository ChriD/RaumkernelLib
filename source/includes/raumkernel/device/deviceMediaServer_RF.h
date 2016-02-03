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
#ifndef RAUMKERNEL_DEVICEMEDIARSERVER_RF_H
#define RAUMKERNEL_DEVICEMEDIARSERVER_RF_H

#include <raumkernel/device/deviceMediaServer.h>
#include <raumkernel/device/proxies/CpUpnpOrgContentDirectory_Raumfeld1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager1.h>


namespace Raumkernel
{
    namespace Devices
    {
        class MediaServer_Raumfeld : public MediaServer
        {
            public:
                MediaServer_Raumfeld();
                virtual ~MediaServer_Raumfeld();
                EXPORT virtual bool isRaumfeldMediaServer() override;

            protected:
                virtual void createProxyContentDirectory() override;
                virtual void createProxyConnectionManager() override;

                void searchThreadProxy(std::string _containerId, std::string _searchCriteria, std::string _extraData) override;
                void browseThreadProxy(std::string _containerId, std::string _browseFlag, std::string _extraData) override;
              
                virtual void onContentDirectoryProxyPropertyChanged() override;
                virtual void onContentDirectoryProxyContainerUpdateIdsChanged() override;
                virtual void oConnectionManagerProxyPropertyChanged() override;    

        };

    }
}
#endif