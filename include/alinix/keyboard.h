/**
 * @author Ali Mirmohammad
 * @file keyboard.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Keyboard utils are implemented here.
*/
#ifndef __ALINIX_KERNEL_KEYBOARD_H
#define __ALINIX_KERNEL_KEYBOARD_H
#include <alinix/types.h>

/**
 * @brief Kernel keyboard status.
 * @note Should be used within the keyboard tasks.
*/
struct InternalKeyboardStatus{
    bool LeftShift;
    bool RightShift;

    bool Alt;
    bool AltGr;
    
    bool LeftControl;
    bool RightControl;
};

struct KeyboardStatus
{
    bool CapsLock;
    bool NumLock;
};

enum KeyboardType
{
    PS2,
    USB
};

typedef struct {
    enum KeyboardType type;
    struct InternalKeyboardStatus status;
} Keyboard;

bool ContainsKey(uint8_t key, uint8_t* packet, int* pos);
void UpdateLEDS();

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_COMMAND_PORT   0x64

#define KBD_CR_NL       0x0a
#define KBD_BACKSPACE   0x08
#define KBD_TABULATION  0x09

// See scancodes at wiki.osdev.org/PS2/2_Keyboard
#define KEY_ESCAPE      0x01
#define KEY_BACKSPACE   0x0e
#define KEY_TAB         0x0f
#define KEY_ENTER       0x1c
#define KEY_LEFT_CTRL   0x1d
#define KEY_LEFT_SHIFT  0x2a
#define KEY_RIGHT_SHIFT 0x36
#define KEY_LEFT_ALT    0x38
#define KEY_SPACE       0x39
#define KEY_CAPS_LOCK   0x3a
#define KEY_F1          0x3b
#define KEY_F2          0x3c
#define KEY_F3          0x3d
#define KEY_F4          0x3e
#define KEY_F5          0x3f
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_NUMBER_LOCK 0x45
#define KEY_SCROLL_LOCK 0x46
#define KEY_F11         0x57
#define KEY_F12         0x58
#define KEY_UP          0x48
#define KEY_DOWN        0x50
#define KEY_LEFT        0x4b
#define KEY_RIGHT       0x4d
#define KEY_PAGE_UP	0x49
#define KEY_PAGE_DOWN	0x51

#define CAPS_LOCK 0x3A


#define BACKSPACE 14
#define ESCAPE 1
#define PAGEUP 73
#define PAGEDOWN 81


/*Keyboard key scancode defined here (ascii)*/
#define Q_KEY 0x18
#define W_KEY 0x19
#define E_KEY 0x1A
#define R_KEY 0x1B
#define T_KEY 0x1C
#define Y_KEY 0x1D
#define U_KEY 0x1E
#define I_KEY 0x1F
#define O_KEY 0x20
#define P_KEY 0x21
#define A_KEY 0x26
#define S_KEY 0x27
#define D_KEY 0x20
#define F_KEY 0x29
#define G_KEY 0x2A
#define H_KEY 0x2B
#define J_KEY 0x2C
#define K_KEY 0X2D
#define L_KEY 0x2E
#define Z_KEY 0x35
#define X_KEY 0x36
#define C_KEY 0x37
#define V_KEY 0x38
#define B_KEY 0x39
#define N_KEY 0x3B
#define M_KEY 0x3C


#define SCROLL_UP     1
#define SCROLL_DOWN   2

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_STATUS_PORT    0x64
#define KEYBOARD_COMMAND_PORT   0x64

