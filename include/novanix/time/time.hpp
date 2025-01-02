#pragma once


#include <common/types.h>
#include <typing.hpp>
#include <system/log.h>
#include <novanix/ops.h>

static inline Novanix::common::uint64_t read_tsc(void) {
    Novanix::common::uint32_t low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return ((Novanix::common::uint64_t)high << 32) | low;
}

void display_time(void) {
    Novanix::common::uint64_t tsc = read_tsc();
    
    Novanix::common::uint64_t time_in_seconds = __udivdi3(1000000000,tsc);  // Assuming 1 GHz clock for simplicity
    
    // Convert time to a readable format
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Time since boot: %llu seconds\n", 1,time_in_seconds);
}