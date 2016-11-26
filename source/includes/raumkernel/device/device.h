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
#ifndef RAUMKERNEL_DEVICE_H
#define RAUMKERNEL_DEVICE_H

#include <raumkernel/raumkernelBaseMgr.h>

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>

namespace Raumkernel
{
    namespace Devices
    {
        class Device : public RaumkernelBaseMgr
        {
            public:
                EXPORT Device();
                EXPORT virtual ~Device();

                void setUDN(std::string _UDN);
                void setDeviceType(std::string _deviceType);
                void setFriendlyName(std::string _friendlyName);
                void setModelName(std::string _modelName);
                void setModelDescription(std::string _modelDescription);
                void setManufacturer(std::string _manufacturer);
                void setManufacturerUrl(std::string _manufacturerUrl);
                void setDeviceXML(std::string _deviceXML);
                void setModelNumber(std::string _modelNumber);
                void setSerialNumber(std::string _serialNumber);
                void setIsRaumfeldDevice(bool _isRaumfeldDevice);

                void setCpDevice(OpenHome::Net::CpDeviceCpp* _cpDevice);

                EXPORT std::string getUDN();
                EXPORT std::string getDeviceType();
                EXPORT std::string getFriendlyName();
                EXPORT std::string getModelName();
                EXPORT std::string getModelDescription();
                EXPORT std::string getManufacturer();
                EXPORT std::string getManufacturerUrl();
                EXPORT std::string getDeviceXML();
                EXPORT std::string getModelNumber();
                EXPORT std::string getSerialNumber();
                EXPORT std::string getDeviceDescription();
                EXPORT bool getIsRaumfeldDevice();

            protected:
                std::string UDN;
                std::string deviceType;
                std::string friendlyName;
                std::string modelName;
                std::string modelDescription;
                std::string manufacturer;
                std::string manufacturerUrl;
                std::string deviceXML;
                std::string modelNumber;
                std::string serialNumber;
                bool isRaumfeldDevice;

                // because the ohNet gives us a raw pointer instead a shared one we are sticked to this raw pointer
                // not very nice but if we handle it with care it should be no problem
                OpenHome::Net::CpDeviceCpp* cpDevice;

                virtual void addSubscriptions();
                virtual void removeSubscriptions();
                virtual void createProxies();
                virtual void deleteProxies();
                virtual void cpDeviceLost();
        };

    }
}

#endif