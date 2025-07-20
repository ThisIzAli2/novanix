/**
 * @author Ali Mirmohammad
 * @file ops.h
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __NOVANIX_KERNEL_OPS_H
#define __NOVANIX_KERNEL_OPS_H


#include <common/init.hpp>

char binary_to_char(const char* bin);
void binary_to_string(const char* binary_input, char* output);
uint32_t string_to_binary(const char* input);
void char_to_binary(uint8_t c, char* buffer);
uint32_t strlen_kernel(const char* str);



#endif /*__NOVANIX_KERNEL_OPS_H*/