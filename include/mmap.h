/**
 * @author Ali Mirmohammad
 * @file mmap.h
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

#ifndef NOVANIX_KERNEL_MEMORY_MAP_H
#define NOVANIX_KERNEL_MEMORY_MAP_H

#include <common/init.hpp>

typedef struct{
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
}memmap_entry_t;

static memmap_entry_t memmap[] = {
    {0x00000000, 0x0009FC00, 1},   // Usable RAM under 1MB
    {0x00100000, 0x3FF00000, 1},   // Usable RAM from 1MB to 1GB
    {0x40000000, 0x40000000, 2}    // Reserved
};

#define MEMMAP_ENTRIES sizeof(sizeof(memmap) / sizeof(memmap[0]))

VOID print_rem_ram();

#endif /*NOVANIX_KERNEL_MEMORY_MAP_H*/