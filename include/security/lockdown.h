#ifndef __NOVANIX_KERNEL_LOCKDOWN_H
#define __NOVANIX_KERNEL_LOCKDOWN_H


#include <common/init.hpp>

#define HALT_COMMAND asm volatile ("hlt")

enum LOCKDOWN_REASON{
    CORRUPT = 0,
};
VOID put_system_lockdown();

#endif /*__NOVANIX_KERNEL_LOCKDOWN_H*/