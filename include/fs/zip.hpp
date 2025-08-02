/**
 * @author Ali Mirmohammad
 * @file zip.hpp
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

#ifndef __NOVANIX_KERNEL_ZIP_HPP
#define __NOVANIX_KERNEL_ZIP_HPP

#include <common/init.hpp>
#include <fs/fs.h>

#define MAX_ZIPPED_FILES 10

class ZipFile{
    private:
        const char* cur_dir = current_directory;
        static INTEGER counter_zip;
        file_t zipped_files[MAX_ZIPPED_FILES];
        typedef struct Zip{
            file_t file;
        }zip_t;
        zip_t ret_file[MAX_ZIPPED_FILES];
        VOID __create_zip_file(file_t file){
            if (counter_zip >= 10){
                printk(VGA_COLOR_RED,"You cannot create more zip files than 10!",1);
            }else{            ret_file[counter_zip].file = file;
            counter_zip++;
        }
        }
    public:
        zip_t create_zip_file(file_t file){
            __create_zip_file(file);
            return ret_file[counter_zip];
        }


};

#endif /*__NOVANIX_KERNEL_ZIP_HPP*/