/**
 * @author Ali Mirmohammad
 * @file listfiles.hpp
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
#ifndef __LIST_FILES
#define __LIST_FILES



#include <typing.hpp>
#include <types.h>
#include <common/init.hpp>
#include <common/devlinkedlist.hpp>

class Retain{

    public:
    const char* filename;
    INTEGER chunk_size;
    const char* content;
        Retain(const char* filename,INTEGER chunk_size,const char* content){
            this->filename = filename;
            this->chunk_size = chunk_size;
            this->content = content;

        }    
    public:
        VOID retention(const char* file_name,INTEGER size,const char* content){
                    const char* file = file_name;
            if (!file_name || !size){
                Novanix::system::printk(VGA_COLOR_WHITE,"ERROR!",1);
            }
            else{
                Novanix::system::printk(VGA_COLOR_WHITE,"Creating file: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,file_name,1);
                Novanix::system::printk(VGA_COLOR_WHITE," with size: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,stringify(size),1);
                Novanix::system::printk(VGA_COLOR_WHITE," and content: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,content,1);
            }
                }
    
};  


Retain inline create_file(const char* file_name,INTEGER size,const char* content){
    Retain file(file_name,size,content);
    file.retention(file_name,size,content);
    return file;
}





#endif /*__LIST_FILES*/