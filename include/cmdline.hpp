#pragma once

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>

inline void cmdline(){
    do{
        read_key();
        // printk(VGA_COLOR_WHITE,stringify(read_key()),1); // 4 test
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,">/",0);
        Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,handle_keyboard(read_key()),0);

    }while(read_key() != 0);
}