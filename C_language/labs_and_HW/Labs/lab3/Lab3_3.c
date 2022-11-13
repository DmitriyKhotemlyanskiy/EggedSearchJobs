#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 4


float CRadius(Complex);
void Error_Msg(char* str);
void InputAndWriteToFile(FILE *f);
int CheckFile(FILE *f,float m);

int main()
{
	
	FILE *f;
	
	
	InputAndWriteToFile(f);
        

	printf("\nThere are %d big numbers\n",CheckFile(f,4));
        return 0;
}


void Error_Msg(char* str)
{
   printf("\n%s",str);
   exit(1);
}

