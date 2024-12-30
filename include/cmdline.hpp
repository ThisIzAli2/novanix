#pragma once

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


#define VGA_WHITE VGA_COLOR_WHITE
    
#define PRINT_PROMPT Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, ">", 0);



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
    INTEGER index = 0;
    char* cmd = new char[BUFFER_CONSTANT];  // Command buffer
    INTEGER i = 0;
    char* full_cmd = new char[BUFFER_CONSTANT];  // To hold the full command
    INTEGER j = 0;
    
    // Print the prompt
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, ">", 0);

    do {
        // Read the key and handle the input
        // read_key();
        INTEGER keycode = read_key();  // Store the result of read_key()

        key = handle_keyboard(keycode);  // Get the key pressed
        
        
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, key, 0);

        if (key != nullptr) {
            if (index < 127) {

                
                
                if (keycode == 142 || keycode == 14){
                    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "\b \b", 0);  // Move cursor back and clear the character
                    if (index > 0) {

                        // index--;  // Decrement index to remove the last character from the buffer
                    // cmd[--index] = '\0';  // Null-terminate the string
                    // Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "\b \b", 0);  // Move cursor back and clear the character

                }
                }

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
                    ELIF (cmd_cmp(full_cmd,"shutdown-now") == 0){
                        if (!(have_access)){
                            Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"You do not have super user access, try sudo-su [password]",1);
                        }else{
                        shutdown_sys_now();
                        }
                    }
                    ELIF (cmd_cmp(full_cmd,"shutdown-delay") == 0){
                        if (!(have_access)){
                            Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"You do not have super user access, try sudo-su [password]",1);
                        }else{
                            int temp_shut_down = 1000000000000000000;
                            while(--temp_shut_down);
                            shutdown_sys_now();
                        }
                    }
                    ELIF(cmd_cmp(full_cmd,"pwd") == 0){
                        fs_manager->printCurrentDir();
                    }
                    ELIF(full_cmd[0] == 'e' && full_cmd[1] == 'c' && full_cmd[2] == 'h' && full_cmd[3] == 'o'){
                        INTEGER *i_for_echo_cmd = new INTEGER;
                        INTEGER *count = new INTEGER;
                        char* to_print = new char[1024]; 
                        *count = 0;
                        for (*i_for_echo_cmd = 5; full_cmd[*i_for_echo_cmd] != '\0'; ++(*i_for_echo_cmd)) {
                            ++(*count);
                            *to_print = full_cmd[*i_for_echo_cmd];
                            Novanix::system::printk(VGA_COLOR_WHITE,to_print,0);

                        }
                        Novanix::system::printk(VGA_COLOR_WHITE,"\n",0);
                        delete i_for_echo_cmd;
                        delete count;
                        delete[] to_print;
                    }

                    ELIF(full_cmd[0] == 's' && full_cmd[1] == 'e' && full_cmd[2] == 't' && full_cmd[3] == '-' && full_cmd[4] == 'p' && full_cmd[5] == 'a' && full_cmd[6] == 's' && full_cmd[7] == 's' && full_cmd[8] == 'w' && full_cmd[9] == 'o' && full_cmd[10] == 'r' && full_cmd[11] == 'd'){
                        INTEGER *i_pass = new INTEGER;
                        INTEGER *count_on = new INTEGER;
                        char password_saved[50] = {0};
                        INTEGER n = 0;
                        for (int i_pass = 13; full_cmd[i_pass] != '\0' && n < sizeof(password_saved) - 1; ++i_pass) {
                            password_saved[n++] = full_cmd[i_pass];
                            ++(*count_on);

                        }
                        password_saved[n++] = '\0';
                        Novanix::system::printk(VGA_WHITE,"Your password is:",0);
                        Novanix::system::printk(VGA_WHITE,password_saved,1);


                        delete i_pass;
                        delete count_on;



                    }
                    ELIF (cmd_cmp(full_cmd,"shutdown") == 0){
                        Novanix::system::printk(VGA_WHITE,"Use shutdown-[option]",1);
                    }
                    ELIF (full_cmd[0] == 's' and full_cmd[1] == 'u' and full_cmd[2] == 'd' and full_cmd[3] == 'o' and full_cmd[4] == '-' and full_cmd[5] == 's' and full_cmd[6] == 'u'){
                        char enter_password[PASSWORD_BUFFER_SIZE];
                        INTEGER counter = 0;
                        char passwrd[50] = {0}; // Initialize to zero
                        INTEGER n = 0;

                        // Extract password from full_cmd starting at index 8
                        for (INTEGER x = 8; full_cmd[x] != '\0'; ++x) {
                            passwrd[n++] = full_cmd[x];
                            counter++;
                        }
                        passwrd[n] = '\0'; // Null-terminate the extracted password

                        // Simulate password entry and comparison
                        // Assume `enter_password` is filled with user input from some mechanism
                        // Replace the following line with actual input logic
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, passwrd, 1);

                        if (cmd_cmp(user_password, passwrd) == 0) {
                            Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "SUDO access Granted!", 1);
                            have_access = true;
                        } else {
                            Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "Wrong password", 1);
                        }
                    }
                    ELIF (cmd_cmp(full_cmd, "") == 0){
                    
                    }  else {
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Entered command does not exists",1);
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
            } else {
                Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"\nThe entered string is too long, cannot be handled by the buffer.\n",0);
                Novanix::common::MemoryOperations::memset(full_cmd,0,sizeof(full_cmd));
                Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"\n",0);
                PRINT_PROMPT
                index = 0;
                // free the buffer 
            }
        }
    } while (read_key() != 0);  // Loop until a key is pressed

    // Deallocate memory
    delete[] key;
    delete[] cmd;
    delete[] full_cmd;
}
