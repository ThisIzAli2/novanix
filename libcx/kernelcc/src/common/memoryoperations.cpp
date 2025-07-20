/**
 * @author Ali Mirmohammad
 * @file memoryoperations.cpp
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
#include <common/memoryoperations.h>

using namespace Novanix::common;

void* MemoryOperations::memmove(void* dstptr, const void* srcptr, uint32_t size)
{
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (uint32_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (uint32_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}
int MemoryOperations::memcmp(const void* aptr, const void* bptr, uint32_t size)
{
    const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (uint32_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}
void* MemoryOperations::memset(void* bufptr, char value, uint32_t size)
{
    unsigned char* buf = (unsigned char*) bufptr;
	for (uint32_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}
void* MemoryOperations::memcpy(void* dstptr, const void* srcptr, uint32_t size)
{
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (uint32_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}