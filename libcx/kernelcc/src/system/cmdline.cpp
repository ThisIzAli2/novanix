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



/**
 * This is the main file for the command line interface (CLI), where all the commands for the operating system are defined here.
 * 
 * Here are some important commands of the system:
 * sudo-su [password] : Write the password to access sudo.
 * shutdown-now : Show down the system instantly.
 * halt : Halt the kernel, if there was a series threat.
 * cal : Show the calendar.
 * time: Show the system time.
 * hawk : The operating system's text editor.
 * cat : Read a file's content.
 * motd: Show the message of the day.
 * set-password : Set the new password. 
 * sudo-reset : Reset the SUDO access.
 * echo : print a word in the terminal.
 * if : Show the information about a file.
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
#include <graphics/graphics.h>
#include <security/sudo.h>
#include <security/lockdown.h>
#include <math/circle.h>
#include <special.h>
#include <security/memaccess.h>
#include <fs/cat.h>
#include <game/gaming.h>
#include <constant.h>
#include <drivers/cpu.h>
#include <random/rand.h>
#include <io/io.h>
#include <fs/filesearch.h>
#include <fs/commands.h>
#include <common/common.hpp>
#include <graphics/graphics.hpp>
#include <fs/physical.h>
#include <fs/fat16.h>
#include <fs/fat32.h>
#include <mmap.h>
#include <fs/hfs/fstruct.h>
#include <fs/fileinfo.h>


char* dirs[MAX_DIRS];

INTEGER counter = 0;
extern fat32_fs_t fs;




    
#define PRINT_PROMPT Novanix::system::printk(Novanix::system::VGA_WHITE, "%s>", 0,current_directory);



INTEGER counter_terminal;

#define str_cmp cmd_cmp




// We do not want to be in the developer mode, which shows all the bugs and logs.
#ifdef DEV
#undef DEV
#endif

#if defined(DEV)
#warning "You are compiling Kernel in developer mode."
#endif
/**
 * Handle the command line in the kernel, does the command control of the CUI.
 */
