#ifndef __Novanix__SYSTEM__NEW_H
#define __Novanix__SYSTEM__NEW_H

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