/**
 * @author Ali Mirmohammad
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
 * @file crypto.h
 * @abstraction:
 * 	- Kernel crypto header file.
*/
#ifndef __ALINIX_KERNEL_CRYPTO_H
#define __ALINIX_KERNEL_CRYPTO_H

#include <alinix/types.h>
#include <alinix/klist.h>

#define ARCH_KMALLOC_MINALIGN 128
#define CRYPTO_MINALIGN ARCH_KMALLOC_MINALIGN
#define CRYPTO_MINALIGN_ATTR __attribute__ ((__aligned__(CRYPTO_MINALIGN)))

struct crypto_tfm {
	refcount_t refcnt;

	u32 crt_flags;

	int node;
	
	void (*exit)(struct crypto_tfm *tfm);
	
	struct crypto_alg *__crt_alg;

	void *__crt_ctx[] CRYPTO_MINALIGN_ATTR;
};

#endif /*__ALINIX_KERNEL_CRYPTO_H*/