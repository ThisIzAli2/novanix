/**
 * @author Ali Mirmohammad
 * @file fifostream.h
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
#ifndef __Novanix__SYSTEM__MEMORY__FIFOSTREAM_H
#define __Novanix__SYSTEM__MEMORY__FIFOSTREAM_H

#include <common/types.h>
#include <common/memoryoperations.h>
#include <system/memory/stream.h>

namespace Novanix
{
    namespace system
    {
        class FIFOStream : public Stream
        {
        private:
            // Internal buffer
            char* buffer;
            // End of the internal buffer
            char* buffer_end;
            // Number of items in the buffer
            int count;
            // Maximum allowed items
            int capacity;
            // Pointer to head
            char* head;
            // Pointer to tail
            char* tail;
        public:
            /**
             * Create a new fifo stream
            */
            FIFOStream(int capacity = 100);
            ~FIFOStream();

            /**
             * Read a byte from this stream
            */
            char Read();
            /**
             * Write a byte to this stream buffer
            */
            void Write(char byte);
            /**
             * How many bytes can currently be read?
            */
            int Available();
        };
    }
}

#endif