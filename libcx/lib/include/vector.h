/**
 * @author Ali Mirmohammad
 * @file vector.h
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
#ifndef __Novanix__VECTOR_H
#define __Novanix__VECTOR_H

#include <types.h>

namespace Novanix
{
    template<typename T>
    class Vector
    {
    private:
        uint32_t size = 0;
        uint32_t capacity = 0;
        T* buffer = 0;

        void reserve(int capacity)
        {
            T* newBuf = new T[capacity];
            memcpy(newBuf, this->buffer, sizeof(T) * this->size);

            this->capacity = capacity;
            
            if(this->buffer)
                delete this->buffer;
            this->buffer = newBuf;
        }
    public:
        Vector()
        {
            this->size = 0;
            this->capacity = 0;
            this->buffer = 0;
        }
        ~Vector()
        { this->clear(); }

        int Size()
        { return this->size; }

        void push_back(const T& item)
        {
            if(this->capacity == 0)
                reserve(10);
            else if(this->size == this->capacity)
                reserve(2 * this->size);
            
            this->buffer[this->size] = item;
            this->size++;
        }

        void pop_back()
        { this->size--; }

        void clear()
        {
            this->capacity = 0;
            this->size = 0;

            if(this->buffer)
                delete this->buffer;
            this->buffer = 0;
        }

        T& GetAt(int n)
        { return this->buffer[n]; }

        T& operator[](int n)
        { return this->buffer[n]; }

        T* data()
        { return this->buffer; }

        ///////////////////
        // Iterators
        ///////////////////

        typedef T* iterator;
        iterator begin()
        {
            return this->buffer;
        }

        iterator end()
        {
            return this->buffer + this->size;
        }
    };
}

#endif