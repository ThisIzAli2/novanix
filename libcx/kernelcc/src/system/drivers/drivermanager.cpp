/**
 * @author Ali Mirmohammad
 * @file drivermanager.cpp
 * @credits Remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
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