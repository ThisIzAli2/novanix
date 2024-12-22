/**
 * @author Ali Mirmohammad
 * @file port.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 * 	- Provide util header for the I/O ports.
*/

#ifndef __ALINIX_KERNEL_PORT_H
#define __ALINIX_KERNEL_PORT_H

#include <alinix/types.h>

unsigned char inportb (unsigned short _port);

void outportb (unsigned short _port, unsigned char _data);

unsigned short inportw(unsigned short _port);

void outportw(unsigned short _port, unsigned short _data);
unsigned int inportl(unsigned short _port);
void outportl(unsigned short _port, unsigned int _data);

void inportsm(unsigned short port, unsigned char * data, unsigned long size);

void outportsm(unsigned short port, unsigned char * data, unsigned long size) ;
inline static void outl(uint16_t port, uint32_t value) {
__asm__ volatile (
	"outl %0, %1"
	:
	: "a"(value), "Nd"(port)
);
}
void writeMemReg(const uint32_t addr, const uint32_t val);

uint32_t readMemReg(const uint32_t addr);

#define halt asm volatile("hlt")

#define enable_int asm volatile("sti")

#define disable_int asm volatile("cli")


static __inline__ void outsw(uint16_t __port, const void *__buf, unsigned long __n) {
	__asm__ __volatile__("cld; rep; outsw"
			: "+S"(__buf), "+c"(__n)
			: "d"(__port));
}

static __inline void insw(uint16_t __port, void *__buf, unsigned long __n) {
	__asm__ __volatile__("cld; rep; insw"
			: "+D"(__buf), "+c"(__n)
			: "d"(__port));
}
 

#endif // __ALINIX_KERNEL_PORT_H