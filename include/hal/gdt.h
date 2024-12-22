#ifndef GDT_H
#define GDT_H

#include <types.h>

struct gdt_info {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t flags;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((__packed__));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((__packed__));

void gdt_init();
void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access);
extern void gdt_set(struct gdt_ptr *ptr);

#endif