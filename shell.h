#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUF_SIZE 3
#define DELIM " \t\r\a\n"

char* readInput();
char** parseInput(char*);
int calcArgNum(char*);
int calcArgLength(char*);

#endif
