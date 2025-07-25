/**
 * @author Ali Mirmohammad
 * @file file_system_for_kernel.h
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
#ifndef __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_
#define __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_


#include <common/string.h>
#include <system/log.h>
#include <system/bootconsole.h>
#include <stringify.h>
#include <novanix/strops.hpp>



using namespace Novanix::system;
#define MAX_SUBDIRECTORIES 128
//TODO: Make this variable obsolete, also move it to globals.h and globals.cpp to use it.
static char dir_name[256] = {0};  // Static array to store the directory name (fixed size)

#define MAX_DIRS 100  // Maximum number of directories
#define MAX_NAME_LEN 256  // Maximum length of directory names

#define CURRENT_DIR_BUFFER_SIZE 256

static char* current_directory = "/home";

/**
 * @brief This class is used to handle the kernel file system.
 */
class FileSystem {
public:
    const char* currDir = "home";
    INTEGER dirCount = 0;  // Counter for directories
    char dirs[1000] = {0};
    INTEGER count = 0;
    char listing[5][50];
    char* ls = new char[1024];
    char *dirArray[MAX_DIRS];  // Array to store directory names
private:
    char currentDirectory[CURRENT_DIR_BUFFER_SIZE] = "home";

    struct Directory {
        const char* name;
        Directory* subdirectories;
        INTEGER subdirectoryCount;
        Directory* parent;
    } root;

    Directory* findDirectory(Directory* dir, const char* name) {
        for (INTEGER i = 0; i < dir->subdirectoryCount; i++) {
            if (Novanix::common::String::strcmp(dir->subdirectories[i].name, name) == 0) {
                return &dir->subdirectories[i];
            }
        }
        return nullptr;
    }

public:
    FileSystem() {
        Novanix::common::String::strcpy(currentDirectory, "/");
        static Directory home = {"home", nullptr, 0, &root};
        static Directory usr = {"usr", nullptr, 0, &root};
        static Directory bin = {"bin", nullptr, 0, &root};
        static Directory subdirectories[] = {home, usr, bin};
        root = {"/", subdirectories, 3, nullptr};
    }

    void printCurrentDir() {
        Novanix::system::printk(VGA_COLOR_WHITE, "%s", 1, current_directory);
        return;
    }

    char* mkdir(const char *name, char* dirs[], INTEGER *count) {
    // Check if we can add more directories
    if (*count >= MAX_DIRS) {
        return nullptr;  // No space left to add more directories
    }

    if (contains(dir_name,256,name) == 1){
        return nullptr;
    }

    // Allocate memory for the directory name manually (using a static array for simplicity)

    // Calculate the length of the directory name
    INTEGER len = 0;
    while (name[len] != '\0') {
        len++;
    }

    // Copy the name into the static array
    for (INTEGER i = 0; i < len; i++) {
        dir_name[i] = name[i];
    }
    dir_name[len] = '\0';  // Null-terminate the string

    // Store the directory name in the dirs array
    dirs[*count] = dir_name;

    // Increment the count of directories
    (*count)++;

    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Created dir",1);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,name,1);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"\n",1);
    return dir_name;
    }

    bool rmdir(const char* name) {
        Directory* currentDir = findDirectory(&root, currentDirectory);
        if (!currentDir) {
            Novanix::system::printk(VGA_COLOR_RED, "Error: Current directory not found.\n",1);
            return false;
        }

        Directory* dirToRemove = findDirectory(currentDir, name);
        if (!dirToRemove) {
            Novanix::system::printk(VGA_COLOR_RED, "Error: Directory not found.\n",1);
            return false;
        }

        if (dirToRemove->subdirectoryCount > 0) {
            Novanix::system::printk(VGA_COLOR_RED, "Error: Directory is not empty.\n",1);
            return false;
        }

        Directory* newSubdirectories = new Directory[currentDir->subdirectoryCount - 1];
        INTEGER index = 0;
        for (INTEGER i = 0; i < currentDir->subdirectoryCount; i++) {
            if (&currentDir->subdirectories[i] != dirToRemove) {
                newSubdirectories[index++] = currentDir->subdirectories[i];
            }
        }

        delete[] currentDir->subdirectories;
        currentDir->subdirectories = newSubdirectories;
        currentDir->subdirectoryCount--;

        Novanix::system::printk(VGA_COLOR_GREEN, "Directory '%s' removed successfully.\n", 1,name);
        return true;
    }
};

#endif /*__NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_*/