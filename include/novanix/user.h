/**
 * @author Ali Mirmohammad
 * @file user.h
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
#ifndef __NOVANIX_KERNEL_USER_H
#define __NOVANIX_KERNEL_USER_H


#define BASE_USER_PASS_BUFFER 32


#define USER_NAME_BUFFER BASE_USER_PASS_BUFFER
#define PASSWORD_BUFFER_SIZE BASE_USER_PASS_BUFFER

#define DEFAULT_PASSWORD "admin"

static char user_name[USER_NAME_BUFFER] = "admin";
static char *user_password = "admin";



#define PASSWORD  *user_password


#define USER_NOVANIX 8

#endif