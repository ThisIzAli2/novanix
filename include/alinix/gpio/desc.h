/**
 * @file desc.h
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
 * 	- GPIO header file for driver util.
*/
#ifndef _ALINIX_KERNEL_DESC_H
#define _ALINIX_KERNEL_DESC_H

#include <alinix/types.h>

struct gpio_desc {
	unsigned	valid		: 1;
	unsigned	can_wakeup	: 1;
	unsigned	keypad_gpio	: 1;
	unsigned	dir_inverted	: 1;
	unsigned int	mask; /* bit mask in PWER or PKWR */
	unsigned int	mux_mask; /* bit mask of muxed gpio bits, 0 if no mux */
	unsigned long	config;
};

#endif /*_ALINIX_KERNEL_DESC_H*/