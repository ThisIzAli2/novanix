/**
 * @author Ali Mirmohammad
 * @file feditor.h
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

#ifndef __NOVANIX_FEDITOR_H
#define __NOVANIX_FEDITOR_H



#include <common/init.hpp>


void inline draw_editor(){
    INTEGER keycode = read_key();
    char* key_editor = new char[2];
    int index = 0;
    key_editor = handle_keyboard(keycode);
    char* text = new char[BUFFER_CONSTANT];

    do {
        if (key_editor == "-1"){
            continue;
    }
    printk(Novanix::system::VGA_COLOR_WHITE, key_editor, 0);

    } while (read_key() != 0);

    delete[] key_editor;
    delete[] text;

}
void  insert_char(char c);
void backspace();
void save_file(const char* filename);
void editor(const char* filename);


#endif /*__NOVANIX_FEDITOR_H*/