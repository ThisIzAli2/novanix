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


/**
 * Main Lockdown reasons.
 * Undeclared: We don't know.
 */
enum LOCKDOWN_REASON{
    UNDECLARED = 0,
    ROOT_ACCESS_FAILED =1,
    ROOTKIT_DETECTED,
    IO_PORT_ACCESS_VIOLATION,
    KERNEL_IMAGE_TAMPERED,
    UNSIGNED_MODULE_LOADED,
    DEBUGGER_ATTACHED,
    UNAUTHORIZED_SYSCALL,
    STACK_OVERFLOW_DETECTED,
    INVALID_USER_PRIVILEGE,
    DMA_ATTACK_DETECTED,
    CRITICAL_DRIVER_FAILURE,
    PAGE_TABLE_CORRUPTION,
    KERNEL_CODE_MODIFIED,
    EXCESSIVE_PRIVILEGE_ESCALATION,
    HARDWARE_FAULT,
    WATCHDOG_TIMEOUT,
    INVALID_INTERRUPT_VECTOR,
    MALICIOUS_PACKET_RECEIVED,
    READ_FROM_KERNEL_ONLY_MEMORY,
    HASH_MISMATCH_BOOT,
};

static enum LOCKDOWN_REASON lockdown_reason;

VOID put_system_lockdown(enum LOCKDOWN_REASON reason);



#endif /*__NOVANIX_KERNEL_LOCKDOWN_H*/