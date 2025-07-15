/**
 * @author Ali Mirmohammad
 * @file putchar.h
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
#ifndef __NOVANIX_KERNEL_PUTCHAR_H
#define __NOVANIX_KERNEL_PUTCHAR_H

#include <common/types.h>
#include <core/port.h>
#include <system/log.h>
#include <typing.hpp>

#define VGA_ADDRESS 0xB8000
#define SCREEN_WIDTH 80
#define VGA_COMMAND_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5
#define SCREEN_HEIGHT 25

// Current cursor position
static INTEGER cursor_x = 0;
static INTEGER cursor_y = 0;

VOID inline scroll_screen();

// Function to update the hardware cursor
VOID inline update_cursor(INTEGER x, INTEGER y) {
    Novanix::common::uint16_t position = y * SCREEN_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (Novanix::common::uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (Novanix::common::uint8_t)((position >> 8) & 0xFF));
}

// Function to write a character at a specific position on the screen
VOID inline putchar(char c) {
    volatile Novanix::common::uint16_t *vga_buffer = (Novanix::common::uint16_t *)VGA_ADDRESS;

    // Handle special characters
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else {
        // Write the character to the VGA buffer
        vga_buffer[cursor_y * SCREEN_WIDTH + cursor_x] = (Novanix::common::uint16_t)c | (0x07 << 8); // Character with attribute (0x07 = light gray on black)
        cursor_x++;
    }

    // Wrap to the next line if the cursor reaches the end of the screen width
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    // Scroll the screen if the cursor goes beyond the screen height
    if (cursor_y >= SCREEN_HEIGHT) {
        scroll_screen();
        cursor_y = SCREEN_HEIGHT - 1;
    }

    // Update the hardware cursor
    update_cursor(cursor_x, cursor_y);
}

// Function to scroll the screen up by one line
VOID __always_inline scroll_screen() {
    volatile Novanix::common::uint16_t *vga_buffer = (Novanix::common::uint16_t *)VGA_ADDRESS;

    // Copy each line to the line above
    for (INTEGER y = 1; y < SCREEN_HEIGHT; y++) {
        for (INTEGER x = 0; x < SCREEN_WIDTH; x++) {
            vga_buffer[(y - 1) * SCREEN_WIDTH + x] = vga_buffer[y * SCREEN_WIDTH + x];
        }
    }

    // Clear the last line
    for (INTEGER x = 0; x < SCREEN_WIDTH; x++) {
        vga_buffer[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + x] = (Novanix::common::uint16_t)' ' | (0x07 << 8); // Space with attribute
    }
}


uint16_t inline get_cursor_position() {
    uint16_t pos = 0;
    // Tell VGA we want to read the high byte of cursor position
    outb(VGA_COMMAND_PORT, 14);
    pos = inb(VGA_DATA_PORT) << 8;  // high byte
    // Tell VGA we want to read the low byte of cursor position
    outb(VGA_COMMAND_PORT, 15);
    pos |= inb(VGA_DATA_PORT);      // low byte
    return pos;
}



// Function to set cursor position (offset in characters)
void inline set_cursor_position(uint16_t pos) {
    // Send the high byte
    outb(VGA_COMMAND_PORT, 14);
    outb(VGA_DATA_PORT, (pos >> 8) & 0xFF);
    // Send the low byte
    outb(VGA_COMMAND_PORT, 15);
    outb(VGA_DATA_PORT, pos & 0xFF);
}

// Move cursor back by one character
void inline move_cursor_back() {
    uint16_t pos = get_cursor_position();
    if (pos > 0) {
        pos--;
        set_cursor_position(pos);
    }
}
VOID inline clear_last_char() {
    move_cursor_back();
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE, " ", 0);
    move_cursor_back();
}

#endif
