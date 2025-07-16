/**
 * @author Ali Mirmohammad
 * @file pcidrivers.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__PCIDRIVERS_H
#define __Novanix__SYSTEM__DRIVERS__PCIDRIVERS_H

#include <system/components/pci.h>
#include <system/drivers/drivermanager.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            struct PCIAttachedDriverEntry
            {
                common::uint16_t vendorID;
                common::uint16_t deviceID;
                char* driverString;
            } __attribute__((packed));

            class PCIDrivers
            {
            public:
                static void AssignDriversFromPCI(PCIController* pci, DriverManager* driverManager);
            };
        }
    }
}


#endif