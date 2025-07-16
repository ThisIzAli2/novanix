/**
 * @author Ali Mirmohammad
 * @file ahciport.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__DISK_CONTROLLERS__AHCIPORT_H
#define __Novanix__SYSTEM__DRIVERS__DISK_CONTROLLERS__AHCIPORT_H

#include <system/drivers/driver.h>
#include <system/components/pci.h>
#include <system/interruptmanager.h>
#include <system/drivers/disk/ahci/ahcicontroller.h>
#include <system/drivers/disk/ahci/ahcidefs.h>

#include <system/disks/diskcontroller.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            class AHCIController;
            class AHCIPort
            {
            private:
                // Memory base of this specific port
                uint32_t portBase = 0;

                // Controller to which the port belongs
                AHCIController* parent = 0;

                a_commandHeader_t* commandList = 0;
                uint32_t commandListPhys = 0;

                a_fis_t* fis = 0;
                uint32_t fisPhys = 0;

                int index = -1;
                bool isATATPI = false;
                bool useLBA48 = false;
            private:
                // Read Port Register from memory location
                inline uint32_t readRegister(uint32_t offset);

                // Write a value to an Port Register
                inline void writeRegister(uint32_t offset, uint32_t value);

                // Wait for a specific bit to be clear in a register
                inline bool waitForClear(uint32_t reg, uint32_t bits, uint32_t timeout);

                // Wait for a specific bit to be set in a register
                inline bool waitForSet(uint32_t reg, uint32_t bits, uint32_t timeout);

                // Find a CMD slot which is ready for commands
                int FindFreeCMDSlot();
            public:
                AHCIPort(AHCIController* parent, uint32_t regBase, int index);
                ~AHCIPort();

                // Prepare port to be enabled
                bool PreparePort();

                // Enable Port for the first time
                bool StartupPort();

                // Get the type of device attached to this port
                uint32_t GetType();

                // Enable port
                bool Enable();
                
                // Disable port
                bool Disable();

                // Handle a interrupt event received from controller
                void HandleExternalInterrupt();

                // Send Identify command to port
                bool Identify(uint8_t* buffer);

                // Read or write sectors to device
                bool TransferData(bool dirIn, uint32_t lba, uint8_t* buffer, uint32_t count = 1);

                // Eject drive if it is a ATAPI device
                bool Eject();
            };
        }
    }
}

#endif