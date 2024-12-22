/**
 * @author Ali Mirmohammad
 * @file thread.h
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

/**
 * @file thread.h
 * @abstraction:
 *  - Kernel threading and threads handling implementation.
 *  - Header file.
*/
#ifndef __ALINIX_KERNEL_THREAD_H
#define __ALINIX_KERNEL_THREAD_H

#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/register.h>


/**
 * @brief Thread structure.
 * @brief May be used to run a thread.
*/
struct Thread
{
    enum Process* parent;
    uint8_t* stack;
    uint8_t* userStack;
    uint32_t userStackSize;
    enum ThreadState state;
    enum BlockedState blockedState;
    struct CPUState* regsPtr;
    
    uint32_t timeDelta;
    uint8_t* FPUBuffer;
};

#endif /*__ALINIX_KERNEL_THREAD_H*/