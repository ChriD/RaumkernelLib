//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_SUBSCRIPTIONRECEIVERMANAGER_H
#define RAUMKERNEL_SUBSCRIPTIONRECEIVERMANAGER_H

#include <raumkernel/manager/managerBase.h>
#include <raumkernel/xml/rapidxml.hpp>
#include <raumkernel/tools/numUtil.h>


namespace Raumkernel
{
    namespace Manager
    {
        /**
        * The SubscriptionReceiver-Manager
        *
        * This class handles all the subscriptions returns which we will get from the UPNP-Devices
        */
        class SubscriptionReceiverManager : public ManagerBase
        {
            public:
                SubscriptionReceiverManager();
                virtual ~SubscriptionReceiverManager(); 

                virtual void propertyChangedAvTransportProxy(std::string _deviceUDN, std::string _xml);                
                virtual void propertyChangedRenderingControlProxy(std::string _deviceUDN, std::string _xml);

            protected:
                rapidxml::xml_node<>* getInstanceNodeFromXML(std::string _xml);
                std::string getNodeVal(rapidxml::xml_node<>* _parentNode, std::string _nodeName, std::string _oldVal, bool &_valChanged, std::string _attributeName = "val");                
            /**
            * A mutex for locking renderer property changes
            */
            std::mutex mutexRendererPropertyChange;
        };
    }
}


#endif