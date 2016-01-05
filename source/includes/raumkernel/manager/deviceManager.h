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
#ifndef RAUMKERNEL_DEVICESMANAGER_H
#define RAUMKERNEL_DEVICESMANAGER_H

#include <map>
#include <unordered_map>
#include <raumkernel/manager/managerBase.h>
#include <raumkernel/device/deviceMediaRenderer.h>
#include <raumkernel/device/deviceCreator.h>

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>


namespace Raumkernel
{
    namespace Manager
    {
        /**
        * The DeviceManager
        *
        * This class handles all the devices found on the network stack and creats/holds the appropriate wrapper classes like Renderer / MediaServer
        */
        class DeviceManager : public ManagerBase
        {
            public:
                EXPORT DeviceManager();
                EXPORT virtual ~DeviceManager();   

                /**
                * Not intended for external use
                * Adds a ohNet UPNP Device and the appropriate wrapper class
                */
                void addDevice(OpenHome::Net::CpDeviceCpp& _device);
                /**
                * Not intended for external use
                * Removes a ohNet UPNP Device and the appropriate wrapper class
                */
                void removeDevice(OpenHome::Net::CpDeviceCpp& _device);

                /**               
                * locks the internal device lists
                * device lists should always be locked when updateing the list or when performing an action on any of those devices
                * do not forget to unlock those lists again
                */
                void lockDeviceList();
                /**             
                * unlocks the internal device lists
                * device lists should always be locked when updateing the list or when performing an action on any of those devices
                * do not forget to unlock those lists again
                */
                void unlockDeviceList();
                /**
                * Returns a shared pointer to a media renderer device
                * Returns nullptr if no devive was found!
                * do not forget to lock / unock the internal list when using the media renderer object
                */
                EXPORT std::shared_ptr<Devices::MediaRenderer> getMediaRenderer(std::string _udn);


                /**
                * this signal will be fired if a media renderer was added to the internal list. 
                * Be aware that this signal is not within the mutexlock scope of the list
                * Therefore if you want to call any method on the renderer you should lock the deviceManager list
                */
                sigs::signal<void(std::shared_ptr<Devices::MediaRenderer>)> sigMediaRendererAdded;
                /**
                * this signal will be fired if a media renderer was removed from the internal list.
                * Be aware that this signal is not within the mutexlock scope of the list
                * Be aware that calling methods on the renderer may fail!
                */
                sigs::signal<void(std::shared_ptr<Devices::MediaRenderer>)> sigMediaRendererRemoved;
                //sigs::signal<void(std::shared_ptr<Devices::MediaServer>)> sigMediaServerAdded;
                //sigs::signal<void(std::shared_ptr<Devices::MediaServer>)> sigMediaServerRemoved;
                //sigs::signal<void(std::shared_ptr<Devices::ConfigDevice>)> sigConfigDeviceAdded;
                //sigs::signal<void(std::shared_ptr<Devices::ConfigDevice>)> sigConfigDeviceRemoved;

                /**
                * this signal will be fired if a usable device (MediaServer, MediaRenderer, ...) was added to the internal list.
                * Be aware that this signal is not within the mutexlock scope of the list
                * Therefore if you want to call any method on the renderer you should lock the deviceManager list
                */
                sigs::signal<void()> sigDeviceListChanged;

            protected:
              
                // this list holds references to all the UPNP devices found by the UPNP control point, no matter if they ar usable by th kenrel or not
                std::unordered_map<std::string, OpenHome::Net::CpDeviceCpp*> upnpDeviceMap;

                std::unordered_map<std::string, std::shared_ptr<Devices::MediaRenderer>> mediaRendererMap;
                //std::unordered_map<std::string, std::shared_ptr<Devices::MediaServer>> mediaServersMap;
                //std::shared_ptr<Devices::ConfigDevice>

                // a mutex that will secure our device lists
                std::mutex		mutexDeviceLists;

               


        };
    }
}


#endif