#ifndef __NOVANIX_KERNEL_CLEAN_H
#define __NOVANIX_KERNEL_CLEAN_H

#define VGA_ADDRESS 0xB8000
#define VGA_COLUMNS 80
#define VGA_ROWS 25
#define WHITE_ON_BLACK 0x0F

void inline clear_screen() {
    unsigned char* video_memory = (unsigned char*) VGA_ADDRESS;
    for (int i = 0; i < VGA_COLUMNS * VGA_ROWS; i++) {
        video_memory[i * 2] = ' ';               // Blank character
        video_memory[i * 2 + 1] = WHITE_ON_BLACK; // Attribute
    }
}

#endif