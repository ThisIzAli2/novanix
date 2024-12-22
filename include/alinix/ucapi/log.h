/**
 * @file log.h
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
 *  - UACPI util.
*/


#ifndef __ALINIX_KERNEL_LOG_H_UACPI_INCLUDED
#define __ALINIX_KERNEL_LOG_H_UACPI_INCLUDED

#include <alinix/ucapi/context.h>
#include <alinix/ucapi/types.h>

#define uacpi_log_lvl(lvl, ...) \
    do { if (uacpi_rt_should_log(lvl)) uacpi_kernel_log(lvl, __VA_ARGS__); } while (0)

#define uacpi_debug(...) uacpi_log_lvl(UACPI_LOG_DEBUG, __VA_ARGS__)
#define uacpi_trace(...) uacpi_log_lvl(UACPI_LOG_TRACE, __VA_ARGS__)
#define uacpi_info(...)  uacpi_log_lvl(UACPI_LOG_INFO, __VA_ARGS__)
#define uacpi_warn(...)  uacpi_log_lvl(UACPI_LOG_WARN, __VA_ARGS__)
#define uacpi_error(...) uacpi_log_lvl(UACPI_LOG_ERROR, __VA_ARGS__)

#endif /*__ALINIX_KERNEL_LOG_H_UACPI_INCLUDED*/