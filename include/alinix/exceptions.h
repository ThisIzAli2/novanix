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
 * @file exceptions.h
 * @abstraction:
 *  - Kernel Exceptions header file implemented.
*/

#ifndef __ALINIX_KERNEL_EXCEPTIONS_H
#define __ALINIX_KERNEL_EXCEPTIONS_H

#include <alinix/types.h>

uint32_t DivideByZero(uint32_t esp);
uint32_t GeneralProtectionFault(uint32_t esp);
uint32_t PageFault(uint32_t esp);
uint32_t TrapException(uint32_t esp);
uint32_t FloatingPointException(uint32_t esp);
uint32_t StackSegmentFault(uint32_t esp);
uint32_t HandleException(uint32_t number, uint32_t esp);
void EnablePagefaultAutoFix();
void DisablePagefaultAutoFix();
void ShowStacktrace(uint32_t esp);


#endif /*__ALINIX_KERNEL_EXCEPTIONS_H*/