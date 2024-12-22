/**
 * @author Ali Mirmohammad
 * @file interruptmanager.h
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
 *  - Defines managing the interrupts and IRQ.
*/

#ifndef ALINIX_INTERRUPTMANAGER_H
#define ALINIX_INTERRUPTMANAGER_H

#include <alinix/types.h>


void InterruptHandler(uint8_t interruptNumber);

// uint32_t HandleInterrupt(uint8_t interrupt, uint32_t esp);

// uint32_t HandleInterrupt(uint32_t esp);
#include <alinix/idt.h>

#endif // ALINIX_INTERRUPTMANAGER_H