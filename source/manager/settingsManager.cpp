
#include <raumkernel/manager/settingsManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        SettingsManager::SettingsManager() : ManagerBase()
        {
            settingsFileName = "raumkernel.xml";
        }


        SettingsManager::~SettingsManager()
        {
        }


        void SettingsManager::setFileName(std::string _settingsFileName)
        {
            settingsFileName = _settingsFileName;
        }


        void SettingsManager::loadSettings()
        {
            logDebug("Load settings", CURRENT_POSITION);
            loadSettingsFromFile(settingsFileName);
            validateSettings();
        }


        std::string SettingsManager::getValue(std::string _settingsPath, std::uint16_t _index)
        {
            // lock the map while we do read some settings
            std::lock_guard<std::mutex> lock(mutexSettingsMapAccess);

            if (settingsMap.find(_settingsPath) != settingsMap.end())
                return settingsMap.at(_settingsPath);
            return "";
        }

       
        void SettingsManager::walkNode(const rapidxml::xml_node<>* _node, std::string _path, int _indent)
        {
            const auto ind = std::string(_indent * 4, ' ');       
            const rapidxml::node_type nodeType = _node->type();
            std::string path = "";

            // we do not want to have the "Application" node be stored in the path!
            if (_indent > 1)         
                path = _path;

            switch (nodeType) 
            {
                case rapidxml::node_element:            
                                                          
                    for (const rapidxml::xml_attribute<>* a = _node->first_attribute(); a; a = a->next_attribute()) 
                    {
                        // INFO: we may enter here to store attribute values to nodes/paths
                        // e.g a map with the path as key and a sunmap of attribute keys + values
                    }            
                    for (const rapidxml::xml_node<>* n = _node->first_node(); n; n = n->next_sibling())
                    {                            
                        walkNode(n, path + "/" + _node->name(), _indent + 1);
                    }                                                     
                    break;

                case rapidxml::node_data:         
                    // we got a node data where there might be a value, so we store the value in the map with the path given in the recursive method
                    logDebug("Found setting: " + path + " = " + std::string(_node->value()), CURRENT_POSITION);
                    settingsMap.insert(std::make_pair(path, _node->value()));
                    break;

                default:                 
                    break;
            }
        }


        void SettingsManager::loadSettingsFromFile(std::string _fileName)
        {
            logDebug("Loading settings from file '" + _fileName + "'", CURRENT_POSITION);

            // lock the map while we do update it
            std::lock_guard<std::mutex> lock(mutexSettingsMapAccess);

            // start with a nice clean map.
            settingsMap.clear();

            try
            {
                rapidxml::xml_document<> doc;
                rapidxml::xml_node<> *applicationNode;

                // we do have to have a settings file. if no file name is given or we are not able to open the file we have to crash the kernel!
                if (_fileName.empty())
                {
                    logCritical("Not settings file specified! System will not be able to start!", CURRENT_POSITION);
                    throw Raumkernel::Exception::RaumkernelException(Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH, CURRENT_POSITION, "Unrecoverable error! ABORT!", 100);
                }

                std::ifstream settingsFileStream(_fileName.c_str());
                if (settingsFileStream.fail())
                {
                    logCritical("Can not open settings file '" + _fileName + "'! System will not be able to start!", CURRENT_POSITION);
                    throw Raumkernel::Exception::RaumkernelException(Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH, CURRENT_POSITION, "Unrecoverable error! ABORT!", 101);
                }

                std::vector<char> buffer((std::istreambuf_iterator<char>(settingsFileStream)), std::istreambuf_iterator<char>());
                buffer.push_back('\0');          
                doc.parse<0>(&buffer[0]);

                // find the root node which has to be the 'Application' node	
                applicationNode = doc.first_node("Application", 0, false);
                if (!applicationNode)
                {
                    logCritical("'Application' node not found in settings file! System will not be able to start!", CURRENT_POSITION);
                    throw Raumkernel::Exception::RaumkernelException(Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH, CURRENT_POSITION, "Unrecoverable error! ABORT!", 102);
                }
                                              
                logDebug("Parsing settings file...", CURRENT_POSITION);

                // go through all nodes and load those values and path into the settings map
                walkNode(applicationNode);

                logDebug("Parsing settings file is done!", CURRENT_POSITION);             
                logDebug("Settings loaded!", CURRENT_POSITION);

            }
            catch (Raumkernel::Exception::RaumkernelException &e)
            {
                if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                    throw e;                
            }
            catch (std::exception &e)
            {
                throw e;
            }
            catch (std::string &e)
            {
                throw e;
            }
            catch (...)
            {
                throw std::runtime_error("Unknown exception! [SettingsManager::loadSettingsFromFile]");
            }

        }


        void SettingsManager::validateSetting(std::string _settingPath)
        {
            std::string settingsValue = getValue(_settingPath);            
            if (settingsValue.empty())
            {
                logCritical(_settingPath + " is not set!", CURRENT_POSITION);
                throw Raumkernel::Exception::RaumkernelException(Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH, CURRENT_POSITION, "Unrecoverable error! ABORT!", 110);
            }           
        }



        void SettingsManager::validateSettings()
        {
            std::string settingsValue;

            logDebug("Validate settings...", CURRENT_POSITION);        
            
            // check if all mandatory settings we need are there!
            validateSetting(SETTINGS_RAUMKERNEL_HOSTCONFIGDEVICENAME);           
            validateSetting(SETTINGS_RAUMKERNEL_MEDIASERVERNAME);
            validateSetting(SETTINGS_RAUMKERNEL_HOSTREQUESTPORT);
            validateSetting(SETTINGS_RAUMKERNEL_MEDIARENDERERIDENTIFICATION);
            validateSetting(SETTINGS_RAUMKERNEL_MEDIASERVERIDENTIFICATION);
            validateSetting(SETTINGS_RAUMKERNEL_RAUMFELDDESCRIPTIONVIRTUALMEDIAPLAYER);
            validateSetting(SETTINGS_RAUMKERNEL_RAUMFELDMANUFACTURER);

            logDebug("Settings validated!...", CURRENT_POSITION);
        }

    }
}