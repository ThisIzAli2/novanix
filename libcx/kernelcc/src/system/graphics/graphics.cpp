#include <graphics/graphics.h>


void put_pixel(int x, int y, unsigned char color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    unsigned char* video = (unsigned char*)VGA_ADDRESS;
    video[y * SCREEN_WIDTH + x] = color;
}

void draw_rect(int x, int y, int width, int height, unsigned char color) {
    for (int dy = 0; dy < height; dy++) {
        for (int dx = 0; dx < width; dx++) {
            put_pixel(x + dx, y + dy, color);
        }
    }
}

void clear_screen(unsigned char color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            put_pixel(x, y, color);
        }
    }
}

// Stub for draw_text (replace with actual bitmap/font handling)
void draw_text(int x, int y, const char* text, unsigned char color) {
    // You’ll need a font array like 8x8 font bitmaps to implement this.
    // For now, this can be left as a no-op or used with BIOS interrupt if using real mode.
}
void gui() {
    clear_screen(0); // Black background
    draw_rect(50, 40, 220, 120, 4);   // Red window
    draw_rect(50, 160, 220, 20, 1);   // White taskbar

    draw_text(60, 60, "Welcome to Nova GUI!", 15); // White text

    while (1); // Freeze here to keep GUI showing
}