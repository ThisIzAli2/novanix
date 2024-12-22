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
 * @file libgcc.h
 * @abstract:
 * 	- Kernel LIBGCC for the compiler implemented.
*/
#ifndef __ALINIX_KERNEL_LIB_GCC_H
#define __ALINIX_KERNEL_LIB_GCC_H

struct DWstruct {
	int high, low;
};

typedef union {
	struct DWstruct s;
	long long ll;
} DWunion;

#endif /*__ALINIX_KERNEL_LIB_GCC_H*/