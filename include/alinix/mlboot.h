/**
 * @author Ali Mirmohammad
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

/**
 * @file mlboot.h
 * @abstraction:
 *  - Multiboot implementation.
*/
#ifndef __ALINIX_KERNEL_ML_BOOT_H
#define __ALINIX_KERNEL_ML_BOOT_H


#include <alinix/types.h>

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER MAGIC 0x2BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003





typedef struct multiboot_info_header{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
}__attribute__((__packed__)) multiboot_header_t;





#include <alinix/physicalmemory.h> // This should be for Memory management.


#endif /*__ALINIX_KERNEL_ML_BOOT_H*/