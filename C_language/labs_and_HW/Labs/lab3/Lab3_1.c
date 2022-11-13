#include<stdio.h>
#include<stdlib.h>

typedef struct Person
{
	char ID[10];
	char F_name[11];
	char L_name[16];
	int Age;
	char Addr[51];
}Person;

void Error_Msg(char*);

int main()
{
	Person temp;
	FILE *in,*out;
	
	return 0;	
}



void Error_Msg(char* msg)
{
	printf("\n%s",msg);
	exit(1);
}