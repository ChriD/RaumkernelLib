
#include <raumkernel/manager/stateManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        StateManager::StateManager() : ManagerBase()
        {            
        }


        StateManager::~StateManager()
        {
            logDebug("Destroying State-Manager", CURRENT_POSITION);
        }


        void StateManager::saveState(std::string _stateId = "", std::string _roomId = "")
        {
            // TODO: @@@
            // lock the device and zone map to be sure nothing goes out of scope while saving the data
            // lock the state file
        }


        void StateManager::restoreState(std::string _stateId = "", std::string _roomId = "")
        {
            // TODO: @@@
            // lock the state file
            
            // restore the zone configuration if necessary

            // restore the volume

            // restore the content (container / url)

            // restore the playlist position

            // restore the stream/track position

            // restore the state (play/pause/stop)
            
        }
    }
}