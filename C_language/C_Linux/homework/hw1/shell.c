#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char input[7];
	int pid;
	
	do {
		printf("Enter <Shell1> to run linux commands without parameters\n"
		"Enter <Shell2> to run linux commands with parameters\n"
		"Enter <Shell3> to run commands to file editing\nShell$** ");
		scanf("%s", input);		//Wait for user input
		if (strcmp("Exit", input) != 0) {		//If "Exit" break the loop and exit from the program
			if ((pid = fork()) == 0) {		//create new fork and save it's pid
				if (execv(input, NULL) == -1) {  //execute program named "input"
					printf("Not Supported\n");
					exit(1);
				}
			}
			if (pid != 0) {
				waitpid(pid);		//waiting for end of program with pid
			}
		}
		else{ break;}
	} while (1);
	return 0;
}
