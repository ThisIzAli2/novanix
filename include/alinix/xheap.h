/**
 * @author Ali Mirmohammad
 * @file xheap.h
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
 *  - Kernel x heap implemented.
*/
#ifndef __ALINIX_KERNEL_X_HEAP_H
#define __ALINIX_KERNEL_X_HEAP_H

#include <alinix/types.h>
#include <alinix/mm.h>

#define HEAP_MAGIC      0xA0B0C0



/**
 * @brief Heap data structure.
*/
typedef struct heap_header {
    int magic; // sanity check: 0xA0B0C0
    size_t size;
    int is_free;
    struct heap_header *next;
} heap_header_t;

typedef struct {
    size_t size;
    vmm_addr_t *start;
    size_t used;
    heap_header_t *first_header;
} heap_info_t;

/**
 * @brief X heap function(memory stuff)
 */
void heap_init(vmm_addr_t *addr);
void *umalloc(size_t len, vmm_addr_t *heap);
void ufree(void *ptr, vmm_addr_t *heap);
void *umalloc_sys(size_t len);
void ufree_sys(void *ptr);
void kheap_init();
void *kmalloc(size_t len);
void kfree(void *ptr);
void *first_free(size_t len);
int get_heap_size();
int get_used_heap();
void print_header(heap_header_t *head);

#endif /*__ALINIX_KERNEL_X_HEAP_H*/