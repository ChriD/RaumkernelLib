
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
            logDebug("Destroying Settings-Manager", CURRENT_POSITION);
        }


        void SettingsManager::setFileName(const std::string &_settingsFileName)
        {
            settingsFileName = _settingsFileName;
        }


        void SettingsManager::loadSettings()
        {
            logDebug("Load settings", CURRENT_POSITION);
            loadSettingsFromFile(settingsFileName);
            validateSettings();
        }


        std::string SettingsManager::getValue(const std::string &_settingsPath, const std::string &_defaultValue, const std::uint16_t &_index)
        {
            // lock the map while we do read some settings
            std::lock_guard<std::mutex> lock(mutexSettingsMapAccess);

            if (settingsMap.find(_settingsPath) != settingsMap.end())
                return settingsMap.at(_settingsPath);
            return _defaultValue;
        }

       
        void SettingsManager::walkNode(pugi::xml_node _node, const std::string &_path, const int &_indent)
        {
            const auto ind = std::string(_indent * 4, ' ');                   
            std::string path = "";

            // we do not want to have the "Application" node be stored in the path!
            if (_indent >= 1)         
                path = _path;

            for (auto childNode : _node.children())
            {
                if (childNode.value() && !std::string(childNode.value()).empty())
                {
                    logDebug("Found setting: " + path + " = " + std::string(childNode.value()), CURRENT_POSITION);
                    settingsMap.insert(std::make_pair(path, childNode.value()));
                }
                walkNode(childNode, path + "/" + childNode.name(), _indent + 1);
            }                   
        }


        void SettingsManager::loadSettingsFromFile(const std::string &_fileName)
        {
            logDebug("Loading settings from file '" + _fileName + "'", CURRENT_POSITION);

            // lock the map while we do update it
            std::lock_guard<std::mutex> lock(mutexSettingsMapAccess);

            // start with a nice clean map.
            settingsMap.clear();

            try
            {
                pugi::xml_document doc;       
                pugi::xml_node applicationNode;                

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

                pugi::xml_parse_result result = doc.load_file(_fileName.c_str());

                // find the root node which has to be the 'Application' node	
                applicationNode = doc.child("Application");
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


        void SettingsManager::validateSetting(const std::string &_settingPath)
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