
#include <raumkernel/device/eventParser/deviceEventParser.h>

namespace Raumkernel
{
    namespace Devices
    {
        namespace EventParser
        {
            DeviceEventParser::DeviceEventParser() : RaumkernelBaseMgr()
            {
            }


            DeviceEventParser::~DeviceEventParser()
            {
            }


            void DeviceEventParser::setDevice(Devices::Device *_device)
            {
                device = _device;
            }


            std::string DeviceEventParser::getNodeVal(pugi::xml_node _parentNode, std::string _nodeName, std::string _oldVal, bool &_valChanged, std::string _attributeName)
            {
                pugi::xml_node valueNode;
                pugi::xml_attribute attribute;                
                std::string value;

                if (!_parentNode)
                    return _oldVal;
                
                valueNode = _parentNode.child(_nodeName.c_str());
                if (!valueNode)
                    return _oldVal;

                attribute = valueNode.attribute(_attributeName.c_str());
                if (!attribute)
                    return _oldVal;

                value = attribute.value();

                if (value != _oldVal)
                    _valChanged = true;

                return value;
            }
           
        }

    }
}