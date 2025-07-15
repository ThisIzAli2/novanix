#ifndef __NOVANIX_KERNEL_LOCKDOWN_H
#define __NOVANIX_KERNEL_LOCKDOWN_H


#include <common/init.hpp>

enum LOCKDOWN_REASON{
    CORRUPT = 0,
};
VOID put_system_lockdown();

#endif /*__NOVANIX_KERNEL_LOCKDOWN_H*/