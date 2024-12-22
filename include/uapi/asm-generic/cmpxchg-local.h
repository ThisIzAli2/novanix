#ifndef __ASM_GENERIC_CMPXCHG_LOCAL_H
#define __ASM_GENERIC_CMPXCHG_LOCAL_H


#include <heisen/typing.h>
#include <heisen/irqflags.h>

extern unsigned long wrong_size_cmpxchg(volatile void *ptr)
	__noreturn;

/*
 * Generic version of __cmpxchg_local (disables interrupts). Takes an unsigned
 * long parameter, supporting various types of architectures.
 */
static inline unsigned long __generic_cmpxchg_local(volatile void *ptr,
		unsigned long old, unsigned long new, int size)
{
	unsigned long flags, prev;

	/*
	 * Sanity checking, compile-time.
	 */
	if (size == 8 && sizeof(unsigned long) != 8)
		wrong_size_cmpxchg(ptr);

	raw_local_irq_save(flags);
	switch (size) {
	case 1: prev = *(uint8_t *)ptr;
		if (prev == (old & 0xffu))
			*(uint8_t *)ptr = (new & 0xffu);
		break;
	case 2: prev = *(uint16_t *)ptr;
		if (prev == (old & 0xffffu))
			*(uint16_t *)ptr = (new & 0xffffu);
		break;
	case 4: prev = *(uint32_t *)ptr;
		if (prev == (old & 0xffffffffu))
			*(uint32_t *)ptr = (new & 0xffffffffu);
		break;
	case 8: prev = *(uint64_t *)ptr;
		if (prev == old)
			*(uint64_t *)ptr = (uint64_t)new;
		break;
	default:
		wrong_size_cmpxchg(ptr);
	}
	raw_local_irq_restore(flags);
	return prev;
}

/*
 * Generic version of __cmpxchg64_local. Takes an uint64_t parameter.
 */
static inline uint64_t __generic_cmpxchg64_local(volatile void *ptr,
		uint64_t old, uint64_t new)
{
	uint64_t prev;
	unsigned long flags;

	raw_local_irq_save(flags);
	prev = *(uint64_t *)ptr;
	if (prev == old)
		*(uint64_t *)ptr = new;
	raw_local_irq_restore(flags);
	return prev;
}

#endif