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


#define DEFAULT_FILE_SIZE 4

#define MAX_FILES 1000
static file_t files[MAX_FILES];

file_t __create_file(char* name,char* data,int size);
void create_file_function(char* data);
file_t __create_empty_file(char* name);

VOID create_empty_file(char* name);


#endif /*__FCREATE_NOVANIX_H*/