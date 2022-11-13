#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	char Name[7];			//save name of student
	char Mahlaka[5];		//save the department 
	char num1[4], num2[4];	//save the marks of student
}student;

void Error_Msg(char*);
float average(char *a, char *b);
void FindStud(FILE*, FILE*);

int main()
{
	FILE *in, *out;
	
	if (!(in = fopen("Students.txt", "r")))Error_Msg("The input file is wrong");
	if (!(out = fopen("StudentsNew.txt", "w")))Error_Msg("The output file is wrong");
	FindStud(in, out);

	fclose(in);
	fclose(out);
	return 0;
}


void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}

void FindStud(FILE* input, FILE* output)
{
	student temp_stud;			//temporal saving of data
	while (feof(input) == NULL)		//loop for reading data of each student
	{
		fgets(temp_stud.Name, 7, input);		//read the name of student
		fgets(temp_stud.Mahlaka, 5, input);		//read the department
		fgets(temp_stud.num1, 4, input);		//read the first mark
		fgets(temp_stud.num2, 4, input);		//read the second mark
		if (!strcmp(temp_stud.Mahlaka, "Comp"))		//if strcmp == 0 
		{
			fprintf(output,"%s %.2f\n", temp_stud.Name, average(&temp_stud.num1, &temp_stud.num2)); //print to file the data of student
		}
	}
}
float average(char *a, char *b)
{
	int x = atoi(a), y = atoi(b);	//convert x and y from char to integer
	return (x+y)/2.0;			//calculate and return the average
}


