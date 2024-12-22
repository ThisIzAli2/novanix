/**
 * @file io.h
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


#ifndef __ALINIX_KERNEL_U_CAPI_IO_H
#define __ALINIX_KERNEL_U_CAPI_IO_H

#include <alinix/ucapi/acpi.h>
#include <alinix/ucapi/types.h>
#include <alinix/types.h>

uacpi_status uacpi_gas_read(const struct acpi_gas *gas, u64 *value);
uacpi_status uacpi_gas_write(const struct acpi_gas *gas, u64 value);

#endif /*__ALINIX_KERNEL_U_CAPI_IO_H*/