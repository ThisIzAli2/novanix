/**
 * @author Ali Mirmohammad
 * @file node.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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

#ifndef __ALINIX_KERNEL_NODE_H
#define __ALINIX_KERNEL_NODE_H

/**
 * @abstraction:
 *  - Handles different kernel nodes.
 *  - Header file implemented.
*/
#include <alinix/types.h>
#include <alinix/interruptmanager.h>
#include <alinix/ulib.h>


/**
 * @brief Structure for the system nodes.
*/
typedef struct Node {
    void (*handler)(uint8_t);
    struct Node* next;
} Node;


/**
 * @brief Node data structure for the kernel DS.
*/
typedef struct List {
    Node* head;
    Node* tail;
} List;

void List_push(List* list, void (*handler)(uint8_t)) ;



void AddHandler(uint8_t interrupt, void (*handler)(uint8_t));

#endif /*__ALINIX_KERNEL_NODE_H*/