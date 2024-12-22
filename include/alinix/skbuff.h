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
 * @file skbuff.h
 * @abstraction:
 *  - Kernel Sk buffer implementation header file.
*/
#ifndef __ALINIX_KERNEL_SK_BUFF_H
#define __ALINIX_KERNEL_SK_BUFF_H

#include <alinix/types.h>
#include <alinix/list.h>
#include <alinix/rbtree_types.h>
#include <alinix/llist.h>
#include <alinix/ktime.h>
#include <alinix/spinlock.h>
#include <alinix/spinlock_types.h>

/**
 * @brief https://github.com/torvalds/linux/blob/master/include/linux/skbuff.h#L855
*/

struct sk_buff;

struct sk_buff_head {
	/* These two members must be first to match sk_buff. */
    struct sk_buff	*next;
    struct sk_buff	*prev;

	u32		qlen;
	spinlock_t	lock;
};

struct sk_buff{
    union {
        struct {
            struct sk_buff * next;
            struct sk_buff * prev;
        };
        struct rb_node		rbnode; /* used in netem, ip4 defrag, and tcp stack */
		struct list_head	list;
		struct llist_node	ll_node;
    };

    union {
        ktime_t tstamp;
        u64		skb_mstamp_ns; /* earliest departure time */
    };
    char			cb[48] __attribute__((__aligned__(8)));

    union {
        struct {
            unsigned long _skb_refdst;
            struct sk_buff *skb;
        };
        struct list_head	tcp_tsorted_anchor;
    };
};

#endif // __ALINIX_KERNEL_SK_BUFF_H