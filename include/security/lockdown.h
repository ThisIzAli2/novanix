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


//TODO: Complete here
/**
 * Main Lockdown reasons.
 * Undeclared: We don't know yet.
 * ROOT_ACCESS_FAILED : There has been an attempt to brute force to sudo password.
 * ROOTKIT_DETECTED : There has been a rootkit in ther kernel files or system.
 * IO_PORT_ACCESS_VIOLATION : Unauthorized process accessed a hardware I/O port.
 * KERNEL_IMAGE_TAMPERED : 	Kernel's code segment has been modified after boot.
 * UNSIGNED_MODULE_LOADED : 	Module loaded into kernel was not verified or signed.
 * DEBUGGER_ATTACHED : 	A debugging tool has hooked into the kernel.
 * UNAUTHORIZED_SYSCALL : 	A syscall was called from an unexpected ring or address.
 * STACK_OVERFLOW_DETECTED : Stack smashing detected (via canaries or overflow checks).
 * INVALID_USER_PRIVILEGE : 	User process tried to execute a kernel-level instruction.
 * DMA_ATTACK_DETECTED : DMA-capable device tried to access sensitive memory.
 * CRITICAL_DRIVER_FAILURE : 	A kernel driver crashed or caused corruption.
 * PAGE_TABLE_CORRUPTION : 	Page tables were modified by unauthorized process.
 * KERNEL_CODE_MODIFIED : 	Kernel instruction page changed in memory (could be self-modifying code).
 * EXCESSIVE_PRIVILEGE_ESCALATION : Multiple failed attempts to elevate privileges.
 * 
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