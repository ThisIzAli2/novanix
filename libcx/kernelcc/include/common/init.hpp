/**
 * @author Ali Mirmohammad
 * @file init.hpp
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
#ifndef __NOVANIX_KERNEL_COMMON_INIT__HPP 
#define __NOVANIX_KERNEL_COMMON_INIT__HPP


#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>
#include <help.hpp>
#include <typing.hpp>
#include <shutdownsys.h>
#include <buffer.h>
#include <putchar.h>
#include <novanix/dir.h>
#include <novanix/user.h>
#include <novanix/access.h>
#include <novanix/time/time.hpp>
#include <system/memory/heap.h>


#ifndef __keep_inline 
#define __keep_inline inline
#endif //__keep_inline

static __keep_inline VOID outl(uint16_t port, uint32_t val) {
    asm volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}
static __keep_inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}



#define IS_NOT_EMPTY_OR_SPACES(s) ({                        \
    const char* _p = (s);                                   \
    int _result = 0;                                        \
    if (_p) {                                               \
        while (*_p) {                                       \
            if (*_p != ' ' && *_p != '\t' &&                \
                *_p != '\n' && *_p != '\r') {               \
                _result = 1;                                \
                break;                                      \
            }                                               \
            _p++;                                           \
        }                                                   \
    }                                                       \
    _result;                                                \
})

#define HALT_SYS asm volatile("hlt");


#endif /*__NOVANIX_KERNEL_COMMON_INIT__HPP */