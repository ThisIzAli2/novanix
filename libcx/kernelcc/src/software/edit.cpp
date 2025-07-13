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

using namespace Novanix::system;
char* draw_editor(){
    char* key_editor = new char[2];
    int index = 0;
    char* text = new char[BUFFER_CONSTANT];
    char* full_prompt = new char[128];

    do {
        INTEGER keycode = read_key();
        key_editor = handle_keyboard(keycode);
        if (key_editor == "-1"){
            continue;
    }

    printk(Novanix::system::VGA_COLOR_WHITE, key_editor, 0);

    if (key_editor[0] == '\n'){
        for (int k = 0; k < index; ++k){
            full_prompt[k] = text[k];
        }
    }

    } while (read_key() != 0);

    delete[] key_editor;
    delete[] text;
    delete[] full_prompt;

    return full_prompt;

}
