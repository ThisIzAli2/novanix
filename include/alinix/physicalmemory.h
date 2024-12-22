/**
 * @author Ali Mirmohammad
 * @file physicalmemory.h
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
 *  - Kernel Physical memory header file implementation.
 *  - Useful macros and DS implemented.
*/

#ifndef __ALINIX_KERNEL_PHYISCAL_MEMORY_H
#define __ALINIX_KERNEL_PHYISCAL_MEMORY_H

#include <alinix/types.h>

#define BLOCK_SIZE 4_KB
#define BLOCKS_PER_BYTE 8 //Every byte describes 8 blocks

#define	TAILQ_REMOVE(head, elm, field) do {				\
	if (((elm)->field.tqe_next) != NULL)				\
		(elm)->field.tqe_next->field.tqe_prev = 		\
		    (elm)->field.tqe_prev;				\
	else								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = (elm)->field.tqe_next;			\
} while (/*CONSTCOND*/0)

typedef struct multiboot_memory_map {
    unsigned int size;
    unsigned long base_addr_low;
    unsigned long base_addr_high;
    unsigned long length_low;
    unsigned long length_high;
    unsigned int type;
}  __attribute__((packed)) grub_multiboot_memory_map_t;

typedef struct {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} multiboot_info_t;

static uint32_t memorySize;
static uint32_t usedBlocks;
static uint32_t maximumBlocks;
static uint32_t* memoryArray;


/**
 * SetBit - Set a bit in the memory array
 * @bit: The bit number to set
 *
 * This function sets the specified bit in the memory array `memoryArray`.
 * It calculates the index of the `uint32_t` element in the array and then
 * sets the bit using a bitwise OR operation.
 *
 * Example usage:
 *     SetBit(5); // Set the 5th bit in the memory array
 */
static inline void SetBit(uint32_t bit) {
    memoryArray[bit / 32] |= (1 << (bit % 32));
}


/**
 * UnsetBit - Unset a bit in the memory array
 * @bit: The bit number to unset
 *
 * This function unsets (clears) the specified bit in the memory array `memoryArray`.
 * It calculates the index of the `uint32_t` element in the array and then unsets
 * the bit using a bitwise AND operation with the complement of a bit mask.
 *
 * Example usage:
 *     UnsetBit(5); // Unset the 5th bit in the memory array
 */
static inline void UnsetBit(uint32_t bit) {
    memoryArray[bit / 32] &= ~(1 << (bit % 32));
}


/**
 * TestBit - Test if a bit is set in the memory array
 * @bit: The bit number to test
 *
 * This function tests if the specified bit is set in the memory array `memoryArray`.
 * It calculates the index of the `uint32_t` element in the array and then tests
 * the bit using a bitwise AND operation with a bit mask.
 *
 * Returns: true if the bit is set, false otherwise.
 *
 * Example usage:
 *     bool isSet = TestBit(5); // Test if the 5th bit is set in the memory array
 */
static inline bool TestBit(uint32_t bit) {
    return memoryArray[bit / 32] & (1 << (bit % 32));
}

static uint32_t FirstFree();
static uint32_t FirstFreeSize(uint32_t size);


/**
 * Initialize - Initialize memory management parameters
 * @size: Total size of the memory region in bytes
 * @bitmap: Pointer to the memory bitmap array
 *
 * This function initializes the memory management parameters based on the
 * provided total size of the memory region and a pointer to the memory bitmap
 * array. It calculates the maximum number of blocks that can fit in the memory
 * region and sets the global variables `memorySize`, `maximumBlocks`, and
 * `memoryArray` accordingly.
 *
 * Example usage:
 *     Initialize(8192, (uint32_t*)0x1000); // Initialize with 8192 bytes and bitmap at address 0x1000
 */
static inline void Initialize(uint32_t size, uint32_t bitmap) {
    memorySize = size;
    maximumBlocks = size / 4096;
    memoryArray = (uint32_t*)bitmap;
}


/**
 * SetRegionFree - Set a memory region as free
 * @base: Base address of the memory region
 * @size: Size of the memory region in bytes
 *
 * This function sets a memory region as free by unsetting the corresponding
 * bits in the memory bitmap array. It calculates the start and end blocks
 * of the memory region based on the provided base address and size, and then
 * iterates over the blocks to unset the corresponding bits using the `UnsetBit`
 * function.
 *
 * Example usage:
 *     SetRegionFree(0x1000, 4096); // Set a 4KB memory region starting at address 0x1000 as free
 */
