#ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>



extern char cwd[PATH_MAX];
extern char* builtins[];
extern void (*builtin_funcs[])(char**);

#endif
