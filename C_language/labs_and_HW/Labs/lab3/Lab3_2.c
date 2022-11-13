#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    char name[20];
    int grades[3];
}student;

void Error_Msg(char*);
int InputData(student **,FILE*);
void OutputData(int,student*,FILE*);

int main()
{
	FILE *fp; 
	student * arr;
        int size;
	if(!(fp=fopen("Students.txt","r")))
          Error_Msg("The input file is wrong");
        size = InputData(&arr,fp);
        fclose(fp);
        if(!(fp=fopen("Students.txt","w")))
        Error_Msg("The output file is wrong");
	OutputData(size,arr,fp);
        fclose(fp);





        return 0;	
}


int InputData(student ** p_array, FILE * fp)
{
 student * arr;
 int i=1;
 
 arr = (student*)malloc(sizeof(student));
 while(fscanf(fp,"%s %d %d %d",arr[i-1].name,&arr[i-1].grades[0],&arr[i-1].grades[1],&arr[i-1].grades[2])!=EOF)
 {


 }

 *p_array=

  return        /*return the number of students*/


}

void OutputData(int arr_size,student *arr,FILE* fp)
{
  
}


void Error_Msg(char* msg)
{
	printf("\n%s",msg);
	exit(1);
}