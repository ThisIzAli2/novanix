/**
 * @author Ali Mirmohammad
 * @file new.h
 * @credits Remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __Novanix__SYSTEM__NEW_H
#define __Novanix__SYSTEM__NEW_H

/**
 * This file redefines all the operators needed for the kernel.
 */

#include <stddef.h>
#include <system/memory/heap.h>

using namespace Novanix::system;
 
void *operator new(size_t size)
{
    return KernelHeap::malloc(size);
}
 
void *operator new[](size_t size)
{
    return KernelHeap::malloc(size);
}

void* operator new(size_t size, void* ptr)
{
    return ptr;
}

void* operator new[](size_t size, void* ptr)
{
    return ptr;
}
 
void operator delete(void *p)
{
    KernelHeap::free(p);
}
 
void operator delete[](void *p)
{
    KernelHeap::free(p);
}

void operator delete(void* ptr, size_t size)
{
    KernelHeap::free(ptr);
}
void operator delete[](void* ptr, size_t size)
{
    KernelHeap::free(ptr);
}

#endif