/**
 * @author Ali Mirmohammad
 * @file fat32.cpp
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

#include <fs/fat32.h>


static INTEGER __always_inline fat32_cluster_to_lba(uint32_t cluster,fat32_fs_t *fs){
    return fs->data_start_lba + (cluster-2) * fs->sectors_per_cluster;
}