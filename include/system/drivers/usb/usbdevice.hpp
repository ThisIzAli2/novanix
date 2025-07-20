/**
 * @author Ali Mirmohammad
 * @file usbdevice.hpp
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

#ifndef __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP

#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif




#include <alinix/types.h>
#include <system/drivers/usb/usbdriver.hpp>
#include <system/drivers/usb/usbcontroller.hpp>

class USBDriver;

typedef struct InterruptTransfer
{
    uint8_t* bufferPointer;
    uint32_t bufferPhys;
    int bufferLen;

    USBDriver* handler;
    int queueIndex;

    uint32_t tdPhys;
    void* td;
    int numTd;

    void* qh;
    int endpoint;
} InterruptTransfer_t;

class USBController;
class USBDevice; // Forward declaration of USBDevice class


class USBDevice {
public:
    uint8_t portNum = 0;
    uint8_t devAddress = 0;
    USBController* controller = nullptr;
    char* deviceName = nullptr;
    char* device;
    uint16_t classID = 0;
    uint16_t subclassID = 0;
    uint16_t protocol = 0;
    uint16_t vendorID = 0;
    uint16_t productID = 0;
    USBController* driver = nullptr;

    struct UHCIProperties {
        bool lowSpeedDevice;
        int maxPacketSize;
    } uhciProperties;

    struct OHCIProperties {
        int desc_mps;
        bool ls_device;
    } ohciProperties;

    uint8_t* hidDescriptor = nullptr;

public:
    USBDevice();
    ~USBDevice();

    bool AssignDriver();

    void OnUnplugged();
};


#endif /*__ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP*/
