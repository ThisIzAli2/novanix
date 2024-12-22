/**
 * @author Ali Mirmohammad
 * @file tss.h
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
 *  - Kernel TSS utility header file.
*/
#ifndef __ALINIX_KERNEL_TSS_H
#define __ALINIX_KERNEL_TSS_H

#include <alinix/memory.h>
#include <alinix/types.h>
#include <alinix/core/tss.h>

void TSS_Install(uint32_t idx, uint32_t kernelSS, uint32_t kernelESP);

void TSS_SetStack(uint32_t kernelSS, uint32_t kernelESP);

struct TSSEntry* TSS_GetCurrent();


#endif /*__ALINIX_KERNEL_TSS_H*/