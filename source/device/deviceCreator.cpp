
#include <raumkernel/device/deviceCreator.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/manager/settingsManager.h>

namespace Raumkernel
{
    namespace Devices
    {
        DeviceCreator::DeviceCreator() : RaumkernelBaseMgr()
        {
        }


        DeviceCreator::~DeviceCreator()
        {
        }


        void DeviceCreator::setDeviceInformationFromDeviceXML(std::shared_ptr<Device> _device, rapidxml::xml_node<> *_deviceNode)
        {
            rapidxml::xml_document<> doc;
            rapidxml::xml_node<> *deviceNode = _deviceNode, *valueNode;
            std::string	deviceType, deviceUDN, deviceFriendlyName, deviceModelDescription, deviceModelName, deviceManufacturer, deviceManufacturerUrl;
            std::string	deviceModelNumber, deviceSerialNumber;

            deviceType = deviceNode->first_node("deviceType", 0, false)->value();
            deviceUDN = deviceNode->first_node("UDN", 0, false)->value();
            deviceUDN = Raumkernel::Tools::CommonUtil::FormatUDN(deviceUDN);
            valueNode = deviceNode->first_node("friendlyName", 0, false);
            if (valueNode)
                deviceFriendlyName = valueNode->value();
            valueNode = deviceNode->first_node("modelDescription", 0, false);
            if (valueNode)
                deviceModelDescription = valueNode->value();
            valueNode = deviceNode->first_node("modelName", 0, false);
            if (valueNode)
                deviceModelName = valueNode->value();
            valueNode = deviceNode->first_node("manufacturer", 0, false);
            if (valueNode)
                deviceManufacturer = valueNode->value();
            valueNode = deviceNode->first_node("manufacturerURL", 0, false);
            if (valueNode)
                deviceManufacturerUrl = valueNode->value();
            valueNode = deviceNode->first_node("modelNumber", 0, false);
            if (valueNode)
                deviceModelNumber = valueNode->value();
            valueNode = deviceNode->first_node("serialNumber", 0, false);
            if (valueNode)
                deviceSerialNumber = valueNode->value();

    
            _device->setLogObject(getLogObject());
            _device->setUDN(deviceUDN);
            _device->setDeviceType(deviceType);
            _device->setFriendlyName(deviceFriendlyName);
            _device->setModelDescription(deviceModelDescription);
            _device->setModelName(deviceModelName);
            _device->setModelNumber(deviceModelNumber);
            _device->setSerialNumber(deviceSerialNumber);
            _device->setManufacturer(deviceManufacturer);
            _device->setManufacturerUrl(deviceManufacturerUrl);
        }


