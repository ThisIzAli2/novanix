#ifndef __GRAPHICS_KERNEL_HPP
#define __GRAPHICS_KERNEL_HPP


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define BYTES_PER_PIXEL 4

// Assume this pointer points to your framebuffer memory
volatile unsigned char* framebuffer = (volatile unsigned char*)0x000B8000; // example address; replace with real one

// Function to put a pixel at (x, y) with a 32-bit color (0xAARRGGBB or 0xRRGGBBAA depending on format)
void inline put_pixel(int x, int y, unsigned int color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

    // Calculate pixel position in framebuffer memory
    unsigned int offset = (y * SCREEN_WIDTH + x) * BYTES_PER_PIXEL;

    // Write color bytes - assuming little-endian and format: 0xAARRGGBB in memory as BB GG RR AA
    framebuffer[offset + 0] = (color >> 0) & 0xFF;    // Blue
    framebuffer[offset + 1] = (color >> 8) & 0xFF;    // Green
    framebuffer[offset + 2] = (color >> 16) & 0xFF;   // Red
    framebuffer[offset + 3] = (color >> 24) & 0xFF;   // Alpha (or unused)
}

// Draw a filled rectangle from (x, y) with width w and height h in given color
void inline draw_rect(int x, int y, int w, int h, unsigned int color) {
    for (int iy = 0; iy < h; iy++) {
        for (int ix = 0; ix < w; ix++) {
            put_pixel(x + ix, y + iy, color);
        }
    }
}


#endif /*__GRAPHICS_KERNEL_HPP*/