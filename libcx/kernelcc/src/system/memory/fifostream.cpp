#include <system/memory/fifostream.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

FIFOStream::FIFOStream(int capacity)
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