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
#ifndef __ALINIX_KERNEL_DRIVERS_USB_USB_CONTROLLER_HPP
#define __ALINIX_KERNEL_DRIVERS_USB_USB_CONTROLLER_HPP

#include <alinix/types.h>
#include <alinix/list.hpp>

namespace alinix{
    namespace drivers{
        namespace usb{
                    enum USBControllerType
        {
            UHCI,
            OHCI,
            EHCI,
            xHCI
        };

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

        class USBDevice;
        class USBController
        {
        protected:
            List<InterruptTransfer_t*> interrupTransfers;            
        public:
            // What type of controller is this
            USBControllerType type;
            // Create new instance of USBController class
            USBController(USBControllerType usbType);

            // Setup this controller into the active state
            virtual void Setup();

            // Function that will get called on a periodic interval in which the controller can perform specific kinds of things.
            // One of these things is port connection change checking and updating devices if necessary.
            virtual void ControllerChecksThread();

            /////
            // USB Common functions per controller
            /////

            // Perform a bulk in operation
            virtual bool BulkIn(USBDevice* device, void* retBuffer, int len, int endP);
            // Perform a bulk out operation
            virtual bool BulkOut(USBDevice* device, void* sendBuffer, int len, int endP);

            // Perform a control in operation
            virtual bool ControlIn(USBDevice* device, void* target = 0, const int len = 0, const uint8_t requestType = 0, const uint8_t request = 0, const uint16_t valueHigh = 0, const uint16_t valueLow = 0, const uint16_t index = 0);
            // Perform a control out operation
            virtual bool ControlOut(USBDevice* device, const int len = 0, const uint8_t requestType = 0, const uint8_t request = 0, const uint16_t valueHigh = 0, const uint16_t valueLow = 0, const uint16_t index = 0);
            
            // Place a interrupt in transfer in the dedicated queue, handler will get called on completion
            virtual void InterruptIn(USBDevice* device, int len, int endP);

            /////
            // Functions that use controler specific implementations
            /////

            // Get Device descriptor of specific device
            bool GetDeviceDescriptor(struct DEVICE_DESC* dev_desc, USBDevice* device);

            // Get String descriptor of specific device
            bool GetStringDescriptor(struct STRING_DESC* stringDesc, USBDevice* device, uint16_t index, uint16_t lang = 0);
            
            // Get String descriptor of specific device
            // Returns buffer with Configuration header and additional data            
            uint8_t* GetConfigDescriptor(USBDevice* device);
            
            // Set configuration for device
            bool SetConfiguration(USBDevice* device, uint8_t config);

            // Receive devices current configuration
            int GetConfiguration(USBDevice* device);
            
            // Get maximum of Logical unit numbers, Only for Mass Storage Devices!
            int GetMaxLuns(USBDevice* device);
        };
        }
    }
}

#endif /*__ALINIX_KERNEL_DRIVERS_USB_USB_CONTROLLER_HPP*/