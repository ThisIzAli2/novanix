/**
 * @file uacpi.h
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
#ifndef __ALINIX_KERNEL_UACPI_H
#define __ALINIX_KERNEL_UACPI_H

#include "types.h"
#include "api.h"

#ifndef UACPI_REDUCED_HARDWARE
    #define UACPI_REDUCED_HARDWARE 0
#endif /*UACPI_REDUCED_HARDWARE*/

#if UACPI_REDUCED_HARDWARE == 1
#define UACPI_MAKE_STUB_FOR_REDUCED_HARDWARE(fn, ret) \
    UACPI_NO_UNUSED_PARAMETER_WARNINGS_BEGIN          \
    static inline fn { return (ret); }                \
    UACPI_NO_UNUSED_PARAMETER_WARNINGS_END

#define UACPI_ALWAYS_ERROR_FOR_REDUCED_HARDWARE(fn) \
    UACPI_MAKE_STUB_FOR_REDUCED_HARDWARE(fn, UACPI_STATUS_COMPILED_OUT)
#define UACPI_ALWAYS_OK_FOR_REDUCED_HARDWARE(fn) \
    UACPI_MAKE_STUB_FOR_REDUCED_HARDWARE(fn, UACPI_STATUS_OK)
#else

#if UACPI_REDUCED_HARDWARE != 0
#error UACPI_REDUCED_HARDWARE must be set to either 0 or 1
#endif /*UACPI_REDUCED_HARDWARE*/

#define UACPI_STUB_IF_REDUCED_HARDWARE(fn, ret) fn;
#define UACPI_ALWAYS_ERROR_FOR_REDUCED_HARDWARE(fn) fn;
#define UACPI_ALWAYS_OK_FOR_REDUCED_HARDWARE(fn) fn;
#endif

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*
 * Bad table checksum should be considered a fatal error
 * (table load is fully aborted in this case)
 */
#define UACPI_PARAM_BAD_CSUM_FATAL (1 << 0)

/*
 * Bad table header should be considered a fatal error
 * (table load is fully aborted in this case)
 */
#define UACPI_PARAM_BAD_TBL_HDR_FATAL (1 << 1)

/*
 * Force uACPI to use RSDT even for later revisions
 */
#define UACPI_PARAM_BAD_XSDT (1 << 2)

typedef struct uacpi_params {
    enum uacpi_log_level log_level;
    u64 flags;
} uacpi_params;

typedef struct uacpi_init_params {
    u64 rsdp;
    uacpi_params rt_params;

    /*
     * If this is set, ACPI mode is not entered during the call to
     * uacpi_initialize. The caller is expected to enter it later at thier own
     * discretion by using uacpi_enter_acpi_mode().
     */
    bool no_acpi_mode;
} uacpi_init_params;

/*
 * Initializes the uACPI subsystem, iterates & records all relevant RSDT/XSDT
 * tables. Enters ACPI mode.
 */
uacpi_status uacpi_initialize(struct uacpi_init_params*);

/*
 * Parses & executes all of the DSDT/SSDT tables.
 * Initializes the event subsystem.
 */
uacpi_status uacpi_namespace_load(void);

/*
 * Initializes all the necessary objects in the namespaces by calling
 * _STA/_INI etc.
 */
uacpi_status uacpi_namespace_initialize(void);

/*
 * Evaluate an object within the namespace and get back its value.
 * Either root or path must be valid.
 * A value of NULL for 'parent' implies uacpi_namespace_root() relative
 * lookups, unless 'path' is already absolute.
 */
uacpi_status uacpi_eval(uacpi_namespace_node *parent, const char *path,
                        uacpi_args *args, uacpi_object **ret);

/*
 * Same as uacpi_eval, but the return value type is validated against
 * the 'ret_mask'. UACPI_STATUS_TYPE_MISMATCH is returned on error.
 */
uacpi_status uacpi_eval_typed(
    uacpi_namespace_node *parent, const char *path,
    uacpi_args *args, u32 ret_mask, uacpi_object **ret
);

/*
 * A shorthand for uacpi_eval_typed with UACPI_OBJECT_INTEGER_BIT.
 */
uacpi_status uacpi_eval_integer(
    uacpi_namespace_node *parent, const char *path,
    uacpi_args *args, u64 *out_value
);

/*
 * Helpers for entering & leaving ACPI mode. Note that ACPI mode is entered
 * automatically during the call to uacpi_initialize().
 */
UACPI_ALWAYS_OK_FOR_REDUCED_HARDWARE(
    uacpi_status uacpi_enter_acpi_mode(void)
)
UACPI_ALWAYS_ERROR_FOR_REDUCED_HARDWARE(
    uacpi_status uacpi_leave_acpi_mode(void)
)

#ifdef __cplusplus
}
#endif // __cplusplus


#endif /*__ALINIX_KERNEL_UACPI_H*/