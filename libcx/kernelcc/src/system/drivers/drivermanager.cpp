#include <system/drivers/drivermanager.h>
#include <system/log.h>

using namespace Novanix;
using namespace Novanix::system;
using namespace Novanix::system::drivers;

DriverManager::DriverManager()
{
    this->driverList.Clear();
}

void DriverManager::AddDriver(Driver* drv)
{
    this->driverList.push_back(drv);
}

void DriverManager::ActivateAll()
{
    for(int i = 0; i < driverList.size(); i++)
    {
        Log(Info, "Activating driver %s", driverList[i]->GetDriverName());
        
        if(driverList[i]->Initialize() == false)
            Log(Error, "driver initialize failed for driver -> %s ", driverList[i]->GetDriverName());
    }
}