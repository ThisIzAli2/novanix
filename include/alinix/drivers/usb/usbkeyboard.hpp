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
#ifndef __ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H
#define __ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H

#include <alinix/types.h>
#include "usbdevice.hpp"
#include "usbdriver.hpp"
#include "keyboard.hpp"


namespace alinix{
    namespace drivers{
        namespace usb{
        class USBKeyboard : public USBDriver, public Keyboard
            {
            private:
                int InInterruptEndpoint = -1;

                uint8_t prevPacket[8];
            public:
                // Instance initializer
                USBKeyboard(USBDevice* dev);
                
                // Called when mass storage device is plugged into system
                bool Initialize() override;

                // Called when mass storage device is unplugged from system
                void DeInitialize() override;

                // Called by USB driver when we receive a interrupt packet
                bool HandleInterruptPacket(InterruptTransfer_t* transfer) override;

                // Update LED's on a keyboard device
                void UpdateLEDS() override;
            };
        }
    }
}

#endif /*__ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H*/