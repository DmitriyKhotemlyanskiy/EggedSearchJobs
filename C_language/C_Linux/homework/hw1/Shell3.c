#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

#define DIV " \t\r\n\a"

char **readArguments(char *str);
int Merge3(char* args[]);
int Merge2(char *args[]);
int Find_Max(char *args[]);
int Size (char* str);
int Delete(char *args[]);

int main() {
	char** args;
	char str[64];	
	do{
		printf("Shell3$** ");
		fgets(str, sizeof(str), stdin);
		args = readArguments(str);
		if(strcmp(args[0],"Merge")==0){
			if(args[3] != NULL)
				Merge3(args);
			else Merge2(args);
		}
		else if(strcmp(args[0],"Find_Max")==0){
			int res;
			if(args[2] != NULL){
				res = Find_Max(args);
				if(res == 1)
					printf("%s\n", args[1]);
				else if(res == 2)
					printf("%s\n", args[2]);
				else
					printf("Same length files\n");
			}
			else printf("Not supported\n");
		}
		else if(strcmp(args[0],"Size")==0){
			if(args[1] != NULL)
				printf("%d\n", Size(args[1]));
			else 
				printf("Not supported\n");
		}
		else if(strcmp(args[0],"Delete")==0){
			if(args[1] != NULL)
				Delete(args);
			else printf("Not supported\n");	
		}
		else if(strcmp(args[0], "Esc") == 0) 
			break;
		else
			printf("Not supported\n");
		
	}while(1);
	free(args);
	return 0;
}
//******************Function for creating arguments array*************
char **readArguments(char *str){
	int i = 0;
	int buff_size = 64;
	char **arr = malloc(strlen(str)*sizeof(char*));
	char *word;
	if(!arr){
		printf("\nMemory allocation Error\n");
		exit(1);
	}
	word = strtok(str,DIV); 	//Separate a first word in string
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

//**********************Merge with 3 arguments*****************************
int Merge3(char* args[]){
	int fd_from1, fd_from2, fd_to;
	int read_b1, read_b2, write_b;
	int last_iteration_file1 = 0;
	int last_iteration_file2 = 0;
	char read_buff1[2], read_buff2[2];
//************Creting and opening 3 files*******************
	if((fd_from1 = open(args[1], O_RDONLY)) == -1){
		printf("\nOpening file %s\n", args[1]);
		return -1;
	}
	if((fd_from2 = open(args[2], O_RDONLY)) == -1){
		printf("\nOpening file %s\n", args[2]);
		return -1;
	}
	if((fd_to = open(args[3], O_WRONLY | O_CREAT, 0664)) == -1){
		printf("\n%s file ERROR\n", args[3]);
		return -1;
	}
	if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
		printf("\nReading from file %s ERROR\n", args[1]);
		return -1;
	}
	if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
		printf("\nReading from file %s ERROR\n", args[2]);
		return -1;
	}
//***************Main loop reading 2 files and write in file 3************** 
	while(1){
		//****************Loop for reading file 1 char after char*****************
			while(read_b1 > 0 && read_buff1[0] != ' ' && read_buff1[0] != '\n'){
				if((write_b = write(fd_to, read_buff1, read_b1)) == -1){
					printf("\nWriting ERROR\n");
					return -1;
				}
				if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
					printf("\nReading from file %s ERROR\n", args[1]);
					return -1;
				}
			//Add sapce after writing a word 
				if(read_buff1[0] == ' '){
					if((write_b = write(fd_to, " ", 1)) == -1){
						printf("\nWriting ERROR\n");
						return -1;
					}
				}					
			}
	//**************End of Loop reads file 1*****************************
		//Read one more char that it is space ' '
			if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
				printf("\nReading from file %s ERROR\n", args[1]);
				return -1;
			}
		//If its last iteration add space after the last words
			if(read_b1 == 0 && last_iteration_file1 == 0){
				if(read_b1 == 0){
					if((write_b = write(fd_to, " ", 1)) == -1){
						printf("\nWriting ERROR\n");
						return -1;
					}
				}
				last_iteration_file1 = 1;
			}		
	//****************Loop for reading file 2 char after char*****************		
			while(read_b2 > 0 && read_buff2[0] != ' ' && read_buff2[0] != '\n'){
				if((write_b = write(fd_to, read_buff2, read_b2)) == -1){
					printf("\nWriting ERROR\n");
					return -1;
				}
				if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
					printf("\nReading from file %s ERROR\n", args[2]);
					return -1;
				}
		//Add sapce after writing a word
				if(read_buff2[0] == ' '){
					if((write_b = write(fd_to, " ", 1)) == -1){
						printf("\nWriting ERROR\n");
						return -1;
					}
				}
			}
	//**************End of Loop reads file 2*****************************
		//Read one more char that it is space ' '
			if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
				printf("\nReading from file %s ERROR\n", args[2]);
				return -1;
			}
		//If its last iteration add space after the last words
			if(read_b2 == 0 && last_iteration_file2 == 0){
				if(read_b2 == 0){
					if((write_b = write(fd_to, " ", 1)) == -1){
						printf("\nWriting ERROR\n");
						return -1;
					}
				}
				last_iteration_file2 = 1;
			}
	//If EOF of file 1 and file 2	
		if(read_b1 <= 0 && read_b2 <= 0){
			 break;
		}
	}