        std::shared_ptr<Devices::MediaRenderer> DeviceCreator::createMediaRendererFromDeviceXML(std::string _deviceXML)
        {
            rapidxml::xml_document<> doc;
            rapidxml::xml_node<> *deviceNode, *rootNode, *valueNode;
            std::string deviceModelDescription, deviceManufacturer;            
            std::shared_ptr<Devices::MediaRenderer> mediaRenderer;
            bool isVirtualRenderer = false, isRaumfeldRenderer = false;

            // to parse the string we have to put it ino char* (because c_str() returns const char*)
            char* cstr = new char[_deviceXML.size() + 1];
            strcpy(cstr, _deviceXML.c_str());
            doc.parse<0>(cstr);

            // find the root node which has to be the 'device' node	
            rootNode = doc.first_node("root", 0, false);
            if (!rootNode)
            {
                logError("Requested device XML from device does not contain root block!", CURRENT_POSITION);                
                return nullptr;
            }

            // find the root node which has to be the 'device' node	
            deviceNode = rootNode->first_node("device", 0, false);
            if (!deviceNode)
            {             
                logError("Requested device XML from device does not contain device information!", CURRENT_POSITION);
                return nullptr;
            }

            valueNode = deviceNode->first_node("manufacturer", 0, false);
            if (valueNode)
                deviceManufacturer = valueNode->value();
            valueNode = deviceNode->first_node("modelDescription", 0, false);
            if (valueNode)
                deviceModelDescription = valueNode->value();
                                                    
            isVirtualRenderer = deviceModelDescription.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_RAUMFELDDESCRIPTIONVIRTUALMEDIAPLAYER)) != std::string::npos;
            isRaumfeldRenderer = deviceManufacturer.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_RAUMFELDMANUFACTURER)) != std::string::npos;

            if (isRaumfeldRenderer && isVirtualRenderer)
                mediaRenderer = std::shared_ptr<MediaRenderer_RaumfeldVirtual>(new MediaRenderer_RaumfeldVirtual());
            else
                mediaRenderer = std::shared_ptr<MediaRenderer>(new MediaRenderer());           

            setDeviceInformationFromDeviceXML(mediaRenderer, deviceNode);

            // subscribe to media renderer state change! if media renderer comes to another state or data is updated, it will be called!
            // TODO Own suscrive class? 
            //mediaRenderer->SubscribeSignalMediaRendererStateChanged(typeSignalMediaRendererStateChanged::slot_type(boost::bind(&DeviceManager::OnMediaRendererStateChanged, this, _1)));

            return mediaRenderer;
        }


        std::shared_ptr<Devices::Device> DeviceCreator::createDeviceFromDeviceXML(std::string _deviceXML)
        {
            rapidxml::xml_document<> doc;
            rapidxml::xml_node<> *deviceNode, *rootNode, *valueNode;           
            std::shared_ptr<Devices::MediaRenderer> mediaRenderer = nullptr;
            std::shared_ptr<Devices::Device> createdDevice = nullptr;;
            std::string deviceType, deviceUDN;     

            logDebug("Try to create device from device XML", CURRENT_POSITION);

            // to parse the string we have to put it ino char* (because c_str() returns const char*)
            char* cstr = new char[_deviceXML.size() + 1];
            strcpy(cstr, _deviceXML.c_str());
            doc.parse<0>(cstr);

            // find the root node which has to be the 'device' node	
            rootNode = doc.first_node("root", 0, false);
            if (!rootNode)
            {
                logError("Device XML from device does not contain root block!", CURRENT_POSITION);             
                return nullptr;
            }

            // find the root node which has to be the 'device' node	
            deviceNode = rootNode->first_node("device", 0, false);
            if (!deviceNode)
            {
                logError("Device XML from device does not contain device information!", CURRENT_POSITION);                
                return nullptr;
            }

            valueNode = deviceNode->first_node("udn", 0, false);
            if (!valueNode)
            {
                logError("Device XML from device does not contain UDN information!", CURRENT_POSITION);                
                return nullptr;
            }
            deviceUDN = valueNode->value();

            valueNode = deviceNode->first_node("deviceType", 0, false);
            if (!valueNode)
            {
                logError("Device XML from device does not contain type information!", CURRENT_POSITION);                
                return nullptr;
            }
            deviceType = valueNode->value();

            if (deviceType.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_MEDIARENDERERIDENTIFICATION)) != std::string::npos)
            {
                logDebug("Createing device (" + deviceUDN  + ")", CURRENT_POSITION);                
                mediaRenderer = createMediaRendererFromDeviceXML(_deviceXML);
                if (mediaRenderer)
                {
                    createdDevice = mediaRenderer;
                    logDebug("Media Renderer device created (" + deviceUDN + ")", CURRENT_POSITION);
                }
                else
                {
                    logError("Object for device '" + deviceType + "' with UDN: '" + deviceUDN + "' could not be created", CURRENT_POSITION);                    
                }
            }
            // check if device is of type mediaServer
            // in fact there can only be one raumfeld media server we can use
            else if (deviceType.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_MEDIASERVERIDENTIFICATION)) != std::string::npos)
            {
                /*
                mediaServer = this->CreateMediaServerObjectFromDeviceXML(_deviceXML);
                if (mediaServer)
                {
                    if (mediaServer->IsRaumfeldMediaServer())
                    {
                        createdDevice = mediaServer;
                        logDebug("Media Server device created (" + deviceUDN + ")", CURRENT_POSITION);
                    }
                    else
                    {
                        // we can not do anything with a media server which is no raumfeld media server, so....
                        // maybee in future we can us it in any way... But for now....
                        delete mediaServer;
                    }

                }
                else
                {
                    this->Log(LogType::LOGERROR, "Object for device '" + deviceType + "' with UDN: '" + deviceUDN + "' can not be created", __FUNCTION__);
                }
                */
            }
            else
            {
                logDebug("No device was created for " + deviceUDN + ". Device is not usable!", CURRENT_POSITION);
            }            

            return createdDevice;
        }
    }
}