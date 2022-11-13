#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define NUMELEMS 7

char* findMin(char** arrP,int arrSize);

int main()
{
	char *a[] = {"Alona","Nir","Amina","Yosef","alice","Amos","bob"};
	int i;

	for(i=0; i<NUMELEMS; i++)
	   printf("%s\n", a[i]);
	printf("\n%s", findMin(a, NUMELEMS));

	return 0;
}


