/**
 * @author Ali Mirmohammad
 * @file stream.hpp
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
 * @abstraction:
 *  - Kernel stream header file implementation for C++.
*/
#ifndef __ALINIX_KERNEL_STREAM_HPP
#define __ALINIX_KERNEL_STREAM_HPP

#ifndef __cplusplus
#warning "Including stream.hpp in C is not recommended"
#endif /*__cplusplus*/

#include <alinix/types.h>

class Stream
{
public:
    /**
     * Create a new instance of the stream class
    */
    Stream();
    /**
     * Delete the stream and free all the memory it has used
    */
    virtual ~Stream();

    /**
     * Read a byte from this stream
    */
    virtual char Read();
    /**
     * Write a byte to this stream buffer
    */
    virtual void Write(char byte);
    /**
     * How many bytes can currently be read?
    */
    virtual int Available();
};

#endif // __ALINIX_KERNEL_STREAM_HPP