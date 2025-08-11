/**
 * @author Ali Mirmohammad
 * @file mmap.cpp
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
#include <mmap.h>

VOID print_rem_ram(){
    uint64_t total_ram = 0;
    for (INTEGER i = 0;i < MEMMAP_ENTRIES;i++){
        if (memmap[i].type == 1){
            total_ram += memmap[i].length;
                printk(VGA_WHITE,"RAM Region: Base=0x%llx Length=0x%llx bytes\n",1,memmap[i].base_addr, memmap[i].length);
        }
        }

            printk(VGA_WHITE,"Total Available RAM: %llu bytes (%.2f MB)\n",1,
           total_ram, total_ram / (1024.0*1024.0));
           printk(VGA_WHITE,"RAM in MB:",1);
           printk(VGA_WHITE,stringify( total_ram / (1024.0*1024.0)),1);
}
