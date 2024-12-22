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
 * @file ctrl.h
 * Purpose:
 *      - Provide more control over controlling the flow
*/

/**
 * @abstraction:
 *  - Kernel control stuff.
*/
#ifndef __ALINIX_KERNEL_CTRL_H
#define __ALINIX_KERNEL_CTRL_H



#include <alinix/types.h>

typedef void USBDriver;


/**
 * @brief InterruptTransfer data structure.
*/
typedef struct InterruptTransfer
{
    uint8_t* bufferPointer;
    uint32_t bufferPhys;
    int bufferLen;

    USBDriver* handler;
    int queueIndex;

    uint32_t tdPhys;
    void* td;
    int numTd;

    void* qh;
    int endpoint;
} InterruptTransfer_t;

#endif /*__ALINIX_KERNEL_CTRL_H*/