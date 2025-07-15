/**
 * @author Ali Mirmohammad
 * @file usbdriver.cpp
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
#include <system/drivers/usb/usbdriver.h>
#include <system/log.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;
using namespace Novanix::system::drivers;

USBDriver::USBDriver(USBDevice* dev, char* driverName)
: Driver(driverName)
{
    this->device = dev;
}

USBDriver::~USBDriver()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}

void USBDriver::DeInitialize()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}

bool USBDriver::HandleInterruptPacket(InterruptTransfer_t* transfer)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}