/**
 * @author Ali Mirmohammad
 * @file contextheap.cpp
 * @Credits Remco123
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
#include <gui/contextheap.h>
#include <list.h>
#include <string.h>
#include <proc.h>
#include <typing.hpp>

using namespace Novanix;

#define ENTRIES_PER_BYTE 8
#define ARRAY_ENTRY_SIZE 4
#define ARRAY_ENTRIES (blockCount / ENTRIES_PER_BYTE / ARRAY_ENTRY_SIZE)

const int blockSize = 0x1000;
const uint32_t startAddress = 0xA0000000;
const uint32_t endAddress = 0xAB000000;

uint32_t* memoryBitmap = 0;
uint32_t blockCount = 0;

//To create thread safety for memory allocation
DECLARE_LOCK(bitmapOpperation);

__always_inline VOID SetBit(uint32_t bit)
{
    memoryBitmap[bit / 32] |= (1 << (bit % 32));
}
__always_inline VOID UnsetBit(uint32_t bit)
{
    memoryBitmap[bit / 32] &= ~ (1 << (bit % 32));
}
__always_inline bool TestBit(uint32_t bit)
{
    return memoryBitmap[bit / 32] & (1 << (bit % 32));
}


uint32_t FirstFreeSize(uint32_t size)
{
    for (uint32_t i = 0; i < ARRAY_ENTRIES; i++)
        if (memoryBitmap[i] != 0xFFFFFFFF) //Completely used
            for (int j = 0; j < (ENTRIES_PER_BYTE * ARRAY_ENTRY_SIZE); j++) {
                if ((memoryBitmap[i] & (1<<j)) == 0) //Test if bit is unset
                {
                    uint32_t startingBit = i * (ENTRIES_PER_BYTE * ARRAY_ENTRY_SIZE);
                    startingBit += j; //Calculate bit offset in total array

                    uint32_t free = 0; //Loop through each bit to see if its enough space
                    for (uint32_t count = 0; count <= size; count++)
                    {
                        if (!TestBit(startingBit + count))
                            free++; // this bit is clear (free frame)

                        if (free == size)
                            return (i * ENTRIES_PER_BYTE * ARRAY_ENTRY_SIZE) + j; //free count==size needed; return index
                    }
                }
            }

    return -1;
}

VOID ContextHeap::Init()
{
    //Calculate amount of blocks
    blockCount = (endAddress - startAddress) / blockSize;
    
    //Allocate bitmap
    memoryBitmap = new uint32_t[ARRAY_ENTRIES];

    //All memory is free at the start
    memset(memoryBitmap, 0x00, ARRAY_ENTRIES * sizeof(uint32_t));
}
uint32_t ContextHeap::AllocateArea(uint32_t blocks)
{
    LOCK(bitmapOpperation);
    uint32_t frame = FirstFreeSize(blocks);

    if (frame == (uint32_t)-1) {
        UNLOCK(bitmapOpperation);
        return 0; //not enough space
    }

    for (uint32_t i = 0; i < blocks; i++)
        SetBit(frame + i);

    UNLOCK(bitmapOpperation);
    return startAddress + frame * blockSize; 
}
VOID ContextHeap::FreeArea(uint32_t addr, uint32_t blocks)
{
    addr -= startAddress;
    uint32_t frame = addr / blockSize;

    LOCK(bitmapOpperation);
    for (uint32_t i = 0; i < blocks; i++)
        UnsetBit(frame + i);
    UNLOCK(bitmapOpperation);
}
double ContextHeap::MemoryUsage()
{
    uint32_t usedCount = 0;
    for (uint32_t i = 0; i < ARRAY_ENTRIES; i++) {
        if(memoryBitmap[i] == 0xFFFFFFFF)
            usedCount += 32;
        else
            for (int j = 0; j < 32; j++) {
                if (memoryBitmap[i] & (1<<j))
                    usedCount++;
            }
    }
    return ((double)usedCount / (double)blockCount);
}