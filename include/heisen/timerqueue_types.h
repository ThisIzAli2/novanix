#ifndef _HEISEN_TIMERQUEUE_TYPES_H
#define _HEISEN_TIMERQUEUE_TYPES_H

#include <heisen/rbtree_types.h>
#include <heisen/types.h>

struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};

struct timerqueue_head {
	struct rb_root_cached rb_root;
};

#endif /* _HEISEN_TIMERQUEUE_TYPES_H */