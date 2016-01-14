
#include <raumkernel/manager/upnpManager.h>
#include <raumkernel/manager/subscriptionReceiverManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        SubscriptionReceiverManager::SubscriptionReceiverManager() : ManagerBase()
        {           
        }


        SubscriptionReceiverManager::~SubscriptionReceiverManager()
        {            
        }     


        void SubscriptionReceiverManager::propertyChangedAvTransportProxy(std::string _deviceUDN, std::string _xml)
        {
            logDebug("A property on AvTransport proxy has changed (Device: " + _deviceUDN + ")", CURRENT_POSITION);
            // TODO::
            // * lock this method
            // * create the information objects from the xml
            // * lock the device lists from the device manager
            // * update the information objects on the devivce itself
            // * unlock the device lists from the device manager
            // * unlock this methos
        }

        void SubscriptionReceiverManager::propertyChangedRenderingControlProxy(std::string _deviceUDN, std::string _xml)
        {
            logDebug("A property on RenderingControl proxy has changed (Device: " + _deviceUDN + ")", CURRENT_POSITION);
            // TODO::
            // * lock this method
            // * create the information objects from the xml
            // * lock the device lists from the device manager
            // * update the information objects on the devivce itself
            // * unlock the device lists from the device manager
            // * unlock this methos
        }

    }
}