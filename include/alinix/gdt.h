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
 * @file gdt.h
 * Purpose:
 *      - GDT definitions and utils
*/
#ifndef __ALINIX_KERNEL_GDT_H
#define __ALINIX_KERNEL_GDT_H

#include <alinix/types.h>

/**
 * @brief Global descriptor table structure implementation.
*/
struct GDTEntry
{
    uint16_t limit_low;           // The lower 16 bits of the limit.
    uint16_t base_low;            // The lower 16 bits of the base.
    uint8_t  base_middle;         // The next 8 bits of the base.
    uint8_t  access;              // Access flags, determine what ring this segment can be used in.
    uint8_t  granularity;
    uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));


/**
 * @brief GDT pointer structure.
*/
struct GDTPointer
{
    uint16_t limit;               // The upper 16 bits of all selector limits.
    uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

void GdtSetDescriptor(int number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
struct GDTEntry* GetDescriptor(int number);
void GdtInit();


#endif /*__ALINIX_KERNEL_GDT_H*/