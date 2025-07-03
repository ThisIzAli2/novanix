/**
 * @author Ali Mirmohammad
 * @file console.h
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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <fs/vfs.h>
#include <typing.hpp>

VOID console_init(char *usr);
VOID console_init_gui(char *usr);
VOID console_run();
VOID console_run_gui();
VOID console_gui_print(char *str);

char *get_dir();
INTEGER character_check(char c);
VOID console_print(char *buffer, ...);
VOID console_exec(char *buf);
VOID console_cd(char *dir, char *command);
VOID console_start(char *dir, char *command);
VOID console_read(char *dir, char *command);
VOID console_write(char *dir, char *command);
VOID console_touch(char *dir, char *command);
VOID console_delete(char *dir, char *command);
char *console_pwd();
char *console_pwd_user();
VOID print_file(file *f);
VOID print_meminfo();
char *get_argument(char *command, INTEGER n);

#endif