/**
 * @author Ali Mirmohammad
 * @file kobject.h
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
 * @abstraction:
 * 	- Kernel objects header file implemented.
*/
#ifndef __ALINIX_KERNEL_K_OBJECT_H
#define __ALINIX_KERNEL_K_OBJECT_H


#include <alinix/klist.h>
#include <alinix/spinlock_types.h>
#include <alinix/compiler_types.h>

void kobject_put(struct kobject *kobj);


enum kobject_action {
	KOBJ_ADD,
	KOBJ_REMOVE,
	KOBJ_CHANGE,
	KOBJ_MOVE,
	KOBJ_ONLINE,
	KOBJ_OFFLINE,
	KOBJ_BIND,
	KOBJ_UNBIND,
};


/**
 * @brief Kernel object DS.
*/

struct kobject {
	const char		*name;
	struct list_head	entry;
	struct kobject		*parent;
	struct kset		*kset;
	struct kref		kref;

	unsigned int state_initialized:1;
	unsigned int state_in_sysfs:1;
	unsigned int state_add_uevent_sent:1;
	unsigned int state_remove_uevent_sent:1;
	unsigned int uevent_suppress:1;

#ifdef CONFIG_DEBUG_KOBJECT_RELEASE
	struct delayed_work	release;
#endif /*CONFIG_DEBUG_KOBJECT_RELEASE*/
};

struct kset {
	struct list_head list;
	spinlock_t list_lock;
	struct kobject kobj;
	const struct kset_uevent_ops *uevent_ops;
} __randomize_layout;

/**
 * kset_put - Release a reference to a kset
 * @k: pointer to the kset structure
 *
 * This function releases a reference to a kset structure, decrementing
 * its reference count. If the reference count reaches zero, the kset
 * structure is deallocated.
 *
 * The function calls `kobject_put` with the kobject embedded in the kset
 * structure to release the reference.
 *
 * Example usage:
 *     kset_put(my_kset); // Release reference to my_kset
 */
static inline void kset_put(struct kset *k)
{
	kobject_put(&k->kobj);
}




#endif /*__ALINIX_KERNEL_K_OBJECT_H*/