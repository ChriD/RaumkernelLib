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
#ifndef RAUMKERNEL_RAUMKERNEL_H
#define RAUMKERNEL_RAUMKERNEL_H

#include <raumkernel/raumkernelBaseMgr.h>
#include <raumkernel/device/deviceMediaServer.h>
#include <raumkernel/versionInfo.h>


namespace Raumkernel
{

    class Raumkernel : public RaumkernelBaseMgr
    {
        public:
            EXPORT Raumkernel();
            EXPORT virtual ~Raumkernel();
            /**
            * initializes the kernel object
            * 'initLogObject' has to be called before if a logger is not set from external source
            */
            EXPORT virtual void init(const std::string &_settingsFileName = "");
            /**
            * initializes the log object
            * has to be called before init!
            */
            EXPORT virtual void initLogObject(Log::LogType _defaultLogLevel = Log::LogType::LOGTYPE_ERROR, const std::string &_logFilePath = "logs/", const std::vector<std::shared_ptr<Log::LogAdapter>> &_adapterList = std::vector<std::shared_ptr<Log::LogAdapter>>());
            /**
            * returns the version info object/structure for the raumkernel
            */
            EXPORT virtual VersionInfo::VersionInfo getVersionInfo();
            /**
            * returns if the raumfeldSystem is online
            */
            virtual bool isRaumfeldSystemOnline();
            /**
            * do a SIGSEV
            */
            EXPORT virtual void raiseSigsegv();
            /**
            *
            */
            EXPORT virtual void addSystemSignalHandlers();
            /**
            * this signal will be fired if a the raumkernel is ready 
            * (in fact that means that the media server is online!)
            */
            sigs::signal<void()> sigRaumfeldSystemOnline;
            /**
            * this signal will be fired if a the raumkernel is ready 
            * (in fact that will be if the media server goes offline!)
            */
            sigs::signal<void()> sigRaumfeldSystemOffline;
            /**
            * this signal will be fired if a log occurs
            */
            sigs::signal<void(Log::LogData)> sigLog;

        protected:
            void onMediaServerAdded(std::shared_ptr<Devices::MediaServer> _mediaServer);
            void onMediaServerRemoved(std::shared_ptr<Devices::MediaServer> _mediaServer);                      
            void onLog(Log::LogData _logData);

            bool isOnline;

            VersionInfo::VersionInfo versionInfo;

            sigs::connections connections;           
    };

}


#endif