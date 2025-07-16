/**
 * @author Ali Mirmohammad
 * @file fileeditor.h
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

#ifndef __NOVANIX_KERNEL_FILE_EDITOR_H
#define __NOVANIX_KERNEL_FILE_EDITOR_H

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>
#include <help.hpp>
#include <typing.hpp>
#include <shutdownsys.h>
#include <buffer.h>
#include <putchar.h>
#include <novanix/dir.h>
#include <novanix/user.h>
#include <novanix/access.h>
#include <novanix/time/time.hpp>
#include <alinix/types.h>


namespace Novanix {
namespace fs {

    // File permissions
    enum class Permission {
        READ = 1,
        WRITE = 2,
        EXECUTE = 4
    };

    class File {
    private:
        char* filename;  // Name of the file
        uint32_t file_size;  // Size of the file
        uint8_t* file_data;  // Pointer to the file's data
        uint32_t cursor_position;  // Current position of cursor (for reading/writing)

    public:
        // Constructor: initializes a file with the given name
        File(const char* name);

        // Destructor: releases any resources allocated for the file
        ~File();

        // Opens the file
        bool open(Permission permissions);

        // Reads from the file into the given buffer
        ssize_t read(char* buffer, size_t size);

        // Writes to the file from the given buffer
        ssize_t write(const char* buffer, size_t size);

        // Closes the file
        void close();

        // Gets the file's size
        uint32_t get_size() const;

        // Moves the cursor position within the file (used for seek operations)
        void seek(uint32_t position);

        // Checks if the file is open
        bool is_open() const;

        // Creates a new file (in memory for simulation purposes)
        static File* create(const char* name);
    };

}  // namespace fs
}  // namespace Novanix


#endif /*__NOVANIX_KERNEL_FILE_EDITOR_H*/