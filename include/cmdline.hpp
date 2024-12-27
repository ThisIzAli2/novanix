#pragma once

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>
#include <help.hpp>
#include <typing.hpp>
#include <shutdownsys.h>


INTEGER __always_inline cmd_cmp(const char* str1, const char* str2) {
    // Compare each character of both strings
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;  // Return the difference if characters are different
        }
        str1++;
        str2++;
    }

    // If both strings are the same length, return 0 (strings are equal)
    // Otherwise, return the difference between the null terminator of one string and the other string's character
    return *str1 - *str2;
}

__always_inline VOID cmdline() {
    char* key = new char[2];  // Single character input
    int index = 0;
    char* cmd = new char[128];  // Command buffer
    int i = 0;
    char* full_cmd = new char[128];  // To hold the full command
    int j = 0;
    
    // Print the prompt
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, ">", 0);
    
    do {
        // Read the key and handle the input
        read_key();
        key = handle_keyboard(read_key());  // Get the key pressed
        
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, key, 0);
        
        if (key != nullptr) {
            if (index < 127) {
                // Check if Enter key is pressed
                if (key[0] == '\n') {
                    // Copy cmd to full_cmd when Enter is pressed
                    for (int k = 0; k < index; ++k) {
                        full_cmd[k] = cmd[k];
                    }
                    full_cmd[index] = '\0';  // Null-terminate the full_cmd string

                    // Print the full command entered
                    // Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, stringify((int)key), 0);

                    // Compare full_cmd with "help"
                    if (cmd_cmp(full_cmd, "help") == 0) {
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, HELP_MENU,1);
                    }
                    if (cmd_cmp(full_cmd,"shutdown-now") == 0){
                        shutdown_sys_now();
                    }
                    else if (cmd_cmp(full_cmd, "") == 0){

                    }
                    else {
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Your command does not exists",1);
                    }
                    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">", 0);

                    // Reset the cmd and full_cmd arrays
                    Novanix::common::MemoryOperations::memset(cmd, 0, 128);  // Clear cmd array
                    Novanix::common::MemoryOperations::memset(full_cmd, 0, 128);  // Clear full_cmd array
                    index = 0;  // Reset the index for the next command
                } else {
                    // Store the character in cmd if it's not Enter
                    cmd[index++] = key[0];
                    i++;
                }
            }
        }
    } while (read_key() != 0);  // Loop until a key is pressed

    // Deallocate memory
    delete[] key;
    delete[] cmd;
    delete[] full_cmd;
}
