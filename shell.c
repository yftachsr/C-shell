#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* read_input();

int main(){

	char* args[] = {"ls", NULL};
	for(;;) {
		
		printf("> ");
		char* user_input = read_input();
		printf("%s", user_input);
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
