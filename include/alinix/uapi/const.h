/**
 * @file const.h
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
 * @abstract:
 *  - constants implementation.
*/
#ifndef __ALINIX_KERNEL_UAPI_CONST_H
#define __ALINIX_KERNEL_UAPI_CONST_H

#ifdef __ASSEMBLY__
#define _AC(X,Y)	X
#define _AT(T,X)	X
#else
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y)	__AC(X,Y)
#define _AT(T,X)	((T)(X))
#endif /*__ASSEMBLY__*/

#define _UL(x)		(_AC(x, UL))
#define _ULL(x)		(_AC(x, ULL))
#define UL(x) (_UL(x))

#define ULL(x)		(_ULL(x))
#define BIT_ULL(nr)		(ULL(1) << (nr))


#endif /*__ALINIX_KERNEL_UAPI_CONST_H*/