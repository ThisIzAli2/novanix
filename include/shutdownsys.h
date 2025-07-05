
/**
 * @author Ali Mirmohammad
 * @file shutdownsys.h
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
*/#ifndef __NOVANIX_KERNEL_SHUT_DOWN_SYS_H
#define __NOVANIX_KERNEL_SHUT_DOWN_SYS_H

#include <common/types.h>
#include <typing.hpp>

static __always_inline VOID outw(Novanix::common::uint16_t port, Novanix::common::uint16_t value) {
    __asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

VOID __always_inline shutdown_sys_now(){
    outw(0x604, 0x2000); // Port 0x604 is common for ACPI shutdown
}

#endif