
#include <raumkernel/manager/settingsManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        SettingsManager::SettingsManager() : ManagerBase()
        {
            settingsFileName = "settings.xml";
        }


        SettingsManager::~SettingsManager()
        {
            logDebug("Destroying Settings-Manager", CURRENT_POSITION);
        }


        void SettingsManager::setFileName(const std::string &_settingsFileName)
        {
            settingsFileName = _settingsFileName;
        }


        void SettingsManager::initSettings()
        {
            logDebug("Init settings file", CURRENT_POSITION);
            initSettingsFile(settingsFileName);
        }


        std::string SettingsManager::getValue(const std::string &_xPath, const std::string &_defaultValue)
        {
            // lock the map while we do read some settings
            std::lock_guard<std::mutex> lock(mutexSettingsAccess);

            try
            {
                auto settingsXPathNode = applicationNode.select_single_node(_xPath.c_str());
                if (settingsXPathNode)
                    return  settingsXPathNode.node().child_value();
            }
            catch (...)
            {
                logError("Exception while getting value from: " + _xPath, CURRENT_FUNCTION);
            }
            return _defaultValue;
        }


        std::string SettingsManager::getAttributeValue(const std::string &_xPath, const std::string &_attributeName, const std::string &_defaultValue)
        {
            // lock the map while we do read some settings
            std::lock_guard<std::mutex> lock(mutexSettingsAccess);

            try
            {
                auto settingsXPathNode = applicationNode.select_single_node(_xPath.c_str());
                if (settingsXPathNode)
                {
                    auto attribute = settingsXPathNode.node().attribute(_attributeName.c_str());
                    if (attribute)
                        return  attribute.value();
                }
            }
            catch (...)
            {
                logError("Exception while getting value from: " + _xPath, CURRENT_FUNCTION);
            }
            return _defaultValue;
        }

        void SettingsManager::initSettingsFile(const std::string &_fileName)
        {
            logDebug("Loading settings from file '" + _fileName + "'", CURRENT_POSITION);

            // lock the map while we do update it
            std::lock_guard<std::mutex> lock(mutexSettingsAccess);

            try
            {
                // we do have to have a settings file. if no file name is given or we are not able to open the file we have to crash the kernel!
                if (_fileName.empty())
                {
                    logCritical("Not settings file specified! System will not be able to start!", CURRENT_POSITION);
                    throw std::runtime_error("Unrecoverable error! ABORT!");
                }

                std::ifstream settingsFileStream(_fileName.c_str());
                if (settingsFileStream.fail())
                {
                    logCritical("Can not open settings file '" + _fileName + "'! System will not be able to start!", CURRENT_POSITION);
                    throw std::runtime_error("Unrecoverable error! ABORT!");
                }

                pugi::xml_parse_result result = doc.load_file(_fileName.c_str());

                // find the root node which has to be the 'Application' node	
                applicationNode = doc.child("Application");
                if (!applicationNode)
                {
                    logCritical("'Application' node not found in settings file! System will not be able to start!", CURRENT_POSITION);
                    throw std::runtime_error("Unrecoverable error! ABORT!");
                }

                logDebug("Settings file initialized...", CURRENT_POSITION);
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
                throw std::runtime_error("Unknown exception! [SettingsManager::initSettingsFile]");
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