/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP
#define __ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP

#include "driver.hpp"
#include <system/drivers/usb/usbdevice.hpp>

using namespace alinix;

namespace alinix{
    namespace drivers{
        namespace usb{
        typedef struct InterruptTransfer InterruptTransfer_t;

        class USBDriver : public drivers::usb::Driver
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
}

#endif /*__ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP*/