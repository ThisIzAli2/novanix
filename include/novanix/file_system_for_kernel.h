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
    char listing[5][50];
    char* ls = new char[1024];
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

    char* mkdir(const char *name, char* dirs[], int *count) {
    // Check if we can add more directories
    if (*count >= MAX_DIRS) {
        return nullptr;  // No space left to add more directories
    }

    // Allocate memory for the directory name manually (using a static array for simplicity)
    static char dir_name[256];  // Static array to store the directory name (fixed size)

    // Calculate the length of the directory name
    int len = 0;
    while (name[len] != '\0') {
        len++;
    }

    // Copy the name into the static array
    for (int i = 0; i < len; i++) {
        dir_name[i] = name[i];
    }
    dir_name[len] = '\0';  // Null-terminate the string

    // Store the directory name in the dirs array
    dirs[*count] = dir_name;

    // Increment the count of directories
    (*count)++;

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