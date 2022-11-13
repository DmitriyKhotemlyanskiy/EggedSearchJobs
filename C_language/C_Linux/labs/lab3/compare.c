#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fd_file1, fd_file2;
    if(argc == 3){
        if((fd_file1 = open(argv[1], O_RDONLY)) == -1){
            perror("Error opening file #1");
            return -1;
        }
        if((fd_file2 = open(argv[2], O_RDONLY)) == -1){
            perror("Error opening file #2");
            return -1;
        }
         compareFiles(fd_file1,fd_file2,argv[1],argv[2];        	    close(fd_file1);
         close(fd_file2);    
    }
	return 0; 
}

int compareFiles (int file1, int file2, char *file_1, char *file_2){
    int readFile1, readFile2;
    char buffFile1[64], buffFile2[64];
    if((readFile1 = read(file1, buffFile1, 64)) == -1){
        perror("Error reading file #1");
        return -1;
    }
    if((readFile2 = read(file2, buffFile2, 64)) == -1){
        perror("Error reading file #2");
        return -1;
    }
    while(readFile1 > 0 || readFile2 > 0){
        int i = 0;
        while(i < readFile1){
			if(buffFile1[i] != buffFile2[i]){
				printf("\nDifferent files\n");
            	return -1;
			}
			i++;
        }
        if((readFile1 = read(file1, buffFile1, 64)) == -1){
            perror("Error reading file #1");
            return -1;
        }
        if((readFile2 = read(file2, buffFile2, 64)) == -1){
            perror("Error reading file #2");
            return -1;
        }
    }
    printf("\nIdentical files\n");
    return 0;
}
