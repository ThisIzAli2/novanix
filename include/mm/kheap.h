#ifndef KHEAP_H
#define KHEAP_H

#include <mm/heap.h>

void kheap_init();
void *kmalloc(size_t len);
void kfree(void *ptr);

void *first_free(size_t len);

int get_heap_size();
int get_used_heap();

void print_header(heap_header_t *head);

#endif