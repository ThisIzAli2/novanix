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
 * @file fadt.h
 * @abstract:
 *  - RSDT for kernel driver.
*/
#ifndef __ALINIX_KERNEL_FADT_H
#define __ALINIX_KERNEL_FADT_H


/**
 * @ref https://wiki.osdev.org/RSDT
*/

#include <alinix/types.h>
/**
 * @brief FADT header structure util.
*/

struct ACPISDTHeader {
  char Signature[4];
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
};

/**
 * @brief FADT header structure util.
*/
struct RSDT {
  struct ACPISDTHeader h;
  uint32_t PointerToOtherSDT[];  // Flexible array member
};

/**
 * @brief FADT header structure util.
*/

struct XSDT {
  struct ACPISDTHeader h;
  uint64_t PointerToOtherSDT[];  // Flexible array member
};

bool fadtChecksum(struct ACPISDTHeader *tableHeader);
void *findFACP(void *RootSDT);

#endif /*__ALINIX_KERNEL_FADT_H*/
