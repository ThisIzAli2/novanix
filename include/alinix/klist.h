/**
 * @author Ali Mirmohammad
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file klist.h
 * @abstraction:
 * 	- Kernel list implementation.
*/
#ifndef __ALINIX_KERNEL_K_LIST_H    
#define __ALINIX_KERNEL_K_LIST_H

#include <alinix/types.h>
#include <alinix/list.h>

typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;


struct kref {
	refcount_t refcount;
};

struct klist_node {
	void			*n_klist;	/* never access directly */
	struct list_head	n_node;
	struct kref		n_ref;
};


/**
 * @brief Kernel list data structure.
*/
struct klist {
	uint16_t		k_lock;
	struct list_head	k_list;
	void			(*get)(struct klist_node *);
	void			(*put)(struct klist_node *);
} __attribute__ ((aligned (sizeof(void *))));

extern int klist_node_attached(struct klist_node *n);

#endif /*__ALINIX_KERNEL_K_LIST_H*/