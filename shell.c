#include "shell.h"

char cwd[PATH_MAX] = { '\0' };

int main(){

	char** args;
	getcwd(cwd, sizeof(cwd));   
	for(;;) {
		printf("%s", cwd);
		printf("> ");
		char* user_input = read_input();
		args = parse_input(user_input);
		execute_command(args);
	}	
	
	return 0;
}

char* read_input() {

	char* pb = NULL;
	size_t bufsize = 0;
	
	if(getline(&pb, &bufsize, stdin) == -1) {
		if(feof(stdin))
			exit(1);
		else
			exit(-1);
	}
	
	return pb;
}

char** parse_input(char* user_input) {
	
	char** splited_input = malloc(calc_arg_num(user_input) * sizeof(char*) + 1);
	char* token;
	
	if(splited_input == NULL) {
		fprintf(stderr, "Couldn't allocate memory");
		exit(-1);
	}
	
	token = strtok(user_input, DELIM);
	int pos = 0;
	
	while(token != NULL) {
		splited_input[pos] = token;
		pos++;
		token = strtok(NULL, DELIM);
	}
	
	splited_input[pos] = NULL;
		
	return splited_input;
}

void execute_command(char** args) {


	for(int i = 0; i < builtins_num(); i++) {
		if(strcmp(args[0], builtins[i]) == 0) {
			(*builtin_funcs[i])(args);
			return;
		}
	}

	int pid = fork(), status;
	
	if(pid < 0) {
		fprintf(stderr, "Couldn't fork");
		exit(-1);
	}
	
	if(pid == 0) { // Child
		status = execvp(args[0], args);
		if(status < 0) {
			if(errno == ENOENT) 
				fprintf(stderr, "unknown command: %s\n", args[0]);
			else 
				fprintf(stderr, "error upon executing: %s\n", strerror(errno));
			exit(-1);
		}
	} else { // Parent
		do {
			waitpid(-1, &status, WUNTRACED); 
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	
}

int calc_arg_num(char* user_input) {
	
	int counter = 0;
	int index = 0;
	
	while(strchr(DELIM, user_input[index]) != NULL) //skip white character in the begining of the input
		index++;
	
	for(; user_input[index] != '\0'; index++) {
		if(counter > 0 && strchr(DELIM, user_input[index-1]) != NULL) //ignore consecutive white spaces
			continue;
		if(strchr(DELIM, user_input[index]) != NULL)
			counter++;
	}
	
	return counter;
	
}




	
	



