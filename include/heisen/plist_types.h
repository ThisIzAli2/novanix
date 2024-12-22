#ifndef _HEISEN_PLIST_TYPES_H
#define _HEISEN_PLIST_TYPES_H

#include <heisen/types.h>

struct plist_head {
	struct list_head node_list;
};

struct plist_node {
	int			prio;
	struct list_head	prio_list;
	struct list_head	node_list;
};

#endif /* _HEISEN_PLIST_TYPES_H */