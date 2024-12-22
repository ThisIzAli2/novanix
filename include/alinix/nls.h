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
 * @file nls.h
 * @abstraction:
 * 	- Kernel NLS header file implemented.
*/

#ifndef __ALINIX_KERNEL_NLS_H
#define __ALINIX_KERNEL_NLS_H

struct nls_table {
	const char *charset;
	const char *alias;
	int (*uni2char) (int uni, unsigned char *out, int boundlen);
	int (*char2uni) (const unsigned char *rawstring, int boundlen,
			 int *uni);
	const unsigned char *charset2lower;
	const unsigned char *charset2upper;
	// struct module *owner;
	// struct nls_table *next;
};


#endif /*__ALINIX_KERNEL_NLS_H*/