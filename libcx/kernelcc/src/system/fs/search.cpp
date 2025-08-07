/**
 * @author Ali Mirmohammad
 * @file search.cpp
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

#include <fs/filesearch.h>
#include <common/string.h>
#include <global.h>

/**
 * @brief Search a file according to its name.
 */
file_t search_file(char* name) {
    INTEGER i;
    INTEGER files_size = sizeof(files) / sizeof(files[0]);

    for (i = 0; i < files_size; i++) {
        // If names are equal (strcmp returns 0), return the file
        if (String::strcmp(name, files[i].name) == 0) {
            return files[i];
        }
    }

    // Return an empty or invalid file if not found (you must define this behavior)
    file_t not_found;  // Assuming file_t can be default-initialized
    not_found.name = "not found!";
    return not_found;
}
