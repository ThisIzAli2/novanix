#ifndef _HEISEN_TIMER_TYPES_H
#define _HEISEN_TIMER_TYPES_H

#include <heisen/lockdep_types.h>
#include <heisen/types.h>

struct timer_list {
	/*
	 * All fields that change during normal runtime grouped to the
	 * same cacheline
	 */
	struct hlist_node	entry;
	unsigned long		expires;
	void			(*function)(struct timer_list *);
	uint32_t			flags;

#ifdef CONFIG_LOCKDEP
	struct lockdep_map	lockdep_map;
#endif
};

#endif /* _HEISEN_TIMER_TYPES_H */