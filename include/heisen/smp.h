/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __HEISEN_SMP_H
#define __HEISEN_SMP_H

/*
 *	Generic SMP support
 *		Alan Cox. <alan@redhat.com>
 */

#include <heisen/typing.h>

void smp_init(void);

int smp_corecount(void);

int smp_platform_getstatesize(void);

void smp_platform_getstate(void* buf);

void smp_platform_setstate(void* buf);

void smp_platform_getdefaultstate(void *buf, void *stackpointer, void *instr_ptr, void *args);

void smp_signalready(void);
#endif /* __HEISEN_SMP_H */