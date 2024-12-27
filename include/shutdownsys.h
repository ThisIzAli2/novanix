#ifndef __NOVANIX_KERNEL_SHUT_DOWN_SYS_H
#define __NOVANIX_KERNEL_SHUT_DOWN_SYS_H

#include <common/types.h>

static inline void outw(Novanix::common::uint16_t port, Novanix::common::uint16_t value) {
    __asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

#endif