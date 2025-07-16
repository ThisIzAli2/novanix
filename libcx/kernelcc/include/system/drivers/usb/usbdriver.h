/**
 * @author Ali Mirmohammad
 * @file usbdriver.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__USB__USBDRIVER_H
#define __Novanix__SYSTEM__DRIVERS__USB__USBDRIVER_H

#include <system/drivers/driver.h>
#include <system/usb/usbdevice.h>

namespace Novanix
{
    namespace system
    {
        typedef struct InterruptTransfer InterruptTransfer_t;

        class USBDriver : public drivers::Driver
        {
        public:
            // Which device is this driver for
            USBDevice* device;
        public:
            USBDriver(USBDevice* dev, char* driverName);
            virtual ~USBDriver();

            // De-Active this driver from the system
            // Called when device is unplugged
            virtual void DeInitialize();

            // Called from USB Controller when a interrupt packet is received
            virtual bool HandleInterruptPacket(InterruptTransfer_t* transfer);
        };
    }
}

#endif