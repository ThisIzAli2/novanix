/**
 * @file lockdown.h
 * @author Ali Mirmohammad
 * 
 ** This file is part of Novanix.

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
#ifndef __NOVANIX_KERNEL_LOCKDOWN_H
#define __NOVANIX_KERNEL_LOCKDOWN_H


#include <common/init.hpp>

#define HALT_COMMAND asm volatile ("hlt")

enum LOCKDOWN_REASON{
    UNDECLARED = 0,
    ROOT_ACCESS_FAILED =1,
};

static enum LOCKDOWN_REASON lockdown_reason;

VOID put_system_lockdown(enum LOCKDOWN_REASON reason);



#endif /*__NOVANIX_KERNEL_LOCKDOWN_H*/