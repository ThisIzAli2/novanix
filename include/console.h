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