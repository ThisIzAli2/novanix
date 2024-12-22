#ifndef _HEISEN_BOOT_MEM_ALLOC_H
#define _HEISEN_BOOT_MEM_ALLOC_H

#include <heisen/stddef.h>
#include <heisen/stdint.h>
void bootstrap_malloc_init(uintptr_t kernel_end_virt);
void *bootstrap_malloc(size_t s);
void bootstrap_free(void *mem, size_t s);
void bootstrap_malloc_update_handlers(void*(*malloc_hndl)(size_t), void (*free_hndl)(void*));

#endif