/* 
    scan codes in alphabetical order for QWERTY keyboard
    see https://wiki.osdev.org/PS/2_Keyboard
*/
#define SCAN_CODE_KEY_ESC         0x01
#define SCAN_CODE_KEY_1         0x02
#define SCAN_CODE_KEY_2         0x03
#define SCAN_CODE_KEY_3         0x04
#define SCAN_CODE_KEY_4         0x05
#define SCAN_CODE_KEY_5         0x06
#define SCAN_CODE_KEY_6         0x07
#define SCAN_CODE_KEY_7         0x08
#define SCAN_CODE_KEY_8         0x09
#define SCAN_CODE_KEY_9         0x0A
#define SCAN_CODE_KEY_0         0x0B
#define SCAN_CODE_KEY_MINUS         0x0C
#define SCAN_CODE_KEY_EQUAL         0x0D
#define SCAN_CODE_KEY_BACKSPACE         0x0E
#define SCAN_CODE_KEY_TAB         0x0F
#define SCAN_CODE_KEY_Q         0x10
#define SCAN_CODE_KEY_W         0x11
#define SCAN_CODE_KEY_E         0x12
#define SCAN_CODE_KEY_R         0x13
#define SCAN_CODE_KEY_T         0x14
#define SCAN_CODE_KEY_Y         0x15
#define SCAN_CODE_KEY_U         0x16
#define SCAN_CODE_KEY_I         0x17
#define SCAN_CODE_KEY_O         0x18
#define SCAN_CODE_KEY_P         0x19
#define SCAN_CODE_KEY_SQUARE_OPEN_BRACKET         0x1A
#define SCAN_CODE_KEY_SQUARE_CLOSE_BRACKET         0x1B
#define SCAN_CODE_KEY_ENTER         0x1C
#define SCAN_CODE_KEY_LEFT_CTRL         0x1D
#define SCAN_CODE_KEY_A         0x1E
#define SCAN_CODE_KEY_S         0x1F
#define SCAN_CODE_KEY_D         0x20
#define SCAN_CODE_KEY_F         0x21
#define SCAN_CODE_KEY_G         0x22
#define SCAN_CODE_KEY_H         0x23
#define SCAN_CODE_KEY_J         0x24
#define SCAN_CODE_KEY_K         0x25
#define SCAN_CODE_KEY_L         0x26
#define SCAN_CODE_KEY_SEMICOLON         0x27
#define SCAN_CODE_KEY_SINGLE_QUOTE         0x28
#define SCAN_CODE_KEY_ACUTE         0x29
#define SCAN_CODE_KEY_LEFT_SHIFT         0x2A
#define SCAN_CODE_KEY_BACKSLASH         0x2B
#define SCAN_CODE_KEY_Z         0x2C
#define SCAN_CODE_KEY_X         0x2D
#define SCAN_CODE_KEY_C         0x2E
#define SCAN_CODE_KEY_V         0x2F
#define SCAN_CODE_KEY_B         0x30
#define SCAN_CODE_KEY_N         0x31
#define SCAN_CODE_KEY_M         0x32
#define SCAN_CODE_KEY_COMMA         0x33
#define SCAN_CODE_KEY_DOT         0x34
#define SCAN_CODE_KEY_FORESLHASH         0x35
#define SCAN_CODE_KEY_RIGHT_SHIFT         0x36
#define SCAN_CODE_KEY_ASTERISK         0x37
#define SCAN_CODE_KEY_ALT         0x38
#define SCAN_CODE_KEY_SPACE         0x39
#define SCAN_CODE_KEY_CAPS_LOCK         0x3A
#define SCAN_CODE_KEY_F1         0x3B
#define SCAN_CODE_KEY_F2         0x3C
#define SCAN_CODE_KEY_F3         0x3D
#define SCAN_CODE_KEY_F4         0x3E
#define SCAN_CODE_KEY_F5         0x3F
#define SCAN_CODE_KEY_F6         0x40
#define SCAN_CODE_KEY_F7         0x41
#define SCAN_CODE_KEY_F8         0x42
#define SCAN_CODE_KEY_F9         0x43
#define SCAN_CODE_KEY_F10         0x44
#define SCAN_CODE_KEY_NUM_LOCK         0x45
#define SCAN_CODE_KEY_SCROLL_LOCK         0x46
#define SCAN_CODE_KEY_HOME         0x47
#define SCAN_CODE_KEY_UP         0x48
#define SCAN_CODE_KEY_PAGE_UP         0x49
#define SCAN_CODE_KEY_KEYPAD_MINUS         0x4A
#define SCAN_CODE_KEY_LEFT         0x4B
#define SCAN_CODE_KEY_KEYPAD_5         0x4C
#define SCAN_CODE_KEY_RIGHT         0x4D
#define SCAN_CODE_KEY_KEYPAD_PLUS         0x4E
#define SCAN_CODE_KEY_END         0x4F
#define SCAN_CODE_KEY_DOWN         0x50
#define SCAN_CODE_KEY_PAGE_DOWN         0x51
#define SCAN_CODE_KEY_INSERT         0x52
#define SCAN_CODE_KEY_DELETE         0x53
#define SCAN_CODE_KEY_F11         0x57
#define SCAN_CODE_KEY_F12         0x58

#define BACKSPACE 14
#define ESCAPE 1
#define PAGEUP 73
#define PAGEDOWN 81


void keyboard_init();

// a blocking character read
char kb_getchar();
char kb_get_scancode();

extern void clear_screen();
extern void init_keyboard();
extern void wait_for_key_press();
extern void read_scan_code();
extern void print_scan_code();

#endif /*__ALINIX_KERNEL_KEYBOARD_H*/