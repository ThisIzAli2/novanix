#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_ADDRESS 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#ifdef __cplusplus
extern "C" {
#endif

// Set a pixel on screen at (x, y) to a color
void put_pixel(int x, int y, unsigned char color);

// Draw a filled rectangle
void draw_rect(int x, int y, int width, int height, unsigned char color);

// Clear the screen with a color

// Draw basic text at (x, y). You must implement a font or use BIOS font
void draw_text(int x, int y, const char* text, unsigned char color);

void gui();


#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_H