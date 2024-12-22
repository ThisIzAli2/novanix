/**
 * @author Ali Mirmohammad
 * @file list.h
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
 * @abstract:
 *   - Kernel lists header file implemented.
*/
#ifndef __ALINIX_KERNEL_LIST_H
#define __ALINIX_KERNEL_LIST_H

#include <alinix/types.h>
struct hlist_bl_node {
	struct hlist_bl_node *next, **pprev;
};

/**
 * @brief List head DS.
*/
struct list_head {
	struct list_head *next, *prev;
};

/**
 * __list_add_valid - Check if it is valid to add a new list entry between two existing entries
 * @new_: pointer to the new list entry
 * @prev: pointer to the previous list entry
 * @next: pointer to the next list entry
 *
 * This function checks if it is valid to add a new list entry between two existing entries.
 * It ensures that the pointers of the previous and next entries are correctly set to each other,
 * and that the new entry is not the same as the previous or next entry.
 *
 * Returns: true if it is valid to add the new entry, false otherwise.
 */
static inline bool __list_add_valid(struct list_head *new_,
					     struct list_head *prev,
					     struct list_head *next){
        bool ret = true;

        if (next->prev == prev && prev->next == next && new_ != prev && new_ != next){
            return true;
        }
        ret = false;
        
    
    return ret;
}




#endif // __ALINIX_KERNEL_LIST_H