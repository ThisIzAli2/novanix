/**
 * @author Ali Mirmohammad
 * @file editor.cpp
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



#include <software/edit.h>
#include <common/init.hpp>

using namespace Novanix::common;

using namespace Novanix::system;
char* draw_editor() {
    char* key_editor = new char[2];
    INTEGER index = 0;
    char* text = new char[BUFFER_CONSTANT];
    char* full_prompt = new char[POW2(18)];

    while (read_key() != 0) {
        INTEGER keycode = read_key();
        key_editor = handle_keyboard(keycode);


        // Proper string comparison

        // Print the key to screen
        printk(Novanix::system::VGA_COLOR_WHITE, key_editor, 0);

        // Store the key in text buffer
        if (index < BUFFER_CONSTANT - 1 && key_editor[0] != '\n') {
            text[index++] = key_editor[0];
            text[index] = '\0';  // Always null-terminate
        }

        // If Enter is pressed
        if (key_editor[0] == '\n') {
            for (INTEGER k = 0; k < index; ++k) {
                full_prompt[k] = text[k];
            }
            full_prompt[index] = '\0';
            goto exit;            
        }
    }
    exit:
    return full_prompt;
}