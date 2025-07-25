/**
 * @author Ali Mirmohammad
 * @file rand.h
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

#include <common/init.hpp>

static unsigned INTEGER seed = 123456789;


__always_inline INTEGER krand(){
    seed = seed * 1664525 + 1013904223;
    return seed;
}

unsigned __always_inline INTEGER kRandRange(unsigned INTEGER min, unsigned INTEGER max) {
    return min + (krand() % (max - min + 1));
}

INTEGER __always_inline motd_choice(){
    kRandRange(1,3);
}
const char __always_inline* randomCharFromArray(const char* arr, unsigned int len) {
    if (len == 0) return nullptr; // safety check, return null pointer

    unsigned INTEGER index = krand() % len;
    return &arr[index];  // return pointer to the character
}
