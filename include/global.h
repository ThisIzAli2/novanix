/**
 * @author Ali Mirmohammad
 * @file global.h
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
#ifndef __NOVANIX_KERNEL_GLOBAL_H
#define __NOVANIX_KERNEL_GLOBAL_H

#include <common/init.hpp>
#include <software/faccess.h>
#include <game/gaming_generic.hpp>

/**
 * IMPORTANT: Do not include any other file than init.hpp
 */

/**
 * NOTE: JUST DEFINE THE GLOBAL VARIABLES AS "extern", be careful here
 */
extern INTEGER i_file;
extern Snake snake;
extern INTEGER counts_failed_sudo;
extern bool have_access;
extern char user_password[];
extern char* current_directory;




#endif /*__NOVANIX_KERNEL_GLOBAL_H*/
