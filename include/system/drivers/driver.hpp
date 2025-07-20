/**
 * @author Ali Mirmohammad
 * @file driver.hpp
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

#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP

#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif


#include <system/drivers/usb/usbdevice.h>
#include <system/drivers/usb/usbdevice.hpp>

// typedef USBDevice USBDevice;

class Driver
    {
    private:
        char* Name;
        char* Description;
    public:
        // static USBDevice* device; // Pointer to USBDevice
        Driver(char* name = 0, char* description = 0);

        char* GetDriverName();
        char* GetDriverDescription();

        virtual bool Initialize();
    };


static char* GetDriverName();
static char* GetDriverDescription();

static bool Initialize();


#endif //__ALINIX_KERNEL_SYSTEM_DRIVERS_HPP