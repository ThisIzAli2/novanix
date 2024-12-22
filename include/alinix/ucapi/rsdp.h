/**
 * @file rsdp.h
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
 * @abstraction:
 *  - UACPI util.
*/


#ifndef __ALINIX_KERNEL_RSPD_ACPI_H
#define __ALINIX_KERNEL_RSPD_ACPI_H


/**
 * @ref https://wiki.osdev.org/RSDP
*/


#define ACPI_VERSION "1.0"

#include <alinix/compiler.h>
#include <alinix/types.h>

struct RSDP_t{
    char Sign[8];
    u8 check_sum;
    char QEMID[6];
    u8 revision;
    u32 RsdtAddress;
}__attribute__ ((packed));

struct XSDP_t {
 char Signature[8];
 uint8_t Checksum;
 char OEMID[6];
 uint8_t Revision;
 uint32_t RsdtAddress;      // deprecated since version 2.0
 
 uint32_t Length;
 uint64_t XsdtAddress;
 uint8_t ExtendedChecksum;
 uint8_t reserved[3];
} __attribute__ ((packed));


#endif /*__ALINIX_KERNEL_RSPD_ACPI_H*/