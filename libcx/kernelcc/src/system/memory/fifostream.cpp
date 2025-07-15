/**
 * @author Ali Mirmohammad
 * @file fifostream.cpp
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
#include <system/memory/fifostream.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

FIFOStream::FIFOStream(INTEGER capacity)
{
    this->buffer = new char[capacity * sizeof(char)];
    this->buffer_end = (char*)this->buffer + capacity * sizeof(char);
    this->count = 0;
    this->capacity = capacity;
    this->head = this->buffer;
    this->tail = this->buffer;
}

FIFOStream::~FIFOStream()
{
    delete this->buffer;
}

VOID FIFOStream::Write(char item)
{
    if(this->count == this->capacity) {
        Log(Error, "Item count has reached capacity for this stream, data will be ignored. Capacity=%d", this->capacity);
        return;
    }

    MemoryOperations::memcpy((LPVOID)this->head, (LPVOID)&item, sizeof(char));
    this->head = (char*)(this->head + sizeof(char));
    if(this->head == this->buffer_end)
        this->head = this->buffer;
    
    this->count++;
}

char FIFOStream::Read()
{
    char result = 0;
    if(this->count == 0)
        return result;

    MemoryOperations::memcpy((LPVOID)&result, (LPVOID)this->tail, sizeof(char));
    this->tail = (char*)(this->tail + sizeof(char));
    if(this->tail == this->buffer_end)
        this->tail = this->buffer;

    this->count--;
    return result;
}

INTEGER FIFOStream::Available()
{
    return this->count;
}