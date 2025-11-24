#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// TODO
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	for (int i = 0; i < N; i++){
		if (strcmp(cmd, allowed[i]) == 0){
			return 1;
		}
	}
	return 0;
}

int main() {

    // Add variables as needed
	pid_t pid;
	char *argv[20];
    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	char lineCopy[256];
	strcpy(lineCopy, line);

	char *cmd = strtok(lineCopy, " ");
	//Check if the command is valid
	if (isAllowed(cmd) == 0){
		printf("NOT ALLOWED!");
		continue;
	}

	argv[0] = cmd;
	for (int i = 1; i < 20; i++){
		argv[i] = strtok(NULL, " ");
	}
	

	// Add code to spawn processes for the first 9 commands
	// And add code to execute cd, exit, help commands
	//cd: if more than one argument, print "-rsh: cd: too many arguments"
	if (strcmp(cmd, "cd") == 0){
		char *dir = argv[1];
		if (argv[2] != NULL){
			printf("-rsh: cd: too many arguments");
			continue;
		}

	}
	//exit: return from main
	else if (strcmp(cmd, "exit") == 0){
		break;
	}
	//help: print avaliable commands
	else if (strcmp(cmd, "help") == 0){
		printf("The allowed commands are:\n1: cp\n2: touch\n3: mkdir\n4: ls\n5: pwd\n6: cat\n7: grep\n8: chmod\n9: diff\n10: cd\n11: exit\n12: help\n");
	}
	//Posix spawn any other valid command
	else{
		int status = posix_spawnp(&pid, cmd, NULL, NULL, argv, environ);
	}
	// Use the example provided in myspawn.c

    }
    return 0;
}
