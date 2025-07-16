/**
 * @author Ali Mirmohammad
 * @file usbmouse.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__USB__MOUSE_H
#define __Novanix__SYSTEM__DRIVERS__USB__MOUSE_H

#include <system/drivers/usb/usbdriver.h>
#include <system/usb/hidparser.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            class USBMouse : public USBDriver
            {
            private:
                HIDParser hidParser;
                bool GetHIDProperty(struct HID_DATA* target, uint8_t* buffer, int bufLen, HID_USAGE item);

                bool useCustomReport = false;
                struct HID_DATA hidX;
                struct HID_DATA hidY;
                struct HID_DATA hidZ;

                int InInterruptEndpoint = -1;
            public:
                // Instance initializer
                USBMouse(USBDevice* dev);
                
                // Called when device is plugged into system
                bool Initialize() override;

                // Called when device is unplugged from system
                void DeInitialize() override;

                // Called by USB driver when we receive a interrupt packet
                bool HandleInterruptPacket(InterruptTransfer_t* transfer) override;
            };
        }
    }
}

#endif