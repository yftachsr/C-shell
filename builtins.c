#include "builtins.h"


char* builtins[] = { "cd", "help", "exit" };
void (*builtin_funcs[])(char** args) = { &cd, &help, &exit_shell };

void cd(char** args) {
	
	if(args[1] == NULL) {
		fprintf(stderr, "missing path argument to cd\n");
		return;
	}
	
	if(chdir(args[1]) != 0) {
		fprintf(stderr, "cd to %s failed", args[1]);
		return;
	}
	
	getcwd(cwd, sizeof(cwd));
		
}

void help(char** args) {
	
	printf("\nThis shell was writen by Yftach\n");
	printf("It's trying to imitate as much as possible the linux shell\n");
	printf("Features which have yet been implemented (but hopefully will be): history, piping, tab suggestions\n");
	printf("\nBuiltin commands are:\n");
	
	for(int i = 0; i < builtins_num(); i++)
		printf("%s ", builtins[i]);
		
	printf("\n\n");

}

void exit_shell(char** args) {
	
	exit(1);

}

int builtins_num() {
	return sizeof(builtins) / sizeof(char*);
}
