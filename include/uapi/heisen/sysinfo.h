#ifndef _HEISEN_SYSINFO_H
#define _HEISEN_SYSINFO_H


#include <heisen/typing.h>
#define SI_LOAD_SHIFT	16
struct sysinfo {
	__kernel_long_t uptime;		/* Seconds since boot */
	__kernel_ulong_t loads[3];	/* 1, 5, and 15 minute load averages */
	__kernel_ulong_t totalram;	/* Total usable main memory size */
	__kernel_ulong_t freeram;	/* Available memory size */
	__kernel_ulong_t sharedram;	/* Amount of shared memory */
	__kernel_ulong_t bufferram;	/* Memory used by buffers */
	__kernel_ulong_t totalswap;	/* Total swap space size */
	__kernel_ulong_t freeswap;	/* swap space still available */
	uint16_t procs;		   	/* Number of current processes */
	uint16_t pad;		   	/* Explicit padding for m68k */
	__kernel_ulong_t totalhigh;	/* Total high memory size */
	__kernel_ulong_t freehigh;	/* Available high memory size */
	uint32_t mem_unit;			/* Memory unit size in bytes */
	char _f[20-2*sizeof(__kernel_ulong_t)-sizeof(uint32_t)];	/* Padding: libc5 uses this.. */
};


#endif // _HEISEN_SYSINFO_H