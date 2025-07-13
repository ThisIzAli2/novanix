/**
 * @author Ali Mirmohammad
 * @file conf.h
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
#ifndef __NOVANIX_KERNEL_CONF_H
#define __NOVANIX_KERNEL_CONF_H

#include <common/init.hpp>

// === VGA Printing for Kernel ===
#ifndef kprint
#define kprint Novanix::system::printk
#endif

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC



// I/O functions (inline assembly)

// Read from PCI configuration space
// TODO: Change the inline function later, ouaghta be removed
uint32_t  inline pci_config_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (1U << 31) | ((uint32_t)bus << 16) | ((uint32_t)slot << 11) |
                       ((uint32_t)func << 8) | (offset & 0xFC);
    outl(PCI_CONFIG_ADDRESS, address);
    return inl(PCI_CONFIG_DATA);
}

// Print hex number (simple version)
void inline print_hex(uint32_t val) {
    char hex[] = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        char c = hex[(val >> i) & 0xF];
        char str[2] = {c, 0};
        kprint(VGA_COLOR_WHITE, str, 0);
    }
}

// Main PCI scan function
inline void scan_pci_devices() {
    kprint(VGA_COLOR_WHITE, "Scanning PCI devices...\n", 1);

    for (uint8_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            uint32_t id = pci_config_read(bus, slot, 0, 0x00);
            uint16_t vendor = id & 0xFFFF;
            uint16_t device = (id >> 16) & 0xFFFF;

            if (vendor != 0xFFFF) {
                kprint(VGA_COLOR_WHITE, "PCI Device found: Vendor=0x", 0);
                print_hex(vendor);
                kprint(VGA_COLOR_WHITE, " Device=0x", 0);
                print_hex(device);
                kprint(VGA_COLOR_WHITE, "\n", 1);
            }
        }
            break;
    }
    
}


#endif /*__NOVANIX_KERNEL_CONF_H*/