//*****************End of Main Loop***************************************
	close(fd_from1);
	close(fd_from2);
	close(fd_to);
	return 0;
}

int Merge2(char *args[]){
	int fd_from1, fd_from2;
	int read_b1, read_b2;
	int last_iteration_file1 = 0;
	int last_iteration_file2 = 0;
	char read_buff1[2], read_buff2[2];
//************Opening 2 files*******************
	if((fd_from1 = open(args[1], O_RDONLY)) == -1){
		printf("\nOpening file %s\n", args[1]);
		return -1;
	}
	if((fd_from2 = open(args[2], O_RDONLY)) == -1){
		printf("\nOpening file %s\n", args[2]);
		return -1;
	}
	if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
		printf("\nReading from file %s ERROR\n", args[1]);
		return -1;
	}
	if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
		printf("\nReading from file %s ERROR\n", args[2]);
		return -1;
	}
//***************Main loop read 2 files and prints on screen************* 
	while(1){
		//****************Loop for reading file 1 char after char*****************
			while(read_b1 > 0 && read_buff1[0] != ' ' && read_buff1[0] != '\n'){
				printf("%c", read_buff1[0]);
				if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
					printf("\nReading from file %s ERROR\n", args[1]);
					return -1;
				}
			//Add sapce after writing a word 
				if(read_buff1[0] == ' '){
					printf(" "); 
				}					
			}
	//**************End of Loop reads file 1*****************************
		//Read one more char that it is space ' '
			if((read_b1 = read(fd_from1, read_buff1, 1)) == -1){
				printf("\nReading from file %s ERROR\n", args[1]);
				return -1;
			}
		//If its last iteration adds space after the last words
			if(read_b1 == 0 && last_iteration_file1 == 0){
				if(read_b1 == 0){
					printf(" ");
				}
				last_iteration_file1 = 1;
			}		
	//****************Loop for reading file 2 char after char*****************		
			while(read_b2 > 0 && read_buff2[0] != ' ' && read_buff2[0] != '\n'){
				printf("%c", read_buff2[0]);
				if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
					printf("\nReading from file %s ERROR\n", args[2]);
					return -1;
				}
		//Add sapce after writing a word
				if(read_buff2[0] == ' '){
					printf(" ");
				}
			}
	//**************End of Loop reads file 2*****************************
		//Read one more char that it is space ' '
			if((read_b2 = read(fd_from2, read_buff2, 1)) == -1){
				printf("\nReading from file %s ERROR\n", args[2]);
				return -1;
			}
		//If its last iteration adds space after the last words
			if(read_b2 == 0 && last_iteration_file2 == 0){
				if(read_b2 == 0){
					printf(" ");
				}
				last_iteration_file2 = 1;
			}
	//If EOF of file 1 and file 2	
		if(read_b1 <= 0 && read_b2 <= 0){
			 break;
		}
	}
//*****************End of Main Loop*********************
	close(fd_from1);
	close(fd_from2);
	printf("\n");
	return 0;
}
//************Find_Max uses Size funcion****************
int Find_Max(char *args[]){
	int res1 = Size(args[1]);
	int res2 = Size(args[2]);
	if(res1 > res2)
		return 1;
	else if(res1 < res2)
		return 2;
	else return 0;
}
//******************************************************
int Size (char* str){
	int fd_from;
	int read_b;
	char read_buff[2];
	int count = 0;
//************Opens and reads 1 file**********************
	if((fd_from = open(str, O_RDONLY)) == -1){
		printf("\nOpening file %s\n", str);
		return -1;
	}
	if((read_b = read(fd_from, read_buff, 1)) == -1){
		printf("\nReading from file %s ERROR\n", str);
		return -1;
	}
//***********Counts how many characters are in the file without spaces********
	while(read_b > 0){
				if(read_buff[0] != ' ' && read_buff[0] != '\n')
					count++;
				if((read_b = read(fd_from, read_buff, 1)) == -1){
					printf("\nReading from file %s ERROR\n", str);
					return -1;
				}				
			}
	return count;
}

int Delete(char *args[]){
	if(remove(args[1])) {
		printf("Error removing file: %s", args[1]);
		return 1;
	}
	else return 0;
}

