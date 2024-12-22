/**
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
#ifndef __ALINIX_KERNEL_NET_PERF_H
#define __ALINIX_KERNEL_NET_PERF_H

#include <alinix/types.h>
// void perf_print(unsigned long c1l, unsigned long c1h,
// 		unsigned long c2l, unsigned long c2h,
// 		char *key);


#define PERF_START  { \
                         unsigned long __c1l, __c1h, __c2l, __c2h; \
                         __asm__(".byte 0x0f, 0x31" : "=a" (__c1l), "=d" (__c1h))
#define PERF_STOP(x)   __asm__(".byte 0x0f, 0x31" : "=a" (__c2l), "=d" (__c2h)); \
                       }
void pbuf_realloc(struct pbuf *p, uint16_t size); 

uint16_t pbuf_copy_partial(struct pbuf *p, void *dataptr, uint16_t len, uint16_t offset);


#endif