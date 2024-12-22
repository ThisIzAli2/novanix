/**
 * @author Ali Mirmohammad
 * @file virtualmemory.h
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
 *  - Kernel virtual memory header file implementations.
*/
#ifndef __ALINIX_KERNEL_VIRTUAL_MEMORY_H
#define __ALINIX_KERNEL_VIRTUAL_MEMORY_H


#include <alinix/types.h>

// void* BootPageDirectory;
enum PAGE_ENTRY_SIZE
{
    FOUR_KB = 0,
    FOUR_MB = 1
};

#define KERNEL_VIRT_ADDR 3_GB
#define USER_STACK_SIZE 32_KB
#define USER_STACK_TOP (KERNEL_VIRT_ADDR)
#define USER_STACK (USER_STACK_TOP - USER_STACK_SIZE)

#define PAGE_SIZE (4 * 1024)  /* 4_KB */
#define KERNEL_PTNUM 768 //The kernel is in the 768th entry
#define PAGE_TABLE_ADDRESS 0xFFC00000
#define PAGE_DIRECTORY_ADDRESS 0xFFFFF000

#define PAGE_OFFSET_BITS 12

#define PAGEDIR_INDEX(addr) (((uint32_t)addr) >> 22)
#define PAGETBL_INDEX(addr) ((((uint32_t)addr) >> 12) & 0x3ff)
#define PAGEFRAME_INDEX(addr) (((uint32_t)addr) & 0xfff)


/**
 * @brief Entry directory of the page as structure.
*/
struct PageDirectoryEntry
{
    uint32_t present        : 1;    //Is this page present in physical memory or perhaps on the disk.
    uint32_t readWrite      : 1;    //If set the page is r/w otherwise read only.
    uint32_t isUser         : 1;    //If set the page can be accessed by all levels.
    uint32_t writeThrough   : 1;    //If set write through caching is enabled.
    uint32_t canCache       : 1;    //If the bit is set, the page will not be cached.
    uint32_t accessed       : 1;    //Has this page been accesed, set by cpu.
    uint32_t reserved       : 1;    //Reserved.
    uint32_t pageSize       : 1;    //If the bit is set, then pages are 4 MiB in size. Otherwise, they are 4 KiB.
    uint32_t ignored        : 1;
    uint32_t unused         : 3;    //Unused by the cpu so we can use them perhaps for additional page information.
    uint32_t frame          : 20;   //Page Table 4-kb aligned address.
} __attribute__((packed));

struct PageTableEntry
{
    uint32_t present        : 1;    //Is this page present in physical memory or perhaps on the disk.
    uint32_t readWrite      : 1;    //If set the page is r/w otherwise read only.
    uint32_t isUser         : 1;    //If set the page can be accessed by all levels.
    uint32_t writeThrough   : 1;    //If set write through caching is enabled.
    uint32_t canCache       : 1;    //If the bit is set, the page will not be cached.
    uint32_t accessed       : 1;    //Has this page been accesed, set by cpu.
    uint32_t dirty          : 1;    //Indicates that the page has been written to.
    uint32_t reserved       : 1;
    uint32_t global         : 1;    //if set, prevents the TLB from updating the address in its cache if CR3 is reset. Note, that the page global enable bit in CR4 must be set to enable this feature. 
    uint32_t unused         : 3;    //Unused by the cpu so we can use them perhaps for additional page information.
    uint32_t frame          : 20;   //Target memory 4kb block
} __attribute__((packed));

struct PageTable
{
    struct PageTableEntry entries[1024];
}   __attribute__((packed));

struct PageDirectory
{
    struct PageDirectoryEntry entries[1024];
}   __attribute__((packed));

// Invalidate TLB Entries
static inline void invlpg(void* addr)
{
    asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void* GetPageForAddress(uint32_t virtualAddress, bool shouldCreate, bool readWrite, bool userPages);

#endif /*__ALINIX_KERNEL_VIRTUAL_MEMORY_H*/