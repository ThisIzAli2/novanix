#ifndef __NOVANIX_KERNEL_LOCKDOWN_H
#define __NOVANIX_KERNEL_LOCKDOWN_H


#include <common/init.hpp>

#define HALT_COMMAND asm volatile ("hlt")

enum LOCKDOWN_REASON{
    UNDECLARED = 0,
    ROOT_ACCESS_FAILED =1,
};

static enum LOCKDOWN_REASON lockdown_reason;

VOID put_system_lockdown(enum LOCKDOWN_REASON reason);

#endif /*__NOVANIX_KERNEL_LOCKDOWN_H*/