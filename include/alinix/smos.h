/**
 * @author Ali Mirmohammad
 * @file smos.h
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
 *    - Kernel SMOS header file implementation.
*/
#ifndef __ALINIX_KERNEL_SMOS_H
#define __ALINIX_KERNEL_SMOS_H

#define CURRENT_YEAR        2024                           //! Change this each year!


#include <alinix/types.h>

VOID ReadFromCMOS (unsigned char array []);
VOID WriteTOCMOS(unsigned char array[]);

void out_byte(int port, int value);
int in_byte(int port);

enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

#endif /*__ALINIX_KERNEL_SMOS_H*/