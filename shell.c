#include "shell.h"

int main(){

	char** args;
	for(;;) {
		
		printf("> ");
		char* user_input = readInput();
		args = parseInput(user_input);
		executeCommand(args);
	}	
	
	return 0;
}

char* readInput() {

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

char** parseInput(char* userInput) {
	
	int numOfArgs = calcArgNum(userInput);
	char** splitedInput = malloc(numOfArgs * sizeof(char*) + 1);
	char* token;
	
	if(splitedInput == NULL) {
		fprintf(stderr, "Couldn't allocate memory");
		exit(-1);
	}
	
	token = strtok(userInput, DELIM);
	int pos = 0;
	
	while(token != NULL) {
		splitedInput[pos] = token;
		pos++;
		token = strtok(NULL, DELIM);
	}
	
	splitedInput[pos] = NULL;
		
	return splitedInput;
}

void executeCommand(char** args) {

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

int calcArgNum(char* userInput) {
	
	int counter = 0;
	int index = 0;
	
	while(strchr(DELIM, userInput[index]) != NULL) //skip white character in the begining of the input
		index++;
	
	for(; userInput[index] != '\0'; index++) {
		if(counter > 0 && strchr(DELIM, userInput[index-1]) != NULL) //ignore consecutive white spaces
			continue;
		if(strchr(DELIM, userInput[index]) != NULL)
			counter++;
	}
	
	return counter;
	
}

