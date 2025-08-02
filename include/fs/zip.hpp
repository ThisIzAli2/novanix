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
        file_t zipped_files[MAX_ZIPPED_FILES];
        typedef struct Zip{
            file_t file;
            char* file_name;
            char* data;
            char* file_directory;
            INTEGER number;
        }zip_t;
        static zip_t create_zip_file(file_t file,char* data){
            
        }
    public:


};

#endif /*__NOVANIX_KERNEL_ZIP_HPP*/