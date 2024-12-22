/**
 * @file window.h
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/


/**
 * @abstraction:
 *  - Kernel window header file.
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <types.h>

#define WINDOW_EDGE_COLOR               0xA3A29E
#define WINDOW_BACKGROUND_COLOR         0xE8E6E3
#define TEXT_AREA_COLOR                 0xFFFFF6

#define TYPE_TEXT_AREA                  1

typedef struct components {
    uint32_t *component;
    struct components *next;
} components_list_t;

typedef struct window {
    char title[256];
    int x;
    int y;
    int h;
    int w;
    components_list_t *components;
} window_t;

typedef struct wlist {
    window_t *window;
    struct wlist *next;
} window_list_t;

typedef struct text_area {
    uint32_t type;
    int x;
    int y;
    int h;
    int w;
    int cursorx;
    int cursory;
    char content[1024];
} text_area_t;

void windows_list_init();
window_t *window_create(char *title, int x, int y, int w, int h);
void add_component(window_t *window, void *component);
void paint_windows();
void paint_window(window_t *window);
text_area_t *create_text_area(int x, int y, int w, int h);
void text_area_set_text(text_area_t *text_area, char *text);
void text_area_append(text_area_t *text_area, char *text);
void draw_text_area(window_t *window, text_area_t *text_area);

#endif /*WINDOW_H*/