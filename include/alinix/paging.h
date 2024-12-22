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
 * @file paging.h
 * @abstract:
 *  - Kernel Paging.
 *  - memory management.
*/
#ifndef __ALINIX_KERNEL_PAGING_H
#define __ALINIX_KERNEL_PAGING_H

#include <alinix/types.h>
#include <alinix/mm.h>



#define PAGE_SIZE           4096

#define PAGE_PRESENT        0x1
#define PAGE_RW             0x2
#define PAGE_USER           0x4
#define PAGE_ACCESSED       0x20
#define PAGE_FRAME_MASK     0x7FFFF000

typedef uint32_t page_dir_t;

#define PAGEDIR_SIZE        1024

void vmm_init();

void map_kernel(page_dir_t *pdir);

void change_page_directory(page_dir_t *p);
page_dir_t *get_page_directory();
page_dir_t *get_kern_directory();

int vmm_create_page_table(page_dir_t *pdir, vmm_addr_t virt, uint32_t flags);
int vmm_map(page_dir_t *pdir, vmm_addr_t virt, uint32_t flags);
int vmm_map_phys(page_dir_t *pdir, vmm_addr_t virt, mm_addr_t phys, uint32_t flags);
void *get_phys_addr(page_dir_t *pdir, vmm_addr_t virt);
page_dir_t *create_address_space();
void delete_address_space(page_dir_t *pdir);
void vmm_unmap_page_table(page_dir_t *pdir, vmm_addr_t virt);
void vmm_unmap(page_dir_t *pdir, vmm_addr_t virt);
void vmm_unmap_phys(page_dir_t *pdir, vmm_addr_t virt);

void *page_table_malloc();
void paging_set_bit(int bit);
void paging_unset_bit(int bit);
int paging_first_free();
void page_table_free(void *addr);
uint32_t *get_page_table_bitmap();

#endif  /*__ALINIX_KERNEL_PAGING_H*/