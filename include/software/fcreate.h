/**
 * @author Ali Mirmohammad
 * @file fcreate.h
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
#ifndef __FCREATE_NOVANIX_H
#define __FCREATE_NOVANIX_H


#include <common/init.hpp>
#include <fs/fs.h>

file_t __create_file(char* name,char* data,int size);
void create_file_function();


#endif /*__FCREATE_NOVANIX_H*/