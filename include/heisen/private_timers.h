#ifndef HEISEN_PRIV_TIMERS_H
#define HEISEN_PRIV_TIMERS_H

#include <heisen/typing.h>

PRIVATE int hpet_getcount();

PRIVATE int hpet_init();
PRIVATE int pit_init();
PRIVATE int rtc_init();
PRIVATE int apic_timer_init();
PRIVATE int apic_timer_tsc_init();

PRIVATE bool use_tsc();
PRIVATE int tsc_init();
PRIVATE int tsc_mp_init();

#endif // HEISEN_PRIV_TIMERS_H