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
 * @file spinlock.h
 * @abstraction:
 * 	- Kernel spinlock implementations.
*/
#ifndef __ALINIX_KERNEL_SPIN_LOCK_H
#define __ALINIX_KERNEL_SPIN_LOCK_H

#include <alinix/kernel.h>
#include <alinix/assert.h>
#include <alinix/spinlock_types.h>

/**
 * Initializes a spin lock.
 *
 * @param lock A pointer to the spin lock to initialize.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_lock_init(spinlock_t *lock)
{
	int r = pthread_spin_init(lock, 0);
	assert(!r);
}

/**
 * Locks a spin lock.
 *
 * @param lock A pointer to the spin lock to lock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_lock(spinlock_t *lock)
{
	int ret = pthread_spin_lock(lock);
	assert(!ret);
}

/**
 * Unlocks a spin lock.
 *
 * @param lock A pointer to the spin lock to unlock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_unlock(spinlock_t *lock)
{
	int ret = pthread_spin_unlock(lock);
	assert(!ret);
}

/**
 * Locks a spin lock.
 *
 * @param lock A pointer to the spin lock to lock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_lock_bh(spinlock_t *lock)
{
	spin_lock(lock);
}

/**
 * Unlocks a spin lock.
 *
 * @param lock A pointer to the spin lock to unlock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_unlock_bh(spinlock_t *lock)
{
	spin_unlock(lock);
}

/**
 * Locks a spin lock in an interrupt-safe manner.
 *
 * @param lock A pointer to the spin lock to lock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_lock_irq(spinlock_t *lock)
{
	spin_lock(lock);
}

/**
 * Unlocks a spin lock in an interrupt-safe manner.
 *
 * @param lock A pointer to the spin lock to unlock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_unlock_irq(spinlock_t *lock)
{
	spin_unlock(lock);
}

/**
 * Locks a spin lock in an interrupt-safe manner with a specified flags parameter.
 *
 * @param lock A pointer to the spin lock to lock.
 * @param f The flags parameter for the spin lock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_lock_irqsave(spinlock_t *lock, unsigned long f)
{
	spin_lock(lock);
}

/**
 * Unlocks a spin lock in an interrupt-safe manner with a specified flags parameter.
 *
 * @param lock A pointer to the spin lock to unlock.
 * @param f The flags parameter for the spin lock.
 *
 * @return void
 *
 * @throws None
 */
static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long f)
{
	spin_unlock(lock);
}


#endif // __ALINIX_KERNEL_SPIN_LOCK_H