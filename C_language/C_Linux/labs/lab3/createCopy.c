#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
	int fd_from, newDir;
	char *dirName = NULL;
	char *fileName = NULL; 
//******If has two arguments we opening file and creating new directory******
	if(argc == 3){
		dirName = argv[1];
		fileName = argv[2];
		//*****Check if file name and dir name are correct******
		if(strlen(dirName)<1){
			perror("\nDirectory name ERROR\n");
			return -1;
		}

		if(strlen(fileName)<1){
			perror("\nFile name ERROR\n");
			return -1;
		}
		//****************************************************
		if((fd_from = open(argv[2],O_RDONLY)) == -1){
			perror("\nOpening file FROM\n");
			return -1;
		}
		
		if((newDir = mkdir(argv[1], 0777))==-1){
			perror("\nCreaing a new directory ERROR\n");
			return -1;
		}
		createFileInDir(argv[2], argv[1], fd_from);
	}
	close(fd_from);
	return 0;

}

int createFileInDir(char *fileName, char *dirName, int fd_from){
	int newNameLength = 0;
	int i = 0, j = 0;
	int fd_to, readb, writeb;
	char buffer[64];
//**********Creating character array with the way to a new file******
	newNameLength = strlen(fileName) + strlen(dirName)+2;
	char newFileName[newNameLength];

	while(i < strlen(dirName)){
		newFileName[i] = dirName[i];
		i++;
	}
	newFileName[i] = '/';
	i++;

	while(i < newNameLength){
		newFileName[i] = fileName[j];
		i++;
		j++;
	}
	newFileName[i] = '\0';
	
//********Copying a text*********************************************
	if((fd_to = open(newFileName, O_WRONLY | O_CREAT, 0664)) == -1){
		perror("\nOpen new file ERROR\n");
		return -1;
	}
	if((readb = read(fd_from, buffer, 64)) == -1){
		perror("\nReading from file ERROR\n");
		return -1;
	}
	while(readb > 0){
		if((writeb = write(fd_to, buffer, readb)) == -1){
			perror("\nWriting ERROR\n");
			return -1;
		}
		if((readb = read(fd_from, buffer, 64)) == -1){
			perror("\nReading from file error\n");
			return -1;
		}
	}
	close(fd_to);	
//*******************************************************************	
	return 0;
}
