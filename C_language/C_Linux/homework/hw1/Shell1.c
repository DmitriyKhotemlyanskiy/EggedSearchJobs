#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char str[15];
	char dir[20] = { "/bin/" };		//Way to directory with Linux programs
	int pid;
	do {
		printf("Shell1$** ");
		scanf("%s", str);		//Wait for user input
		if (strcmp("Esc", str) != 0) {	//If input is "Esc" end the loop and exit from the program
			if ((pid = fork()) == 0) {		//Create new fork and save it's pid
				strcat(dir, str);	//Create the way to a program
				if (execl(dir, str, NULL) == -1) {	//Execute program
					perror("Not Supported\n");
					exit(1);
				}
			}
			if (pid != 0) {
				waitpid(pid);  //Wait to end of program with pid
			}
		}
		else{ break;}
	} while (1);
	return 0;
}
