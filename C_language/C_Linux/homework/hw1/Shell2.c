#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define DIV " \t\r\n\a"

char **returnArgvArray(char *str);

int main() {
	char str[256];
	char dir[20] = { "/bin/" };
	char **argv;
	int pid, i;

	do {
		printf("Shell2$** ");
		fgets(str, sizeof(str), stdin);	//str save one word from user and put it into argv
		argv = returnArgvArray(str);
		if (strcmp("Esc", str) != 0) {	//If input is "Esc" end the loop and exit from the program
			if((pid = fork()) == 0) {		//Create new fork and save it's pid
				strcat(dir, argv[0]);		//Create a way to program
				if (execv(dir, argv) == -1) { //Execute a program
					printf("Not Supported\n");
					exit(1);
				}
			}
			if (pid != 0) {
				wait();		//Wait for end of program
			}
		}
		else{ break;}
	} while (1);
	free(argv);	//free memory argv
	return 0;
}
//******************Function for creating arguments array*************
char **returnArgvArray(char *str){
	int i = 0;
	int buff_size = 256;
	char **arr = malloc(strlen(str)*sizeof(char*));
	char *word;
	if(!arr){
		printf("\nMemory allocation Error\n");
		exit(1);
	}
	word = strtok(str,DIV);		//Separate a first word in string
	while(word != NULL){
		arr[i] = word;		//a[i] = one word from the string
		i++;
		//If not enough mamory for the argumments create a longer array
		if(i >= buff_size){
			buff_size += buff_size;
			arr = realloc(arr, buff_size * sizeof(char*));
			if(!arr){
				printf("\nMemory allocation Error\n");
				free(arr);
				exit(1);
			}
		}
		word = strtok(NULL, DIV);
	}
	arr[i] = NULL;		// The last argument is NULL
	return arr;
}