VOID cmdline() {
    
    char* key = new char[2];  // Single character input
    INTEGER index = 0;
    char* cmd = new char[BUFFER_CONSTANT];  // Command buffer
    INTEGER i = 0;
    char* full_cmd = new char[BUFFER_CONSTANT];  // To hold the full command
    INTEGER j = 0;
    
    // Print the prompt
    printk(VGA_WHITE, "%s>", 0,current_directory);
    // Novanix::system::printk(Novanix::system::VGA_WHITE, stringify(counter_terminal), 0);
    do {
        // Read the key and handle the input
        INTEGER keycode = read_key();  // Store the result of read_key()

        key = handle_keyboard(keycode);  // Get the key pressed
        
        ++counter_terminal;
        
        printk(VGA_WHITE, key, 0);
        // move_cursor_back();
        if (key != nullptr) {
            if (index < 127) {


                // Check if Enter key is pressed
                if (key[0] == '\n') {
                    counter_terminal = 6;
                    // Copy cmd to full_cmd when Enter is pressed
                    for (INTEGER k = 0; k < index; ++k) {
                        full_cmd[k] = cmd[k];
                    }
                    full_cmd[index] = '\0';  // Null-terminate the full_cmd string

                    // Print the full command entered

                    // Compare full_cmd with "help"
                    if (cmd_cmp(full_cmd, "help") == 0) {
                        printk(VGA_WHITE, HELP_MENU,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"shutdown-now") == 0){
                        if (!(have_access)){
                            printk(VGA_RED,"You do not have super user access, try sudo-su [password]",1);
                        }else{
                        shutdown_sys_now();
                        }
                    }
                    ELIF(cmd_cmp(full_cmd,"graph") == 0){
                    draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xFF000000); // opaque black

                    // Draw a red rectangle at position (100, 100), size 200x150
                    draw_rect(100, 100, 200, 150, 0xFFFF0000); // opaque red

                    // Draw a green rectangle inside the red one
                    draw_rect(150, 150, 100, 50, 0xFF00FF00); // opaque green
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"shutdown-delay") == 0){
                        if (!(have_access)){
                            printk(VGA_RED,"You do not have super user access, try sudo-su [password]",1);
                        }else{
                            INTEGER temp_shut_down = 1000000000000000000;
                            while(--temp_shut_down);
                            shutdown_sys_now();
                        }
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"pwd") == 0){
                        fs_manager->printCurrentDir();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"time") == 0){
                        display_clock();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"gui") == 0){
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"net-tcp") == 0){
                        //! Not ready to use yet
                        printk(VGA_RED,"TCP function not ready yet",1);
                        tcp_receive(19216811,19216811,(uint8_t*)3,19);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"clear") == 0 || cmd_cmp(full_cmd,"cls") == 0){
                        clear_screen();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"halt") == 0){
                        if (!have_access){
                            goto again;
                        } else{
                            asm volatile ("hlt");
                        }
                        again:
                            printk(VGA_RED,"You do not have sudo access, try again.",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"net-udp") == 0){
                        //! Not ready to use yet
                        printk(VGA_RED,"UDP function not ready yet",1);
                        udp_receive(19216811,19216811,(uint8_t*)3,19);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"intg") == 0){
                        printk(VGA_WHITE,INTEGRAL_SIGN,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"version") == 0){
                        printk(VGA_WHITE,KERNEL_VERSION,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"tasks-show") == 0){
                        printk(VGA_WHITE,"System related tasks are fully running...",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"gameplay") == 0){
                        printk(VGA_WHITE,LETTER,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"sound") == 0){
                        play_beep(1000); // Play 1kHz tone
                       
                        stop_beep();     // Stop the sound
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"initfile") == 0){
                        Retain file = Retain("new_file.txt", 1024, "This is the content to save.");
                        file = create_file("welcome.txt",2,"Welcome to Novanix!");
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"wifi") == 0){
                        // scan_wifi_mac_addresses();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"cowsay") == 0){
                        printk(VGA_WHITE,"\n",1);
                        printk(VGA_WHITE,"I love Novanix!",1);
                        printk(VGA_WHITE,COW_STRING,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"cal") == 0){
                            printk(VGA_WHITE,"     september 2025\n",1);
                            printk(VGA_WHITE,"Su Mo Tu We Th Fr Sa\n",1);
                            printk(VGA_WHITE,"       1  2  3  4  5\n",1);
                            printk(VGA_WHITE," 6  7  8  9 10 11 12\n",1);
                            printk(VGA_WHITE,"13 14 15 16 17 18 19\n",1);
                            printk(VGA_WHITE,"20 21 22 23 24 25 26\n",1);
                            printk(VGA_WHITE,"27 28 29 30 \n",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"snake") == 0){
                        snake.print_s(keycode);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'i' && full_cmd[1] == 'f'){
                        INTEGER *i_for_if = new INTEGER;
                        INTEGER *counter_if = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT];
                        *counter_if = 0;
                        to_print[0] = '\0';

                        for (*i_for_if = 3;full_cmd[*i_for_if] != '\0';++(*i_for_if)){
                            to_print[*counter_if] = full_cmd[*i_for_if];
                            ++(*counter_if);
                            to_print[*counter_if] = '\0';
                        }
                        get_file_info(to_print);
                        delete i_for_if;
                        delete counter_if;
                        delete[] to_print;

                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (full_cmd[0] == 'i' && full_cmd[1] == 'n' && full_cmd[2] == 'i' && full_cmd[3] == 't' && full_cmd[4] == 'f' && full_cmd[5] == 'i' && full_cmd[6] == 'l' && full_cmd[7] == 'e' ){
                        INTEGER *i_for_file = new INTEGER;
                        INTEGER *counter_for_file = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT];
                        *counter_for_file = 0;

                        to_print[0] = '\0';

                        for (*i_for_file = 9; full_cmd[*i_for_file] != '\0'; ++(*i_for_file)){
                            to_print[*counter_for_file] = full_cmd[*i_for_file];
                            ++(*counter_for_file);
                            to_print[*counter_for_file] = '\0';
                        }
                        create_file(to_print,"");
                        read_file(to_print);
                        delete i_for_file;
                        delete counter_for_file;
                        delete[] to_print;
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"hfs") == 0){
                        hfs_mount();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (full_cmd[0] == 'z' and full_cmd[1] == 'i' and full_cmd[2] == 'p'){
                        INTEGER *i_for_zip = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT];
                        *counter_k = 0;
                        to_print[0] = '\0';

                        for (*i_for_zip = 4;full_cmd[*i_for_zip] != '\0';++(*i_for_zip)){
                            to_print[*counter_k] = full_cmd[*i_for_zip];
                            ++(*counter_k);
                            to_print[*counter_k] = '\0'; 
                        }
                        file_t f = search_file(to_print);
                        // zip_manager.create_zip_file(f);
                        printk(VGA_WHITE,"file compressed: %s",1,f.name);
                        // TODO: Should search for the file name to get the file_t

                    }
                    ELIF(cmd_cmp(full_cmd,"ram") == 0){
                        print_rem_ram();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (full_cmd[0] == 'c' && full_cmd[1] == 'a' && full_cmd[2] == 'w' && full_cmd[3] == 'k'){
                        INTEGER *i_for_hawk = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT];
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

                    ELIF (full_cmd[0] == 't' and full_cmd[1] == 'o' and full_cmd[2] == 'u' and full_cmd[3] == 'c' and full_cmd[4] == 'h'){
                        INTEGER *i_for_file = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_save = new char[CHAR_CONSTANT]; // Allocate memory for the string
                        *counter_k = 0;

                        to_save[0] = '\0';

                        for (*i_for_file = 6; full_cmd[*i_for_file] != '\0'; ++(*i_for_file)){
                            to_save[*counter_k] = full_cmd[*i_for_file];
                            ++(*counter_k);
                            to_save[*counter_k] = '\0';
                        }
                        file_t file = __create_file(to_save,"",String::strlen("")+1,false);
                        files[i_file++].data = file.data;
                        i_file--;

                        delete i_for_file;
                        delete counter_k;
                        delete[] to_save;
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'c' && full_cmd[1] == 'a' && full_cmd[2] == 't'){
                        INTEGER *i_for_cat = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT];
                        *counter_k = 0;
                        to_print[0] = '\0';

                        for (*i_for_cat = 4; full_cmd[*i_for_cat] != '\0';++(*i_for_cat)){
                            to_print[*counter_k] = full_cmd[*i_for_cat];
                            ++(*counter_k);
                            to_print[*counter_k] = '\0';
                        }

                        cat_file(to_print);
                        delete i_for_cat;
                        delete counter_k;
                        delete[] to_print;
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    
                ELIF(full_cmd[0] == 'r' && full_cmd[1] == 'm' && full_cmd[2] == 'd' && full_cmd[3] == 'i' && full_cmd[4] == 'r'){
                        INTEGER *i_for_rm_dir = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT]; // Allocate memory for the string
                        *counter_k = 0;
                        BOOL retVal;

                        // Initialize the to_print buffer to an empty string
                        to_print[0] = '\0';

                        for (*i_for_rm_dir = 6; full_cmd[*i_for_rm_dir] != '\0'; ++(*i_for_rm_dir)) {
                            to_print[*counter_k] = full_cmd[*i_for_rm_dir]; // Add the current character
                            ++(*counter_k);
                            to_print[*counter_k] = '\0'; // Null-terminate the string
                            
                        }

                        retVal = fs_manager->rmdir(to_print);
                        // if (removed){
                        //     printk(VGA_WHITE,"Directory %s removed successfully",1,to_print);
                        // } else{
                        //     printk(VGA_WHITE,"Directory %s does not exist or cannot be removed",1,to_print);
                        // }
                        // Clean up dynamically allocated memory
                        delete i_for_rm_dir;
                        delete counter_k;
                        delete[] to_print;
                    } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'm' && full_cmd[1] == 'k' && full_cmd[2] == 'd' && full_cmd[3] == 'i' && full_cmd[4] == 'r'){
                        INTEGER *i_for_mkdir = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT]; // Allocate memory for the string
                        *counter_k = 0;

                        // Initialize the to_print buffer to an empty string
                        to_print[0] = '\0';

                        for (*i_for_mkdir = 6; full_cmd[*i_for_mkdir] != '\0'; ++(*i_for_mkdir)) {
                            to_print[*counter_k] = full_cmd[*i_for_mkdir]; // Add the current character
                            ++(*counter_k);
                            to_print[*counter_k] = '\0'; // Null-terminate the string
                            
                        }

                        char* dir = fs_manager->mkdir(to_print, dirs, &count);
                        if (dir == nullptr){
                            printk(VGA_COLOR_RED, "Directory already exists",1);
                        }
                        // Clean up dynamically allocated memory
                        delete i_for_mkdir;
                        delete counter_k;
                        delete[] to_print;
                    } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    ELIF(full_cmd[0] == 'h' && full_cmd[1] == 'a' && full_cmd[2] == 'w' && full_cmd[3] == 'k' && full_cmd[4] == '-' && full_cmd[5] == 's'){
                        char to_print[BUFFER_CONSTANT] = {0};
                        bool access_req;
                        INTEGER i_for_hawk = 7;
                        INTEGER counter_k = 0;
                        while (full_cmd[i_for_hawk] != '\0' && counter_k < BUFFER_CONSTANT - 1) {
                            to_print[counter_k++] = full_cmd[i_for_hawk++];
                        }
                        to_print[counter_k] = '\0';
                        if (not IS_NOT_EMPTY_OR_SPACES(to_print)){
                            printk(VGA_WHITE,"File name cannot be empty!",1);
                        } else{
                            // create_file_function(draw_editor(),to_print);
                            char* data = draw_editor();
                            file_t file = __create_file(to_print,data,String::strlen(data)+1,true);
                            files[i_file++].data = file.data;
                            i_file--;
                        }
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'h' && full_cmd[1] == 'a' && full_cmd[2] == 'w' && full_cmd[3] == 'k'){
                        char to_print[BUFFER_CONSTANT] = {0};
                        INTEGER i_for_hawk = 5;
                        INTEGER counter_k = 0;
                        while (full_cmd[i_for_hawk] != '\0' && counter_k < BUFFER_CONSTANT - 1) {
                            to_print[counter_k++] = full_cmd[i_for_hawk++];
                        }
                        to_print[counter_k] = '\0';
                        if (not IS_NOT_EMPTY_OR_SPACES(to_print)){
                            printk(VGA_WHITE,"File name cannot be empty!",1);
                        } else{
                            // create_file_function(draw_editor(),to_print);
                            char* data = draw_editor();
                            file_t file = __create_file(to_print,data,String::strlen(data)+1,false);
                            files[i_file++].data = file.data;
                            i_file--;
                        }
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"time") == 0){
                        display_time();
                        printk(VGA_WHITE,__TIME__,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"phy") == 0){
                        uint8_t sector_data[512] = {0};  // Clear sector (all zeros)
                        sector_data[0] = 'N';            // Just some test data
                        sector_data[1] = 'O';
                        sector_data[2] = 'V';
                        sector_data[3] = 'A';
                        sector_data[4] = 0;              // Null-terminator or just padding
                        uint32_t sector_to_write = 100; // for example, sector #100 on the disk
                        bool success = ata_write_sector(sector_to_write, sector_data);
                        if (success) {
                            printk(VGA_WHITE,"Sector written successfully!",1);
                        } else {
                            printk(VGA_WHITE,"Failed to write sector.",1);
                        }
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"ls") == 0){
                        print_ls_files_in_dir();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"uname") == 0){
                        printk(VGA_WHITE,"Novanix",1);
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"clock") == 0){
                        draw_circle(160, 100, 60, 15);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"motd") == 0){
                        printk(VGA_WHITE,randomMotd(),1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd, "comm-send") == 0 || cmd_cmp(full_cmd, "comm-recv") == 0) {
                        comm_command_handler(full_cmd);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'c' && full_cmd[1] == 'd'){
                        INTEGER *i_for_cd = new INTEGER;
                        INTEGER *counter_k = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT]; // Allocate memory for the string
                        *counter_k = 0;
                        // Initialize the to_print buffer to an empty string
                        to_print[0] = '\0';
                        for (*i_for_cd = 3; full_cmd[*i_for_cd] != '\0';++(*i_for_cd)){
                            to_print[*counter_k] = full_cmd[*i_for_cd];
                            ++(*counter_k);
                            to_print[*counter_k] = '\0';

                        }

                        if ((contains(dir_name,256,to_print) == 0)){
                                printk(VGA_RED, "Directory not found",1);
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
                    ELIF (cmd_cmp(full_cmd,"sudo --help") == 0){
                        printk(VGA_WHITE,SUDO_HELP_MENU,1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"fat") == 0){
                        INTEGER res;
                        res = fat32_mount(partition_lba);

                        #if defined(DEV)
                        printk(VGA_WHITE,"status code:",1);

                        printk(VGA_WHITE,stringify(res),1);
                        #endif
                        if (res == -1){
                            printk(VGA_RED,"Failed to mount FAT",1);
                        } else{
                            printk(VGA_RED,"Failed to mount FAT",1);
                            printk(VGA_WHITE,"FAT 32 mounted on LBA %s",1,partition_lba);
                            printk(VGA_WHITE,"Bytes per sector: %u",1,fs.bytes_per_sector);
                        }
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(full_cmd[0] == 'e' && full_cmd[1] == 'c' && full_cmd[2] == 'h' && full_cmd[3] == 'o'){
                        INTEGER *i_for_echo_cmd = new INTEGER;
                        INTEGER *count = new INTEGER;
                        char* to_print = new char[CHAR_CONSTANT]; 
                        *count = 0;
                        for (*i_for_echo_cmd = 5; full_cmd[*i_for_echo_cmd] != '\0'; ++(*i_for_echo_cmd)) {
                            ++(*count);
                            *to_print = full_cmd[*i_for_echo_cmd];
                            printk(VGA_WHITE,to_print,0);

                        }
                        printk(VGA_WHITE,"\n",0);
                        delete i_for_echo_cmd;
                        delete count;
                        delete[] to_print;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                    ELIF(cmd_cmp(full_cmd,"heart") == 0){
                        printk(VGA_WHITE,"\x03\n",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"chess") == 0){
                        printk(VGA_WHITE,"\xE2\x99\x94\n",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"pci") == 0){
                        scan_pci_devices();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"cpu-vendor") == 0){
                        print_cpu_info();
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"firewall") == 0){
                        firewall_append(0xC0A80101);
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"firewall-check") == 0){
                        
                            printk(VGA_WHITE,stringify(0xC0A80101),1);
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

                        }



                        password_saved[n++] = '\0';
                        printk(VGA_WHITE,"Your entered password is:",0);
                        printk(VGA_WHITE,password_saved,1);
                        // user_password = password_saved;


                        if (Novanix::common::String::strlen(password_saved) < USER_NOVANIX || !have_access){
                            // user_password = DEFAULT_PASSWORD;

                            if (!have_access){
                                printk(VGA_COLOR_RED,"You do not have sudo access!",1);
                            } ELIF (Novanix::common::String::strlen(password_saved) < USER_NOVANIX){
                                printk(VGA_RED,"Password is too short, 8 char at least",1);
                            } else{
                                printk(VGA_RED,"Unkown error occurred!",1);
                            }
                            
                        } else {
                            printk(VGA_GREEN,"Password saved successfully",1);
                            String::strcpy(user_password,password_saved);
                        }
                        delete i_pass;
                        delete count_on;
                        
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF (cmd_cmp(full_cmd,"shutdown") == 0){
                        printk(VGA_WHITE,"Use shutdown-[option]",1);
                    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ELIF(cmd_cmp(full_cmd,"sudo-reset") == 0){
                        have_access = false;
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
                        if (cmd_cmp(user_password, passwrd) == 0) {
                            printk(Novanix::system::VGA_WHITE, "SUDO access Granted!", 1);
                            have_access = true;
                        } else {

                            if (counts_failed_sudo < MAX_USER_TRIES){
                                goto fail;
                            } else{
                                lockdown_reason = ROOT_ACCESS_FAILED;
                                reset_super_access();
                                put_system_lockdown(lockdown_reason);
                                counts_failed_sudo = 0;
                            }
                            fail:
                            counts_failed_sudo++;
                            printk(VGA_WHITE, "Wrong password!", 1);
                            if (counts_failed_sudo > 1)
                                printk(VGA_WHITE, "Kernel will go into lockdown if you try to brute force the sudo access.", 1);
                            
                        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    } else {
                        if (IS_NOT_EMPTY_OR_SPACES(full_cmd)){
                        printk(VGA_WHITE,"Command not found",1);
                        } else{
                            ;
                        }
                    }
                    printk(VGA_WHITE,"%s>", 0,current_directory);

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
                printk(VGA_RED,"\nThe entered prompt is too long.\n",0);
                Novanix::common::MemoryOperations::memset(full_cmd,0,sizeof(full_cmd));
                printk(VGA_RED,"\n",0);
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