/**
 * @author Ali Mirmohammad
 * @file usbmanager.cpp
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
#include <system/usb/usbmanager.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;
using namespace Novanix::system::drivers;

extern char* USBControllerStrings[];

USBManager::USBManager()
: controllerList(), deviceList()
{
    this->initDone = false;
}

VOID USBManager::USBPoll()
{
    for(USBController* c : controllerList)
        c->ControllerChecksThread();
}

VOID USBManager::AddController(USBController* c)
{
    controllerList.push_front(c);
}
VOID USBManager::RemoveController(USBController* c)
{
    controllerList.Remove(c);
}
VOID USBManager::AddDevice(USBDevice* c)
{
    deviceList.push_back(c);

    if(this->initDone) {
        if(c->AssignDriver())
            Log(Info, "USBDevice %s driver assignment succes!", c->deviceName != 0 ? c->deviceName : "Unnamed");
        else
            Log(Warning, "USBDevice %s driver assignment failed!", c->deviceName != 0 ? c->deviceName : "Unnamed");
    }
}
VOID USBManager::RemoveDevice(USBController* controller, uint8_t port)
{
    USBDevice* dev = 0;
    for(USBDevice* c : deviceList)
        if(c->controller == controller && c->portNum == port) {
            dev = c;
            break;
        }
    
    if(dev == 0 || !initDone)
        Log(Error, "Device was removed from port but no USBDevice was found!");
    else
    {
        Log(Info, "Device %s Removed at port %d from %s controller", dev->deviceName != 0 ? dev->deviceName : "Unnamed", port, USBControllerStrings[dev->controller->type]);
        deviceList.Remove(dev);
        dev->OnUnplugged();
        delete dev;
    }
}

VOID USBManager::SetupAll()
{
    for(USBController* c : controllerList)
        c->Setup();
}

VOID USBManager::AssignAllDrivers()
{
    for(USBDevice* c : deviceList) {
        if(c->AssignDriver())
            Log(Info, "USBDevice %s driver assignment succes!", c->deviceName != 0 ? c->deviceName : "Unnamed");
        else
            Log(Warning, "USBDevice %s driver assignment failed!", c->deviceName != 0 ? c->deviceName : "Unnamed");
    }
    this->initDone = true;
}

