/**
 * @author Ali Mirmohammad
 * @file usbdriver.hpp
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

#ifndef __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP


// #include <system/drivers/driver.h>
#include <system/drivers/driver.hpp>
#include <system/drivers/usb/usbdevice.hpp>
#include <alinix/list.hpp>


// typedef  InterruptTransfer InterruptTransfer ;


class USBDriver {
public:
    uint8_t device;
    // Constructor
    USBDriver(class USBDevice* dev, char* driverName);
 
    // Destructor
    ~USBDriver();

    // Other member functions
    void DeInitialize();
    bool HandleInterruptPacket(struct InterruptTransfer* transfer);
    // static USBDevice* device; // Pointer to USBDevice
};





#endif /*__ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP*/