static inline void SetRegionFree(uint32_t base, uint32_t size) {
    uint32_t start = base / 4096;
    uint32_t end = (base + size) / 4096;
    for (uint32_t i = start; i < end; i++) {
        UnsetBit(i);
    }
}


/**
 * SetRegionUsed - Set a memory region as used
 * @base: Base address of the memory region
 * @size: Size of the memory region in bytes
 *
 * This function sets a memory region as used by setting the corresponding
 * bits in the memory bitmap array. It calculates the start and end blocks
 * of the memory region based on the provided base address and size, and then
 * iterates over the blocks to set the corresponding bits using the `SetBit`
 * function.
 *
 * Example usage:
 *     SetRegionUsed(0x2000, 8192); // Set an 8KB memory region starting at address 0x2000 as used
 */
static inline void SetRegionUsed(uint32_t base, uint32_t size) {
    uint32_t start = base / 4096;
    uint32_t end = (base + size) / 4096;
    for (uint32_t i = start; i < end; i++) {
        SetBit(i);
    }
}


/**
 * ParseMemoryMap - Parse the memory map provided by Multiboot
 * @mbi: Pointer to the Multiboot information structure
 *
 * This function parses the memory map provided by Multiboot and marks
 * the corresponding memory regions as used or free in the memory bitmap array.
 * It iterates over the memory map entries, each of which is 24 bytes long,
 * and extracts the base address, length, and type of each memory region.
 * Based on the type (1 for usable memory, others for reserved memory), it
 * calls the `SetRegionUsed` or `SetRegionFree` function to set the memory
 * region as used or free in the memory bitmap array.
 *
 * Example usage:
 *     ParseMemoryMap(mbi); // Parse the memory map provided by Multiboot
 */
static inline void ParseMemoryMap(const multiboot_info_t* mbi) {
    uint32_t mmap_addr = mbi->mmap_addr;
    uint32_t mmap_length = mbi->mmap_length;
    while (mmap_length > 0) {
        uint32_t base = *(uint32_t*)mmap_addr;
        uint32_t length = *(uint32_t*)(mmap_addr + 8);
        uint32_t type = *(uint32_t*)(mmap_addr + 16);
        if (type == 1) {
            SetRegionUsed(base, length);
        } else {
            SetRegionFree(base, length);
        }
        mmap_addr += 24;
        mmap_length -= 24;
    }
}

/**
 * AllocateBlock - Allocate a memory block
 *
 * This function allocates a memory block by finding the first free block
 * in the memory bitmap array and marking it as used. It then increments
 * the count of used blocks and returns a pointer to the allocated memory block.
 * If no free blocks are available, it returns NULL.
 *
 * Returns: A pointer to the allocated memory block, or NULL if no free blocks are available.
 *
 * Example usage:
 *     void* block = AllocateBlock(); // Allocate a memory block
 */
static inline void* AllocateBlock() {
    uint32_t free = FirstFree();
    if (free == (uint32_t)-1) {
        return NULL;
    }
    SetBit(free);
    usedBlocks++;
    return (void*)(free * 4096);
}

/**
 * FreeBlock - Free a memory block
 * @ptr: Pointer to the memory block to free
 *
 * This function frees a memory block by marking the corresponding block
 * in the memory bitmap array as free. It decrements the count of used blocks
 * and does not perform any actual memory deallocation.
 *
 * Example usage:
 *     FreeBlock(block); // Free a memory block
 */
static inline void FreeBlock(void* ptr) {
    uint32_t address = (uint32_t)ptr;
    uint32_t block = address / 4096;
    UnsetBit(block);
    usedBlocks--;
}

/**
 * AllocateBlocks - Allocate a contiguous block of memory
 * @size: Size of the memory block to allocate in bytes
 *
 * This function allocates a contiguous block of memory by finding the first
 * free block of the specified size in the memory bitmap array and marking
 * it and subsequent blocks as used. It then increments the count of used blocks
 * accordingly and returns a pointer to the allocated memory block. If a block
 * of the specified size is not available, it returns NULL.
 *
 * Returns: A pointer to the allocated memory block, or NULL if no suitable block is available.
 *
 * Example usage:
 *     void* block = AllocateBlocks(8192); // Allocate an 8KB memory block
 */
static inline void* AllocateBlocks(uint32_t size) {
    uint32_t free = FirstFreeSize(size);
    if (free == (uint32_t)-1) {
        return NULL;
    }
    uint32_t start = free;
    uint32_t end = free + (size / 4096);
    for (uint32_t i = start; i < end; i++) {
        SetBit(i);
    }
    usedBlocks += (size / 4096);
    return (void*)(start * 4096);
}

