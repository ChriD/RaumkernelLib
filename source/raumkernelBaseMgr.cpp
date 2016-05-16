
#include <raumkernel/raumkernelBaseMgr.h>

namespace Raumkernel
{
    RaumkernelBaseMgr::RaumkernelBaseMgr() : RaumkernelBase()
    {
        managerEngineer = nullptr;
    }


    RaumkernelBaseMgr::~RaumkernelBaseMgr()
    {
    }


    void RaumkernelBaseMgr::setManagerEngineer(std::shared_ptr<Manager::ManagerEngineer> _managerEngineer)
    {
        managerEngineer = _managerEngineer;
    }
  

    std::shared_ptr<Manager::ManagerEngineer> RaumkernelBaseMgr::getManagerEngineer()
    {
        if (!managerEngineer)
            logError("Calling ManagerEngineer without existance!", CURRENT_POSITION);
        return managerEngineer;
    }
}