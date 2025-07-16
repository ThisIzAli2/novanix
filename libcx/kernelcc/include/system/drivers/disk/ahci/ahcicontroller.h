/**
 * @author Ali Mirmohammad
 * @file ahcicontroller.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__DISK_CONTROLLERS__AHCI_H
#define __Novanix__SYSTEM__DRIVERS__DISK_CONTROLLERS__AHCI_H

#include <system/drivers/driver.h>
#include <system/components/pci.h>
#include <system/interruptmanager.h>
#include <system/drivers/disk/ahci/ahciport.h>

#include <system/disks/diskcontroller.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            class AHCIController : public Driver, public InterruptHandler, public DiskController
            {
            private:
                // Array of ports that are present on this controller
                AHCIPort* ports[32];

                PCIDevice* pciDevice = 0;

                uint32_t regBase = 0;
                int32_t  portCount = 0;

                // Read AHCI Register from memory location
                inline uint32_t readRegister(uint32_t offset);

                // Write a value to an AHCI Register
                inline void writeRegister(uint32_t offset, uint32_t value);
            
                // Wait for a specific bit to be clear in a register
                inline bool waitForClear(uint32_t reg, uint32_t bits, uint32_t timeout);

                // Wait for a specific bit to be set in a register
                inline bool waitForSet(uint32_t reg, uint32_t bits, uint32_t timeout);
            public:
                AHCIController(PCIDevice* device);

                bool Initialize() override;
                bool Reset();

                common::uint32_t HandleInterrupt(common::uint32_t esp) override;

                // DiskController Functions
                char ReadSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf) override;
                char WriteSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf) override;
                bool EjectDrive(common::uint8_t drive) override;
            };
        }
    }
}

#endif