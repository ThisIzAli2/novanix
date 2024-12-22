/**
 * @author Ali Mirmohammad
 * @file lock.hpp
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
 *  - Kernel lock implementation for C++ section.
*/
#ifndef __ALINIX_KERNEL_LOCK_HPP
#define __ALINIX_KERNEL_LOCK_HPP



/**
 * @brief Used to lock the mutex and proccess of the kernel.
*/
class MutexLock
{
private:
    int value = 0;
public:
    MutexLock();

    void Lock();
    void Unlock();
};

#endif /*__ALINIX_KERNEL_LOCK_HPP*/