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