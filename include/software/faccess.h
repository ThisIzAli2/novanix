/**
 * @author Ali Mirmohammad
 * @file faccess.h
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
#ifndef __NOVANIX_KERNEL_F_ACCESS_H
#define __NOVANIX_KERNEL_F_ACCESS_H

#include <software/fcreate.h>

#define COUNT_FILES(files)  sizeof(files) / sizeof(file_t)

VOID read_file(char* file_name);
file_t* find_file_by_name(file_t* files, INTEGER file_count, const char* target_name);


#endif /*__NOVANIX_KERNEL_F_ACCESS_H*/