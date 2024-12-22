/**
 * @file context.h
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


#ifndef __ALINIX_KERNEL__UCAPI_CONTEXT_H
#define __ALINIX_KERNEL__UCAPI_CONTEXT_H

#include <alinix/types.h>
#include "acpi.h"
#include "uacpi.h"
extern struct uacpi_runtime_context g_uacpi_rt_ctx;


struct uacpi_runtime_context {
    /*
     * A local copy of FADT that has been verified & converted to most optimal
     * format for faster access to the registers.
     */
    struct acpi_fadt fadt;

    /*
     * A cached pointer to FACS so that we don't have to look it up in interrupt
     * contexts as we can't take mutexes.
     */
    struct acpi_facs *facs;

    /*
     * pm1{a,b}_evt_blk split into two registers for convenience
     */
    struct acpi_gas pm1a_status_blk;
    struct acpi_gas pm1b_status_blk;
    struct acpi_gas pm1a_enable_blk;
    struct acpi_gas pm1b_enable_blk;

#define UACPI_SLEEP_TYP_INVALID 0xFF
    u8 last_sleep_typ_a;
    u8 last_sleep_typ_b;

    u8 s0_sleep_typ_a;
    u8 s0_sleep_typ_b;

    /*
     * This is a per-table value but we mimic the NT implementation:
     * treat all other definition blocks as if they were the same revision
     * as DSDT.
     */
    bool is_rev1;

#if UACPI_REDUCED_HARDWARE == 0
    bool is_hardware_reduced;
    bool has_global_lock;
    uacpi_handle sci_handle;
#endif /*UACPI_REDUCED_HARDWARE*/

#define UACPI_INIT_LEVEL_EARLY 0
#define UACPI_INIT_LEVEL_TABLES_LOADED 1
#define UACPI_INIT_LEVEL_NAMESPACE_LOADED 2
#define UACPI_INIT_LEVEL_NAMESPACE_INITIALIZED 3
    u8 init_level;

    struct uacpi_params params;
};

/**
 * uacpi_rt_should_log - Check if a log message should be logged
 * @lvl: the log level of the message to be logged
 *
 * This function checks if a log message with the specified log level @lvl
 * should be logged based on the current logging level configuration. It
 * returns true if the specified log level is less than or equal to the
 * current logging level configured in the global uacpi_rt_ctx context,
 * and false otherwise. This function is used to determine whether a log
 * message should be logged based on the current logging settings.
 */
static inline bool uacpi_rt_should_log(enum uacpi_log_level lvl)
{
    return lvl <= g_uacpi_rt_ctx.params.log_level;
}

#endif /*__ALINIX_KERNEL__UCAPI_CONTEXT_H*/