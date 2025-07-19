/**
 * @author Ali Mirmohammad
 * @file scan.cpp
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
#include <network/wifi/scan.h>
#include <common/init.hpp>
#include <network/wifi/conf.h>


unsigned int pci_read_config_dword(unsigned char bus, unsigned char device,
                                   unsigned char function, unsigned char offset) {
    unsigned int address = (1 << 31)              |
                           ((bus & 0xFF) << 16)    |
                           ((device & 0x1F) << 11) |
                           ((function & 0x07) << 8)|
                           (offset & 0xFC);

    outl(PCI_CONFIG_ADDRESS, address);
    return inl(PCI_CONFIG_DATA);
}