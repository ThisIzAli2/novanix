#ifndef __NOVANIX_KERNEL_SHUT_DOWN_SYS_H
#define __NOVANIX_KERNEL_SHUT_DOWN_SYS_H

#include <common/types.h>

static inline void outw(Novanix::common::uint16_t port, Novanix::common::uint16_t value) {
    __asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

void inline shutdown_sys_now(){
    outw(0x604, 0x2000); // Port 0x604 is common for ACPI shutdown
}

#endif