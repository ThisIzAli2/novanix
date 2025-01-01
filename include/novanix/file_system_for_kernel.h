#ifndef __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_
#define __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_


#include <common/string.h>
#include <system/log.h>
#include <system/bootconsole.h>
#include <stringify.h>

using namespace Novanix::system;
#define MAX_SUBDIRECTORIES 128

#define MAX_DIRS 100  // Maximum number of directories
#define MAX_NAME_LEN 256  // Maximum length of directory names

#define CURRENT_DIR_BUFFER_SIZE 256

char* current_directory = "/home";


class FileSystem {
public:
    const char* currDir = "home";
    int dirCount = 0;  // Counter for directories
    char dirs[1000] = {0};
    INTEGER count = 0;
    char *dirArray[MAX_DIRS];  // Array to store directory names
private:
    char currentDirectory[CURRENT_DIR_BUFFER_SIZE] = "home";

    struct Directory {
        const char* name;
        Directory* subdirectories;
        int subdirectoryCount;
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

    auto mkdir(const char *name) {
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"A",1);
            if (dirCount >= MAX_DIRS) {
        Novanix::system::printk(
            Novanix::system::VGA_COLOR_WHITE,
            "Error: Maximum directory count reached.\n",
            1
        );
        return ;
    }

    // Allocate memory for the new directory name using the kernel heap
    dirArray[dirCount] = static_cast<char*>(
        Novanix::system::KernelHeap::malloc(
            Novanix::system::VGA_COLOR_WHITE, 
            reinterpret_cast<unsigned int*>(MAX_NAME_LEN)
        )
    );

    if (dirArray[dirCount] == nullptr) {
        Novanix::system::printk(
            Novanix::system::VGA_COLOR_WHITE,
            "Error: Memory allocation failed.\n",
            1
        );
        return;
    }

    // Copy the directory name to the array
    Novanix::common::String::strncpy(dirArray[dirCount], name, MAX_NAME_LEN - 1);
    dirArray[dirCount][MAX_NAME_LEN - 1] = '\0';  // Null-terminate the string

    dirCount++;

    // Print confirmation message
    Novanix::system::printk(
        Novanix::system::VGA_COLOR_WHITE,
        "Directory added successfully.\n",
        1
    );
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
        int index = 0;
        for (int i = 0; i < currentDir->subdirectoryCount; i++) {
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

#endif