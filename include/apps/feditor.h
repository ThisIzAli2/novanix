#ifndef __NOVANIX_FEDITOR_H
#define __NOVANIX_FEDITOR_H


#define MAX_LINES 100
#define MAX_LINE_LEN 128

char text_buffer[MAX_LINES][MAX_LINE_LEN];
int num_lines = 0;

int cursor_x = 0;
int cursor_y = 0;


#endif /*__NOVANIX_FEDITOR_H*/