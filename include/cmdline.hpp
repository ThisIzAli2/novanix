#pragma once

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>


int inline cmd_cmp(const char* str1, const char* str2) {
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

inline void cmdline(){
    char* key = new char[2];
    int index = 0;
    char *cmd = new char[128];
    int i = 0;
    char* full_cmd = new char[128];
    int j = 0;
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">",0);
    do{
        if (key == "\n"){
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">",0);

        }
        read_key();
        // printk(Novanix::system::VGA_COLOR_WHITE,stringify(read_key()),1); // 4 test
        key = handle_keyboard(read_key());
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,key,0);
        if (key !=0){
             if (index < 127){
                if (cmd_cmp(key,"\n") == 0)
                Novanix::common::MemoryOperations::memcpy(full_cmd,cmd,0);                    

                cmd[index++] = key[0];
                i++;
            Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,full_cmd,0);
            if (cmd_cmp(full_cmd,"help") == 0){
                Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Help Menu",1);
            }
            Novanix::common::MemoryOperations::memset(full_cmd,0,128);
            i = 0;
             }
        }
    }while(read_key() != 0);
}