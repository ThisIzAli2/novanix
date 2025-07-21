/**
 * @author Ali Mirmohammad
 * @file cat.cpp
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
#include <fs/cat.h>


VOID cat_file(char* file){
    for (INTEGER i = 0;i < i_file; i++){
        if (String::strcmp(files[i_file].data,file)){
            printk(VGA_WHITE,files[i_file].data,1);
        }
    }
}
