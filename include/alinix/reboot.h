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
 * @file reboot.h
 * @abstraction:
 *  - Kernel reboot header file implemented, for reboot operations.
*/
#ifndef __ALINIX_KERNEL_REBOOT_H
#define	__ALINIX_KERNEL_REBOOT_H

#include <alinix/types.h>
#include <alinix/syscall.h>


#define REBOOT_PORT 0x64
#define REBOOT_COMMAND 0xFE

// Define the system call numbers
#define __NR_reboot 169

// Define the reboot command constants
#define LINUX_REBOOT_MAGIC1 0xfee1dead
#define LINUX_REBOOT_MAGIC2 672274793
#define LINUX_REBOOT_CMD_POWER_OFF 0x4321fedc

void reboot_x86_sys_call();

/**
 * @brief reboot table data structure.
*/
struct rebootTable{
    int reset_register;
    char *reset_command;
    uint8_t rebootPort;
};

typedef struct rebootTable reboot_t;
// Forward declartion of reboot function 
VOID reboot();

#endif /*__ALINIX_KERNEL_REBOOT_H*/