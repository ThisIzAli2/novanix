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
 * @file lsm_hooks.h
 * @abstract:
 * 	- Kernel files hook header file.
*/
#ifndef __ALINIX_KERNEL_LSM_HOOKS_H
#define __ALINIX_KERNEL_LSM_HOOKS_H

#include <alinix/types.h>

#define LSM_ID_LOCKDOWN 108

union security_list_options {
	#define LSM_HOOK(RET, DEFAULT, NAME, ...) RET (*NAME)(__VA_ARGS__);
	#undef LSM_HOOK
};

struct lsm_id {
	const char	*name;
	uint64_t	id;
};


struct security_hook_list {
	struct hlist_node		list;
	struct hlist_head		*head;
	union security_list_options	hook;
	const struct lsm_id		*lsmid;
} __randomize_layout;


#endif // __ALINIX_KERNEL_LSM_HOOKS_H