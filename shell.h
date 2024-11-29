#ifndef SHELL_H
#define SHELL_H

#include "master.h"
#include "builtins.h"

#define DELIM " \t\r\a\n"

char* read_input();
char** parse_input(char*);
int calc_arg_num(char*);
void execute_command(char**);


#endif
