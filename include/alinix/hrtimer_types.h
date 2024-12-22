/**
 * @author Ali Mirmohammad
 * @file hrtimer_types.h
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
#ifndef __ALINIX_KERNEL_HRT_TIMER_TYPES_H
#define __ALINIX_KERNEL_HRT_TIMER_TYPES_H


#include <alinix/types.h>
#include <alinix/timerqueue_types.h>

struct hrtimer {
	struct timerqueue_node		node;
	ktime_t				_softexpires;
	enum hrtimer_restart		(*function)(struct hrtimer *);
	struct hrtimer_clock_base	*base;
	uint8_t				state;
	uint8_t				is_rel;
	uint8_t				is_soft;
	uint8_t				is_hard;
};

#endif /*__ALINIX_KERNEL_HRT_TIMER_TYPES_H*/