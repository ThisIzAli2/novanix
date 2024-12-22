#ifndef _HEISEN_SHELL_H
#define _HEISEN_SHELL_H

#include <heisen/typing.h>

typedef struct command{
    uint8_t present;
    char* command;
    void* callback;
    char* description;
}command_t;

void shellHandleKey(uint32_t keycode,char ch);
void shellInit();
void shellPrintKernel();
void shellHandleCommand();
void shellResetBuffer();
void registerCommand(char* command,void* callback,char * description);
void helpMenu();
void pung();


#endif // _HEISEN_SHELL_H