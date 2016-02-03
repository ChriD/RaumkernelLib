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


#include <thread>
#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpProxy.h>
#include <raumkernel/signals/signals.hpp>
#include <raumkernel/tools/uriUtil.h>
#include <raumkernel/device/device.h>
#include <raumkernel/device/proxies/CpUpnpOrgContentDirectory1.h>
#include <raumkernel/device/proxies/CpUpnpOrgConnectionManager1.h>


namespace Raumkernel
{
    namespace Devices
    {
        enum class MediaServer_BrowseFlag { MSBF_BrowseDirectChildren, MSBF_BrowseMetadata };

        class MediaServer : public Device
        {
            public:
                MediaServer();
                virtual ~MediaServer();
                /**
                * Searches the media server with the given values
                * You have to subscribe to "searchExecuted" to get the result!
                */
                EXPORT virtual void search(std::string _containerId, std::string _searchCriteria = "", std::string _extraData = "", bool _sync = false);
                /**
                * Browses the media server with the given values
                * You have to subscribe to "browseExecuted" to get the result!
                */
                EXPORT virtual void browse(std::string _containerId, MediaServer_BrowseFlag _browseFlag = MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, std::string _extraData = "", bool _sync = false);
                /**
                * creates a valid avTransportUri for a container id 
                * this uri  can be used for bending or setting the uri on a renderer
                */
                EXPORT virtual std::string createAVTransportUri_Container(std::string _containerId, std::int32_t _trackIndex = -1);
                /**
                * creates a valid avTransportUri for a container id
                * this uri  can be used for bending or setting the uri on a renderer
                */
                EXPORT virtual std::string createAVTransportUri_Single(std::string _singleId);
                /**
                * Returne 'true' if the mesia server is the Raumfeld Media Server
                */
                EXPORT virtual bool isRaumfeldMediaServer();


                sigs::signal<void(const std::string, std::uint32_t, std::uint32_t, std::uint32_t, const std::string)> sigSearchExecuted;
                sigs::signal<void(const std::string, std::uint32_t, std::uint32_t, std::uint32_t, const std::string)> sigBrowseExecuted;

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

                virtual void searchThread(std::string _containerId, std::string _searchCriteria = "", std::string _extraData = "");
                virtual void browseThread(std::string _containerId, MediaServer_BrowseFlag _browseFlag = MediaServer_BrowseFlag::MSBF_BrowseDirectChildren, std::string _extraData = "");

                virtual void searchThreadProxy(std::string _containerId, std::string _searchCriteria, std::string _extraData);
                virtual void browseThreadProxy(std::string _containerId, std::string _browseFlag, std::string _extraData);

                virtual void searchThreadExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData);
                virtual void browseThreadExecuted(std::string _result, std::uint32_t _numberReturned, std::uint32_t _totalMatches, std::uint32_t _updateId, std::string _extraData);

                virtual void onContentDirectoryProxyPropertyChanged();
                virtual void onContentDirectoryProxyContainerUpdateIdsChanged();
                virtual void oConnectionManagerProxyPropertyChanged();                           

        };

    }
}
#endif