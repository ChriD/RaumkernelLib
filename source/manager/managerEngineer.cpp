
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Manager
    {
        ManagerEngineer::ManagerEngineer() : RaumkernelBase()
        {
            settingsManager = nullptr;
        }


        ManagerEngineer::~ManagerEngineer()
        {
        }


        void ManagerEngineer::createManagers()
        {
            // create the settings manager wich will hold all of the settings for the kernel and the corresponding app
            settingsManager = std::shared_ptr<Manager::SettingsManager>(new Manager::SettingsManager());
            settingsManager->setLogObject(getLogObject());
        }


        std::shared_ptr<SettingsManager> ManagerEngineer::getSettingsManager()
        {
            return settingsManager;
        }

    }
}