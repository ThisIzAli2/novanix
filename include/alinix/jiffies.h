/**
 * @author Ali Mirmohammad
 * @file jiffies.h
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
 * 	- Kernel jiffies header file implemented here.
 * 	- Useful macros defined.
*/
#ifndef __ALINIX_KERNEL_JIFFIES_H
#define __ALINIX_KERNEL_JIFFIES_H

#include <alinix/types.h>
#include <alinix/limits.h>

#define MSEC_PER_SEC	1000L
#define USEC_PER_MSEC	1000L
#define NSEC_PER_USEC	1000L
#define NSEC_PER_MSEC	1000000L
#define USEC_PER_SEC	1000000L
#define NSEC_PER_SEC	1000000000L
#define PSEC_PER_SEC	1000000000000LL
#define FSEC_PER_SEC	1000000000000000LL
#define HZ 1000


#define MAX_JIFFY_OFFSET ((LONG_MAX >> 1)-1)


/**
 * _msecs_to_jiffies - Convert milliseconds to jiffies
 * @m: number of milliseconds to convert
 *
 * This function converts a time duration in milliseconds to the equivalent
 * number of jiffies. Jiffies are the unit of time used by the Linux kernel
 * to measure time intervals, and their length depends on the value of `HZ`,
 * which defines the number of jiffies per second.
 *
 * The conversion is performed by dividing the number of milliseconds by
 * the length of a jiffy in milliseconds (`MSEC_PER_SEC / HZ`), with
 * rounding up to ensure that any fractional jiffies are accounted for.
 *
 * Example usage:
 *     unsigned long jiffies = _msecs_to_jiffies(100); // Convert 100 ms to jiffies
 *
 * Returns: The equivalent number of jiffies.
 */
static inline unsigned long _msecs_to_jiffies(const unsigned int m)
{
	return (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
}


/**
 * msecs_to_jiffies - Convert milliseconds to jiffies
 * @m: number of milliseconds to convert
 *
 * This function converts a time duration in milliseconds to the equivalent
 * number of jiffies. Jiffies are the unit of time used by the Linux kernel
 * to measure time intervals, and their length depends on the value of `HZ`,
 * which defines the number of jiffies per second.
 *
 * If the input value @m is greater than zero, the function checks if @m is
 * negative and returns `MAX_JIFFY_OFFSET` if it is. Otherwise, it calls
 * `_msecs_to_jiffies` to perform the conversion.
 *
 * If @m is zero, the function returns 0, indicating that no jiffies have
 * elapsed.
 *
 * Example usage:
 *     unsigned long jiffies = msecs_to_jiffies(100); // Convert 100 ms to jiffies
 *
 * Returns: The equivalent number of jiffies.
 */
static __always_inline unsigned long msecs_to_jiffies(const unsigned int m)
{
	if (m) {
		if ((int)m < 0)
			return MAX_JIFFY_OFFSET;
		return _msecs_to_jiffies(m);
	} else {
		return _msecs_to_jiffies(m);
        // TODO Change here
	}
}



#endif // __ALINIX_KERNEL_JIFFIES_H