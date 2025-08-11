/**
 * @author Ali Mirmohammad
 * @file global.cpp
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
#include <global.h>
#include <fs/zip.hpp>
#include <fs/fat16.h>
#include <fs/fat32.h>

/**
 * IMPORTANT: Define all the global variables here after the extern definition
 */
file_t files[MAX_FILES];
INTEGER i_file = 0;
Snake snake;
INTEGER counts_failed_sudo = 0;
bool have_access = false;
char user_password[50] = "admin";
ZipFile zip_manager;
char* current_directory = "/home";
struct fat16_fs novanix_fat16_fs;
struct block_dev my_block_device; 
fat32_fs_t fs;