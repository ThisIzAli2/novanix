/**
 * @file api.h
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

#ifndef __ALINIX_KERNEL_UCAPI_API__INCLUDED_H
#define __ALINIX_KERNEL_UCAPI_API__INCLUDED_H

#include <alinix/ucapi/types.h>

enum uacpi_log_level {
    /*
     * Super verbose logging, every op & uop being processed is logged.
     * Mostly useful for tracking down hangs/lockups.
     */
    UACPI_LOG_DEBUG = 4,

    /*
     * A little verbose, every operation region access is traced with a bit of
     * extra information on top.
     */
    UACPI_LOG_TRACE = 3,

    /*
     * Only logs the bare minimum information about state changes and/or
     * initialization progress.
     */
    UACPI_LOG_INFO  = 2,

    /*
     * Logs recoverable errors and/or non-important aborts.
     */
    UACPI_LOG_WARN  = 1,

    /*
     * Logs only critical errors that might affect the ability to initialize or
     * prevent stable runtime.
     */
    UACPI_LOG_ERROR = 0,
};


uacpi_status uacpi_kernel_raw_io_read(
    u64 address, u8 byte_width, u64 *out_value
);
uacpi_status uacpi_kernel_raw_io_write(
    u64 address, u8 byte_width, u64 in_value
);
void uacpi_kernel_log(enum uacpi_log_level, const char*, ...);


void uacpi_kernel_vlog(enum uacpi_log_level, const char*, va_list);



#endif /*__ALINIX_KERNEL_UCAPI_API__INCLUDED_H*/