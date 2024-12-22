/**
 * @file joystick.cpp
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
 * MIT License

Copyright (c) 2020 Remco123

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @abstract:
 *  - Implements the joystick driver utility.
*/
#include <core/port.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/c++/gameport.hpp>
#include <system/log.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Joy stick driver util")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


struct JoystickStatus *jst;

using namespace CactusOS::system;

/**
 * @brief Checks if a specific joystick button is pressed.
 *
 * This function iterates over a predefined range of joystick button values
 * to determine if the specified button is pressed. The function reads the
 * state of the joystick from the hardware port and returns true if the button
 * is pressed, and false otherwise.
 *
 * @param buttonnum The button number to check.
 *
 * @return Returns true if the specified button is pressed. Returns false if the
 *         button is not pressed or if the button number is out of the valid range.
 */
bool joystick_button_cxx(uint8_t buttonnum){
    int i;
    for (i = 4; i <= 8; ++i){
        if (joystick_values[i] == buttonnum){
            return ((CactusOS::core::inportb(JOYSTICK_PORT) & buttonnum) == 0);
        }
    }
    // Log(Error,"Invalid value:; Out of bounds.\n");
    return 0;
}

/**
 * @brief Retrieves the current status of the joystick.
 *
 * This function collects the current status of the joystick, including the
 * positions of the X and Y axes, the changes in the X and Y positions (deltas),
 * and the states of several buttons (A, B, C, D). It returns this information
 * encapsulated in a `JoystickStatus` struct.
 *
 * @return A `JoystickStatus` struct containing the current state of the joystick,
 *         including axis positions, deltas, and button states.
 */
struct JoystickStatus joystick_dump(void)
{
    struct JoystickStatus jst;
    jst.AxisX   = joy_stick_status_cxx(JoystickAxisX);
    jst.AxisY   = joy_stick_status_cxx(JoystickAxisY);
    jst.DeltaX  = joy_stick_status_cxx(JoystickDeltaX);
    jst.DeltaY  = joy_stick_status_cxx(JoystickDeltaY);
    jst.ButtonA = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonA));
    jst.ButtonB = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonB));
    jst.ButtonC = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonC));
    jst.ButtonD = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonD));
    return jst;
}
/* 
 * There's no IRQ for joystick port, so we poll instead.
 * However isn't a problem, because very few data is transmitted
 * through game port.
 */

uint16_t joy_stick_status_cxx(uint8_t byte){
    int time_out = 0;
    /* Disable interrupts, so they don't affect timing */
    asm volatile("cli");
    /* Any read needs to be with a write. The byte that we send 
     * can be garbage, it doesn't matters.
     */
    unsigned char stat = (uint16_t)CactusOS::core::inportb(JOYSTICK_PORT);
    CactusOS::core::outportb(JOYSTICK_PORT, GARBAGE_DATA);

    while (1){
        if (stat & byte){
            jst->JoystickFlag = true;
            break;

        }
        else if (time_out == MAX_TIME_ATTEMPTS){
            jst->JoystickFlag = false;
            return 0;
        }
        ++time_out;
    }
    asm volatile("sti");
    return (stat & byte);
}