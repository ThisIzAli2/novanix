/**
 * @author Ali Mirmohammad
 * @file random.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Kernel random module implementation header file.
*/

#ifndef __ALINIX_KERNEL_RANDOM_HEADER_H
#define __ALINIX_KERNEL_RANDOM_HEADER_H

#include <alinix/types.h>

static uint32_t next;

static int Next(uint32_t max );
static int Next(uint32_t min, uint32_t max);             
static void SetSeed(uint32_t seed);

#endif /*__ALINIX_KERNEL_RANDOM_HEADER_H*/