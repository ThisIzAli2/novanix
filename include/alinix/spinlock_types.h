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
 * @file spinlock_types.h
 * @abstraction:    
 *  - Kernel spinlock types implementations header file.
*/
#ifndef __ALINIX_KERNEL_SPIN_LOCK_TYPES_H
#define __ALINIX_KERNEL_SPIN_LOCK_TYPES_H

/**
 * @brief Spinlock data type.
*/
typedef union{
    int  slock;	/* must be signed for proper  CHECK_WAITING */
}spinlock_t;

typedef spinlock_t local_lock_t;
#endif // __ALINIX_KERNEL_SPIN_LOCK_TYPES_H