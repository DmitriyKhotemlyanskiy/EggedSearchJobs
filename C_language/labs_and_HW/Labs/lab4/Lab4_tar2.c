#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	char cName[4];		//for class Name
	char ID[16];		//for ID number of student
	char sName[17];		//for student Name
}student;


void Get_Lost(char *);
void Find(FILE *, char *course);

int main()
{
	char course[4];
	FILE *file;
	file = fopen("Stud.txt", "r");
	if (file == NULL)
		Get_Lost("Cannot open file");
	printf("\nEnter the name of course,up to 3 letters: ");
	gets(course);			//get string of 3 letters from user
	Find(file, course);		//Call Find function
	fclose(file);			//close the text file
	return 0;
}
void Get_Lost(char *s)
{
	puts(s);
	exit(1);
}
void Find(FILE *f, char *course)
{
	char str_temp[8];			//temporary string fos saving new file name
	student temp_stud;			//example
	FILE *out;					//pointer for creating new output file
	int num;					//save ID numder of student
	while (fgets(temp_stud.cName, 4, f) != NULL)		//read input file until EOF
	{
		fgets(temp_stud.ID, 5, f);		//read student's ID from the file and save in a stucture
		fgets(temp_stud.sName, 17, f);	//read student's Name from the file and save in a stucture
		num = atoi(temp_stud.ID);		//convert string to integer number of ID
		_itoa(num, temp_stud.ID, 2);	//convert integer num to binary num and save as string
		strcpy(str_temp, course);		//copy string from course to str_temp
		if (strcmp(temp_stud.cName, course) == 0)	//compare 2 strings (user's str and str from input file)
		{										//if these two strings are equal create new output text file
			strcat(str_temp, ".txt");			//add to str_temp the text between " "
			out = fopen(str_temp, "a");			//create and open new text file with name of str_temp + ".txt"
			if (out == NULL)					//checking opening of file
				Get_Lost("Cannot open file");	//if file was not opened print error on the screen
			fprintf(out, "%s, %s, %s\n", temp_stud.ID, temp_stud.sName, temp_stud.cName);	//print to new file data about a student
			fclose(out);			//close text file
		}
	}
}