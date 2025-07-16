/**
 * @author Ali Mirmohammad
 * @file devlinkedlist.hpp
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
#ifndef __DEV_LINKED_LIST_HPP
#define __DEV_LINKED_LIST_HPP

#include <common/init.hpp>

template <typename T>
class SimpleList {
public:
    T* data;         // Array to store data of type T
    INTEGER capacity;    // Total capacity of the list
    INTEGER size;        // Current size of the list

    // Constructor to initialize the list with a specific capacity
    SimpleList(INTEGER cap) : capacity(cap), size(0) {
        data = new T[capacity]; // Allocate memory for the array of type T
    }

    // Function to add a new element to the list
    VOID append(T value) {
        if (size < capacity) {
            data[size] = value;
            size++;
        } else {
            Novanix::system::printk(VGA_COLOR_WHITE, "List is full!", 1);
        }
    }

    // Function to display the elements of the list
    VOID display() {
        if (size == 0) {
            Novanix::system::printk(VGA_COLOR_WHITE, "List is empty", 1);
            return;
        }

        for (INTEGER i = 0; i < size; i++) {
            // Printing each element (use the appropriate display function if needed)
            Novanix::system::printk(VGA_COLOR_WHITE, stringify(data[i]).c_str(), 1);
        }
    }

    // Destructor to free allocated memory
    ~SimpleList() {
        delete[] data;
    }
};

#endif