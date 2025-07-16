/**
 * @author Ali Mirmohammad
 * @file usbmanager.h
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
#ifndef __Novanix__SYSTEM__USB__USBMANAGER_H
#define __Novanix__SYSTEM__USB__USBMANAGER_H

#include <system/usb/usbcontroller.h>
#include <system/usb/usbdevice.h>

namespace Novanix
{
    namespace system
    {
        class USBManager
        { 
        public:
            // The list of all usb controllers present on this pc. (the ones detected by pci)
            List<USBController*> controllerList;
            // List of all known USBDevices
            List<USBDevice*> deviceList;
            // Holds if usb devices present on boot are all initialized
            bool initDone = false;
        public:
            //Create new instance of USBManager
            USBManager();

            //Add controller to list, called by HC drivers.
            void AddController(USBController* c);
            //Remove controller from list
            void RemoveController(USBController* c);
            //Add device to list, called by HC drivers.
            void AddDevice(USBDevice* c);
            //Remove device, called after device unplug
            void RemoveDevice(USBController* controller, uint8_t port);
            //Send the setup command to all the controllers
            void SetupAll();
            //Make all usb devices detect their properties and automaticly select a driver
            void AssignAllDrivers();
            //Check for changes in usb status
            void USBPoll();
        };
    }
}

#endif