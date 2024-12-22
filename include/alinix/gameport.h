/**
 * @author Ali Mirmohammad
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
 * @file gameport.h
 * @abstract:
 *  - Game port driver for the kernel implementation.
*/
#ifndef __ALINIX_KERNEL_GAME_PORT_H
#define __ALINIX_KERNEL_GAME_PORT_H

#include <alinix/types.h>


/**
 * @ref https://github.com/torvalds/linux/blob/master/include/linux/gameport.h#L16
 * @ref https://wiki.osdev.org/Game_port
*/

// Joy stick code goes here

/* Joystick 200h - 201h. */
#define JOYSTICK_PORT 0x201
#define GARBAGE_DATA       0xAA55
#define MAX_TIME_ATTEMPTS  1000

static uint8_t joystick_values[] = {
    0x01, 0x02, 0x04, 0x08, /* Axis */
    0x10, 0x20, 0x40, 0x80, /* Buttons */
};

/**
 * @brief Joy stick values.
*/
enum JoystickValues
{
    JoystickButtonA = 0x10,
    JoystickButtonB = 0x20,
    JoystickButtonC = 0x40,
    JoystickButtonD = 0x80,
    JoystickAxisX   = 0x01,
    JoystickAxisY   = 0x02,
    JoystickDeltaX  = 0x04,
    JoystickDeltaY  = 0x08,
};
 


/**
 * @brief Joy stick status structure.
*/

struct JoystickStatus{
    uint16_t AxisX;
    uint16_t AxisY;
    uint16_t DeltaX;
    uint16_t DeltaY;
    bool ButtonA;
    bool ButtonB;
    bool ButtonC;
    bool ButtonD;
    bool JoystickFlag;
};



/**
 * @brief Joy stick driver function util declared here.
*/
bool joystick_button(uint8_t buttonnum);
uint16_t joy_stick_status(uint8_t byte);

#endif  /*__ALINIX_KERNEL_GAME_PORT_H*/