/**
 * FreeBlocksF - Free a contiguous block of memory
 * @ptr: Pointer to the start of the memory block to free
 * @size: Size of the memory block to free in bytes
 *
 * This function frees a contiguous block of memory by marking the corresponding
 * blocks in the memory bitmap array as free. It decrements the count of used
 * blocks accordingly and does not perform any actual memory deallocation.
 *
 * Example usage:
 *     FreeBlocksF(block, 8192); // Free an 8KB memory block starting at address 'block'
 */
static inline void FreeBlocksF(void* ptr, uint32_t size) {
    uint32_t address = (uint32_t)ptr;
    uint32_t start = address / 4096;
    uint32_t end = start + (size / 4096);
    for (uint32_t i = start; i < end; i++) {
        UnsetBit(i);
    }
    usedBlocks -= (size / 4096);
}

/**
 * AmountOfMemory - Get the total amount of memory
 *
 * This function returns the total amount of memory, in bytes, that
 * has been initialized for use by the memory management system.
 *
 * Returns: The total amount of memory in bytes.
 *
 * Example usage:
 *     uint32_t totalMemory = AmountOfMemory(); // Get the total amount of memory
 */
static inline uint32_t AmountOfMemory() {
    return memorySize;
}


/**
 * UsedBlocks - Get the number of used memory blocks
 *
 * This function returns the number of memory blocks that are currently
 * in use by the memory management system. Each block is assumed to be
 * 4096 bytes in size.
 *
 * Returns: The number of used memory blocks.
 *
 * Example usage:
 *     uint32_t usedBlocks = UsedBlocks(); // Get the number of used memory blocks
 */
static inline uint32_t UsedBlocks() {
    return usedBlocks;
}

/**
 * FreeBlocks - Get the number of free memory blocks
 *
 * This function returns the number of memory blocks that are currently
 * free and available for allocation by the memory management system.
 * Each block is assumed to be 4096 bytes in size.
 *
 * Returns: The number of free memory blocks.
 *
 * Example usage:
 *     uint32_t freeBlocks = FreeBlocks(); // Get the number of free memory blocks
 */
static inline uint32_t FreeBlocks() {
    return maximumBlocks - usedBlocks;
}

/**
 * TotalBlocks - Get the total number of memory blocks
 *
 * This function returns the total number of memory blocks that are
 * available for allocation by the memory management system. Each block
 * is assumed to be 4096 bytes in size.
 *
 * Returns: The total number of memory blocks.
 *
 * Example usage:
 *     uint32_t totalBlocks = TotalBlocks(); // Get the total number of memory blocks
 */
static inline uint32_t TotalBlocks() {
    return maximumBlocks;
}


/**
 * GetBitmapSize - Get the size of the memory bitmap array
 *
 * This function returns the size of the memory bitmap array in
 * 32-bit words. Each bit in the bitmap represents the status
 * (used or free) of a memory block. The size is calculated based
 * on the maximum number of memory blocks available for allocation.
 *
 * Returns: The size of the memory bitmap array in 32-bit words.
 *
 * Example usage:
 *     uint32_t bitmapSize = GetBitmapSize(); // Get the size of the memory bitmap array
 */
static inline uint32_t GetBitmapSize() {
    return maximumBlocks / 32;
}


/**
 * pageRoundUp - Round up an address to the nearest page boundary
 * @address: The address to round up
 *
 * This function rounds up the given address to the nearest page boundary.
 * It adds 4095 (0xFFF) to the address to ensure that any address within the
 * last page is rounded up to the start of the next page. It then uses a
 * bitwise AND operation with the complement of 4095 to effectively round
 * the address down to the nearest multiple of 4096 (0x1000), which is the
 * size of a page.
 *
 * Returns: The rounded-up address.
 *
 * Example usage:
 *     uint32_t roundedAddress = pageRoundUp(address); // Round up the address to the nearest page boundary
 */
static inline uint32_t pageRoundUp(uint32_t address) {
    return (address + 4095) & ~4095;
}

/**
 * pageRoundDown - Round down an address to the nearest page boundary
 * @address: The address to round down
 *
 * This function rounds down the given address to the nearest page boundary.
 * It uses a bitwise AND operation with the complement of 4095 to effectively
 * round the address down to the nearest multiple of 4096 (0x1000), which is
 * the size of a page.
 *
 * Returns: The rounded-down address.
 *
 * Example usage:
 *     uint32_t roundedAddress = pageRoundDown(address); // Round down the address to the nearest page boundary
 */
static inline uint32_t pageRoundDown(uint32_t address) {
    return address & ~4095;
}

#endif /*__ALINIX_KERNEL_PHYISCAL_MEMORY_H*/