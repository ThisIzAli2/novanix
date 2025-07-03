/**
 * @author Ali Mirmohammad
 * @file filehandle.h
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

#ifndef __NOVANIX_FILE_HANDLE_H
#define __NOVANIX_FILE_HANDLE_H

#include <common/init.hpp>

#define FILE_NAME_MAX 32
#define MAX_FILES 128
#define CONTENT_MAX 1024

// File structure
struct FileEntry {
    char name[FILE_NAME_MAX];
    char content[CONTENT_MAX];
    bool occupied;
};

// In-memory file system
static FileEntry file_table[MAX_FILES];

bool strings_equal(const char* a, const char* b, int max_len) {
    for (int i = 0; i < max_len; i++) {
        if (a[i] != b[i]) return false;
        if (a[i] == '\0') return true;
    }
    return true;
}

/**
 * @brief Function to copy a string 
 */
void string_copy(char* dest, const char* src, int max_len) {
    int i = 0;
    for (; i < max_len - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// Create a file with content

/**
 * @brief Function used to create a file
 */
__always_inline VOID create_file(const char name[FILE_NAME_MAX], const char content[CONTENT_MAX]) {
    // Validate file name
    int name_len = 0;
    while (name_len < FILE_NAME_MAX && name[name_len] != '\0') name_len++;
    if (name_len == FILE_NAME_MAX && name[FILE_NAME_MAX - 1] != '\0') {
        Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: Invalid file name", 1);
        return;
    }
    if (name_len == 0) {
        Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: Empty file name", 1);
        return;
    }

    // Validate content
    int content_len = 0;
    while (content_len < CONTENT_MAX && content[content_len] != '\0') content_len++;
    if (content_len == CONTENT_MAX && content[CONTENT_MAX - 1] != '\0') {
        Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: Content too large", 1);
        return;
    }

    // Duplicate name check
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table[i].occupied && strings_equal(file_table[i].name, name, FILE_NAME_MAX)) {
            Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: File already exists", 1);
            return;
        }
    }

    // Save in first empty slot
    for (int i = 0; i < MAX_FILES; i++) {
        if (!file_table[i].occupied) {
            string_copy(file_table[i].name, name, FILE_NAME_MAX);
            string_copy(file_table[i].content, content, CONTENT_MAX);
            file_table[i].occupied = true;

            Novanix::system::printk(Novanix::system::VGA_COLOR_GREEN, "File created: ", 1);
            Novanix::system::printk(Novanix::system::VGA_COLOR_GREEN, file_table[i].name, 1);
            return;
        }
    }

    Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: File system full", 1);
}


__always_inline VOID read_file(const char name[FILE_NAME_MAX]) {
    // Validate input name length (optional but recommended)
    int name_len = 0;
    while (name_len < FILE_NAME_MAX && name[name_len] != '\0') {
        name_len++;
    }
    if (name_len == 0) {
        Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: Empty file name", 1);
        return;
    }

    // Search for the file in file_table
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table[i].occupied) {
            // Manual string compare (same as before)
            bool match = true;
            for (int j = 0; j < FILE_NAME_MAX; j++) {
                if (file_table[i].name[j] != name[j]) {
                    match = false;
                    break;
                }
                if (name[j] == '\0') break;  // End of string matched
            }

            if (match) {
                // File found: print content
                Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "File content: ", 1);
                Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, file_table[i].content, 1);
                return;
            }
        }
    }

    // File not found
    Novanix::system::printk(Novanix::system::VGA_COLOR_RED, "Error: File not found", 1);
}


#endif // __NOVANIX_FILE_HANDLE_H