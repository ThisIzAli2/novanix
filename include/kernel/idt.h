/**
 * @author Ali Mirmohammad
 * @file idt.h
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

#ifndef _HEISEN_IDT_H
#define _HEISEN_IDT_H

#include <heisen/typing.h>

extern void initIdt();
extern void SetIdtEntry(unsigned char num, size_t handler, unsigned short sel,
                        unsigned char flags);

// Marks the interrupt handler as entered. This is already called for you for
// interrupt handlers registered with InstallHardwareInterruptHandler.
extern void MarkInterruptHandlerAsEntered();

// Marks the interrupt handler as left. This is already called for you for
// interrupt handlers registered with InstallHardwareInterruptHandler.
extern void MarkInterruptHandlerAsLeft();

#endif // _HEISEN_IDT_H