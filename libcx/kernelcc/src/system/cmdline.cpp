/**
 * @author Ali Mirmohammad
 * @file cmdline.cpp
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
#include <software/edit.h>
#include <cmdline.hpp>
#include <network/firewall/blocklist.h>
#include <command/fun.h>
#include <network/wifi/wifi.h>
#include <network/wifi/conf.h>
#include <version.hpp>
#include <network/drivers/e1000_driver.h>
#include <software/fcreate.h>
#include <software/faccess.h>


char* dirs[MAX_DIRS];

INTEGER counter = 0;


    
#define PRINT_PROMPT Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "%s>", 0,current_directory);






#define str_cmp cmd_cmp


/**
 * @brief 
 * An unused function that handles the other cases of the command line interface
 */
__always_inline INTEGER handle(const char* str){
    if (cmd_cmp(str,"get")){
        return 0001;
    } ELIF (cmd_cmp(str,"games") == 0){
        return 0002;
    } else {
        return -1;
    }

}
#ifdef DEV
#undef DEV
#endif
/**
 * Handle the command line in the kernel, does the command control of the CUI
 */
VOID cmdline() {
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
        
        //! Correct Here
        if (key == "-1"){
            continue;
        }
        
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, key, 0);

        if (key != nullptr) {
            if (index < 127) {

                // This might vary
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
                    for (INTEGER k = 0; k < index; ++k) {
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
                            INTEGER temp_shut_down = 1000000000000000000;
                            while(--temp_shut_down);
                            shutdown_sys_now();
                        }
                    }
                    ELIF(cmd_cmp(full_cmd,"pwd") == 0){
                        fs_manager->printCurrentDir();
                    }
                    ELIF (cmd_cmp(full_cmd,"time") == 0){
                        display_clock();
                    }
                    ELIF (cmd_cmp(full_cmd,"net-tcp") == 0){
                        //! Not ready to use yet
                        Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"TCP function not ready yet",1);
                        tcp_receive(19216811,19216811,(uint8_t*)3,19);
                    }
                    ELIF (cmd_cmp(full_cmd,"clear") == 0){
                        clear_screen();
                    }
                    ELIF (cmd_cmp(full_cmd,"halt") == 0){
                        if (!have_access){
                            goto again;
                        } else{
                            asm volatile ("hlt");
                        }
                        again:
                            Novanix::system::printk(VGA_COLOR_RED,"You do not have sudo access, try again.",1);
                    }
                    ELIF (cmd_cmp(full_cmd,"net-udp") == 0){
                        //! Not ready to use yet
                        Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"UDP function not ready yet",1);
                        udp_receive(19216811,19216811,(uint8_t*)3,19);
                    }
                    ELIF(cmd_cmp(full_cmd,"version") == 0){
                        printk(VGA_WHITE,KERNEL_VERSION,1);
                    }
                    ELIF (cmd_cmp(full_cmd,"tasks-show") == 0){
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"System related tasks are fully running...",1);
                    }
                    ELIF (cmd_cmp(full_cmd,"gameplay") == 0){
                        Novanix::system::printk(VGA_COLOR_WHITE,LETTER,1);
                    }
                    ELIF (cmd_cmp(full_cmd,"sound") == 0){
                        play_beep(1000); // Play 1kHz tone
                       
                        stop_beep();     // Stop the sound
                    }
                    ELIF(cmd_cmp(full_cmd,"initfile") == 0){
                        Retain file = Retain("new_file.txt", 1024, "This is the content to save.");
                        file = create_file("welcome.txt",2,"Welcome to Novanix!");
                    }
                    ELIF(cmd_cmp(full_cmd,"wifi") == 0){
                        // scan_wifi_mac_addresses();
                    }

                    ELIF (cmd_cmp(full_cmd,"cowsay") == 0){
                        Novanix::system::printk(VGA_COLOR_WHITE,"\n",1);
                        Novanix::system::printk(VGA_COLOR_WHITE,"I love Nova!",1);
                        Novanix::system::printk(VGA_COLOR_WHITE,COW_STRING,1);
                    }
                    ELIF (cmd_cmp(full_cmd,"cal") == 0){
                            printk(VGA_COLOR_WHITE,"     July 2025\n",1);
                            printk(VGA_COLOR_WHITE,"Su Mo Tu We Th Fr Sa\n",1);
                            printk(VGA_COLOR_WHITE,"       1  2  3  4  5\n",1);
                            printk(VGA_COLOR_WHITE," 6  7  8  9 10 11 12\n",1);
                            printk(VGA_COLOR_WHITE,"13 14 15 16 17 18 19\n",1);
                            printk(VGA_COLOR_WHITE,"20 21 22 23 24 25 26\n",1);
                            printk(VGA_COLOR_WHITE,"27 28 29 30 31\n",1);
                    }

                    ELIF (full_cmd[0] == 'i' && full_cmd[1] == 'n' && full_cmd[2] == 'i' && full_cmd[3] == 't' && full_cmd[4] == 'f' && full_cmd[5] == 'i' && full_cmd[6] == 'l' && full_cmd[7] == 'e' ){
                        INTEGER *i_for_file = new INTEGER;
                        INTEGER *counter_for_file = new INTEGER;
                        char* to_print = new char[1024];
                        *counter_for_file = 0;

                        to_print[0] = '\0';

                        for (*i_for_file = 9; full_cmd[*i_for_file] != '\0'; ++(*i_for_file)){
                            to_print[*counter_for_file] = full_cmd[*i_for_file];
                            ++(*counter_for_file);
                            to_print[*counter_for_file] = '\0';
                        }
                        create_file(to_print,"");
                        read_file(to_print);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (full_cmd[0] == 'c' && full_cmd[1] == 'a' && full_cmd[2] == 'w' && full_cmd[3] == 'k'){
                        INTEGER *i_for_hawk = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[1024];
                        *counter_k = 0;
                        to_print[0] = '\0';

                        for (*i_for_hawk = 5;full_cmd[*i_for_hawk] != '\0'; ++(*i_for_hawk)){
                            to_print[*counter_k] = full_cmd[*i_for_hawk];
                            ++(*counter_k);
                            to_print[*counter_k] = '\0'; 
                        }
                        read_file(to_print);

                        end:
                        delete[] i_for_hawk;
                        delete[] counter_k;
                        delete[] to_print;
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'm' && full_cmd[1] == 'k' && full_cmd[2] == 'd' && full_cmd[3] == 'i' && full_cmd[4] == 'r'){
                        INTEGER *i_for_mkdir = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[1024]; // Allocate memory for the string
                        *counter_k = 0;

                        // Initialize the to_print buffer to an empty string
                        to_print[0] = '\0';

                        for (*i_for_mkdir = 6; full_cmd[*i_for_mkdir] != '\0'; ++(*i_for_mkdir)) {
                            to_print[*counter_k] = full_cmd[*i_for_mkdir]; // Add the current character
                            ++(*counter_k);
                            to_print[*counter_k] = '\0'; // Null-terminate the string
                            
                        }

                        // Novanix::system::printk(VGA_COLOR_WHITE, "\n", 0);
                        // Novanix::system::printk(VGA_COLOR_WHITE, to_print, 0);
                        char* dir = fs_manager->mkdir(to_print, dirs, &count);
                        if (dir == nullptr){
                            Novanix::system::printk(VGA_COLOR_RED, "Directory already exists",1);
                        }
                        // Clean up dynamically allocated memory
                        delete i_for_mkdir;
                        delete counter_k;
                        delete[] to_print;
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"time") == 0){
                        display_time();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"hawk") == 0){
                        create_file_function(draw_editor());
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"uname") == 0){
                        Novanix::system::printk(VGA_COLOR_WHITE,"NovaOs",1);
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"motd") == 0){
                        Novanix::system::printk(VGA_COLOR_WHITE,MESSAGE_OF_THE_DAY,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd, "comm-send") == 0 || cmd_cmp(full_cmd, "comm-recv") == 0) {
                        comm_command_handler(full_cmd);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'c' && full_cmd[1] == 'd'){
                        INTEGER *i_for_cd = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[1024]; // Allocate memory for the string
                        *counter_k = 0;
                        // Initialize the to_print buffer to an empty string
                        to_print[0] = '\0';
                        for (*i_for_cd = 3; full_cmd[*i_for_cd] != '\0';++(*i_for_cd)){
                            to_print[*counter_k] = full_cmd[*i_for_cd];
                            ++(*counter_k);
                            to_print[*counter_k] = '\0';

                        }

                        if ((contains(dir_name,256,to_print) == 0)){
                                Novanix::system::printk(VGA_COLOR_RED, "Directory not found",1);
                                current_directory = "/home";
                            }else {
                                current_directory = to_print;
                            }
                        

                        
                        // Clean up dynamically allocated memory
                        delete i_for_cd;
                        delete counter_k;
                        delete[] to_print;


                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                    ELIF(cmd_cmp(full_cmd,"heart") == 0){
                        Novanix::system::printk(VGA_WHITE,"\x03\n",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"chess") == 0){
                        Novanix::system::printk(VGA_WHITE,"\xE2\x99\x94\n",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"pci") == 0){
                        scan_pci_devices();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"firewall") == 0){
                        firewall_append(0xC0A80101);
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"firewall-check") == 0){
                        
                            Novanix::system::printk(VGA_COLOR_WHITE,stringify(0xC0A80101),1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 's' && full_cmd[1] == 'e' && full_cmd[2] == 't' && full_cmd[3] == '-' && full_cmd[4] == 'p' && full_cmd[5] == 'a' && full_cmd[6] == 's' && full_cmd[7] == 's' && full_cmd[8] == 'w' && full_cmd[9] == 'o' && full_cmd[10] == 'r' && full_cmd[11] == 'd'){
                        INTEGER *i_pass = new INTEGER;
                        INTEGER *count_on = new INTEGER;
                        char password_saved[50] = {0};
                        BOOL failed = false;
                        INTEGER n = 0;
                        for (INTEGER i_pass = 13; full_cmd[i_pass] != '\0' && n < sizeof(password_saved) - 1; ++i_pass) {
                            password_saved[n++] = full_cmd[i_pass];
                            ++(*count_on);
                            // if (Novanix::common::String::strlen(password_saved) < USER_NOVANIX){
                            //     Novanix::system::printk(VGA_COLOR_WHITE,"Password is too short, should be greater than 8 characters",1);
                            //     Novanix::system::printk(VGA_COLOR_WHITE,password_saved,1);
                            //     user_password = DEFAULT_PASSWORD;
                            //     failed = true;
                            // }

                        }


                        Novanix::system::printk(VGA_COLOR_WHITE,stringify(Novanix::common::String::strlen(password_saved)),1);

                        // Novanix::system::printk(VGA_COLOR_WHITE,stringify(Novanix::common::String::strlen(password_saved)),1);
                        // Novanix::system::printk(VGA_COLOR_WHITE,stringify(sizeof(password_saved)),1);
                        password_saved[n++] = '\0';
                        Novanix::system::printk(VGA_WHITE,"Your password is:",0);
                        Novanix::system::printk(VGA_WHITE,password_saved,1);
                        user_password = password_saved;

                        delete i_pass;
                        delete count_on;
                        if (Novanix::common::String::strlen(password_saved) < USER_NOVANIX){
                            user_password = DEFAULT_PASSWORD;
                            Novanix::system::printk(VGA_WHITE,"Password is too short, 8 char at least",1);
                            
                        } else {
                            Novanix::system::printk(VGA_COLOR_WHITE,"Password saved successfully",1);
                        }
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"shutdown") == 0){
                        Novanix::system::printk(VGA_WHITE,"Use shutdown-[option]",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"ethernet") == 0){
                        e1000_init();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                        // Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, passwrd, 1);

                        if (cmd_cmp(user_password, passwrd) == 0) {
                            Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "SUDO access Granted!", 1);
                            have_access = true;
                        } else {
                            Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, "Wrong password", 1);
                        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                    ELIF (cmd_cmp(full_cmd, "Welcome to Nova!") == 0){
                    
                    }  else {
                        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Command not found",1);
                    }
                    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"%s>", 0,current_directory);

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
                // free the buffer 
                Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"\nThe entered prompt is too long.\n",0);
                Novanix::common::MemoryOperations::memset(full_cmd,0,sizeof(full_cmd));
                Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"\n",0);
                PRINT_PROMPT
                index = 0;
            }
        }
    } while (read_key() != 0);  // Loop until a key is pressed

    // Deallocate memory
    delete[] key;
    delete[] cmd;
    delete[] full_cmd;
}