
#include <raumkernel/device/eventParser/deviceEventParser.h>

namespace Raumkernel
{
    namespace Devices
    {
        namespace EventParser
        {
            DeviceEventParser::DeviceEventParser() : RaumkernelBase()
            {
            }


            DeviceEventParser::~DeviceEventParser()
            {
            }


            void DeviceEventParser::setDevice(Devices::Device *_device)
            {
                device = _device;
            }


            rapidxml::xml_node<>* DeviceEventParser::getInstanceNodeFromXML(std::string _xml)
            {
                rapidxml::xml_document<> doc;
                rapidxml::xml_node<> *eventNode, *instanceNode;

                char* cstr = new char[_xml.size() + 1];
                strcpy(cstr, _xml.c_str());
                doc.parse<0>(cstr);

                eventNode = doc.first_node("Event", 0, false);
                if (!eventNode)
                {
                    logError("Subscription XML parsing error! Missing node 'Event'", CURRENT_POSITION);
                    return nullptr;
                }

                instanceNode = eventNode->first_node("InstanceId", 0, false);
                if (!instanceNode)
                {
                    logError("Subscription XML parsing error! Missing node 'InstanceId'", CURRENT_POSITION);
                    return nullptr;
                }

                return instanceNode;
            }


            std::string DeviceEventParser::getNodeVal(rapidxml::xml_node<>* _parentNode, std::string _nodeName, std::string _oldVal, bool &_valChanged, std::string _attributeName)
            {
                rapidxml::xml_node<> *valueNode;
                rapidxml::xml_attribute<> *attribute;
                std::string value;

                if (!_parentNode)
                    return _oldVal;

                valueNode = _parentNode->first_node(_nodeName.c_str(), 0, false);
                if (!valueNode)
                    return _oldVal;

                attribute = valueNode->first_attribute(_attributeName.c_str());
                if (!attribute)
                    return _oldVal;

                value = attribute->value();

                if (value != _oldVal)
                    _valChanged = true;

                return value;
            }
           
        }

    }
}