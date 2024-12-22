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
 * @file rculist.h
 * @abstract:
 * 	- Kernel list header file.
*/
#ifndef __ALINIX_KERNEL_RCU_LIST_H
#define __ALINIX_KERNEL_RCU_LIST_H


#include <alinix/types.h>


/**
 * hlist_add_tail_rcu - add a new entry to the hash list, at the tail
 * @n: the new entry to be added
 * @h: the hash list to add it to
 *
 * This function adds a new entry @n to the end of the hash list @h.
 * This function is safe to call concurrently with traversals and
 * deletions under RCU read locking.
 *
 * Note: write side code, so rcu accessors are not needed.
 */
static inline void hlist_add_tail_rcu(struct hlist_node *n,
				      struct hlist_head *h)
{
	struct hlist_node *i, *last = NULL;

	/* Note: write side code, so rcu accessors are not needed. */
	for (i = h->first; i; i = i->next)
		last = i;

	if (last) {
		n->next = last->next;
	} 
}

#endif /*__ALINIX_KERNEL_RCU_LIST_H*/