/**
 * @author Ali Mirmohammad
 * @file shell.h
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
#ifndef _HEISEN_SHELL_H
#define _HEISEN_SHELL_H

#include <typing.hpp>

#include <typing.h>

typedef struct command{
    uint8_t present;
    char* command;
    VOID* callback;
    char* description;
}command_t;

VOID shellHandleKey(uint32_t keycode,char ch);
VOID shellInit();
VOID shellPrintKernel();
VOID shellHandleCommand();
VOID shellResetBuffer();
VOID registerCommand(char* command,VOID* callback,char * description);
VOID helpMenu();
VOID pung();


#endif // _HEISEN_SHELL_H