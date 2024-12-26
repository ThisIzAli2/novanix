#pragma once

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>

inline void cmdline(){
    const char* cmd;
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">",0);
    do{
        if (cmd == "\n"){
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">",0);

        }

        read_key();
        // printk(Novanix::system::VGA_COLOR_WHITE,stringify(read_key()),1); // 4 test
        cmd = handle_keyboard(read_key());
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,cmd,0);
    }while(read_key() != 0);
}