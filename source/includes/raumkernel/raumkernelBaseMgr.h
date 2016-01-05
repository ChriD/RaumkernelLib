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
#ifndef RAUMKERNEL_RAUMKERNELBASEMGR_H
#define RAUMKERNEL_RAUMKERNELBASEMGR_H

#include <raumkernel/raumkernelBase.h>
//#include <raumkernel/manager/managerEngineer.h>


namespace Raumkernel
{

    // we cannot include 'managerEngineer.h' file because this would lead to an recursive problem due the manager engineer incudes all
    // managers and those include the 'raumkernelBaseMgr.h' file, so we create a dummy ManagerEngineer class for the compiler
    namespace Manager
    {
        class ManagerEngineer;
    }


    class RaumkernelBaseMgr : public RaumkernelBase
    {
        public:
            RaumkernelBaseMgr();
            virtual ~RaumkernelBaseMgr();
            void setManagerEngineer(std::shared_ptr<Manager::ManagerEngineer> _managerEngineer);
            EXPORT std::shared_ptr<Manager::ManagerEngineer> getManagerEngineer();

        protected:
            std::shared_ptr<Manager::ManagerEngineer> managerEngineer;
    };
}


#endif 