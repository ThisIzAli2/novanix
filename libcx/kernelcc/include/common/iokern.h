#ifndef __NOVANIX_KERNEL_IO_KERN_H
#define __NOVANIX_KERNEL_IO_KERN_H

#include <common/types.h>

using namespace Novanix::common;

static inline VOID outl(uint16_t port, uint32_t val) {
    asm volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t result;
    __asm__ volatile ("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}


#endif // __NOVANIX_KERNEL_IO_KERN_H