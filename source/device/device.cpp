
#include <raumkernel/device/device.h>


namespace Raumkernel
{
    namespace Devices
    {
        Device::Device() : RaumkernelBaseMgr()
        {
            cpDevice = nullptr;
            UDN = "";
            deviceType = "";
            friendlyName = "";
            modelName = "";
            modelDescription = "";
            manufacturer = "";
            manufacturerUrl = "";
            deviceXML = "";
            modelNumber = "";
            serialNumber = "";
        }

        Device::~Device()
        {
            // no need to remove subscriptions! delete of proxies will handle this correct!
            deleteProxies();   
        }

        void Device::setUDN(std::string _UDN)
        {
            UDN = _UDN;
        }

        void Device::setDeviceType(std::string _deviceType)
        {
            deviceType = _deviceType;
        }

        void Device::setFriendlyName(std::string _friendlyName)
        {
            friendlyName = _friendlyName;
        }

        void Device::setModelName(std::string _modelName)
        {
            modelName = _modelName;
        }

        void Device::setModelDescription(std::string _modelDescription)
        {
            modelDescription = _modelDescription;
        }

        void Device::setManufacturer(std::string _manufacturer)
        {
            manufacturer = _manufacturer;
        }

        void Device::setManufacturerUrl(std::string _manufacturerUrl)
        {
            manufacturerUrl = _manufacturerUrl;
        }

        void Device::setDeviceXML(std::string _deviceXML)
        {
            deviceXML = _deviceXML;
        }

        void Device::setModelNumber(std::string _modelNumber)
        {
            modelNumber = _modelNumber;
        }

        void Device::setSerialNumber(std::string _serialNumber)
        {
            serialNumber = _serialNumber;
        }

        std::string Device::getUDN()
        {
            return UDN;
        }

        std::string Device::getDeviceType()
        {
            return deviceType;
        }

        std::string Device::getFriendlyName()
        {
            return friendlyName;
        }

        std::string Device::getModelName()
        {
            return modelName;
        }

        std::string Device::getModelDescription()
        {
            return modelDescription;
        }

        std::string Device::getManufacturer()
        {
            return manufacturer;
        }

        std::string Device::getManufacturerUrl()
        {
            return manufacturerUrl;
        }

        std::string Device::getDeviceXML()
        {
            return deviceXML;
        }

        std::string Device::getModelNumber()
        {
            return modelNumber;
        }

        std::string Device::getSerialNumber()
        {
            return serialNumber;
        }

        std::string Device::getDeviceDescription()
        {
            return UDN;
        }


        void Device::setCpDevice(OpenHome::Net::CpDeviceCpp *_cpDevice)
        {      
            cpDevice = _cpDevice;
            if (cpDevice)
            {
                createProxies();
                addSubscriptions();
            }
            else
                cpDeviceLost();
        }

        void Device::cpDeviceLost()
        {
            deleteProxies();
        }

        void Device::createProxies()
        {
            // overload this method to create the proxies
        }

        void Device::deleteProxies()
        {
            // overload this method to delete the created proxies in "CreateProxies"
        }

        void Device::addSubscriptions()
        {
            // overload this method to add subscriptions to upnp services
        }

        void Device::removeSubscriptions()
        {
            // overload this method to add subscriptions to upnp services
        }
    }

}