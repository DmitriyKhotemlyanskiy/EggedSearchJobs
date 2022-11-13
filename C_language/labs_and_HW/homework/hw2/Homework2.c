#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>
typedef struct
{
	char *Name;
	long ID;
	int  ExamMark;
	char NewProg[2];
	char arr[6];
	char FinalScore;
	int OneOrZero;
}student;

typedef struct
{
	student *StudArr;
	int Count;
}University;

void option1(FILE *in, University *Temp);  //Gets the input file and a struct. We read the file input the data into a struct
//during that process we allocate enogh memory in order to get as many students that are in the input file
//this function is implemented just once
void option2(University *Temp, FILE *out); //This function outputs all the data that was entered to struct from the file
void option3(University *Temp, FILE *out); //Outputs the total score after checking the exam mark, checking 
//if the student is in the new program or not and whether the student has completed three home works or not.
void option4(University *Temp, FILE *out); //outputs statistical calculations, this function  gets the average, 
//the standart deviation, the amount of students, the range and amount of students that are in the new program or the old
void option5(University *Temp, FILE *out); //Gets the total average and shows the students that learn in the new 
//program or the old and that are above this average
void option6(University *Temp, FILE *out); //We output to the file END OF PROGRAM
FILE* OutOpen(FILE *out);  //This function opens the file
float AVG(University *Temp);//caclulates the average

void main()
{
	FILE *in=NULL, *out=NULL;
	char ch=0;
	int i;
	University Class;
	Class.StudArr = NULL;
	in = fopen("input.txt", "r");
	if (in == NULL)
	{
		printf("ERROR opening the file");
		exit(1);
	}
	printf("Hi, you have 6 options to choose from:(Press Enter after the option has been complete)\n");
	while (1) {
		printf("(1). Get the data of the students from the file.\n");
		ch = _getch();
		if (ch == '1') {
			option1(in, &Class);
			_getch();
			system("cls");
			break;
		}
		else
			printf("\nInput Error, please try again!\n");
	}
	while (1)
	{
		printf("What else do you want to do?\n");
		printf("(2). Get the output file of the enterd data.\n");
		printf("(3). Calculate the final score of the students\n");
		printf("(4). Show statiscal data of the exam marks\n");
		printf("(5). Show the data of the student who are above the course average:\n");
		printf("(6). If you choose this option the program will be finished.\n\n");
		printf("And your choise is: ");
		scanf("%c", &ch);
		switch (ch)
		{
		case '2':
			out = OutOpen(out);
			option2(&Class, out);
			fclose(out);
			_getch();
			break;
		case '3':
			out = OutOpen(out);
			option3(&Class, out);
			fclose(out);
			_getch();
			break;
		case '4':
			out = OutOpen(out);
			option4(&Class, out);
			fclose(out);
			_getch();
			break;
		case '5':
			out = OutOpen(out);
			option5(&Class, out);
			fclose(out);
			_getch();
			break;
		case '6':
			out = OutOpen(out);
			option6(&Class, out);
			printf("\nBye bye\n\n");
			fclose(out);
			for (i = 0; i < Class.Count; i++) //Free dynamic memory allocations
				free(Class.StudArr[i].Name);
			free(Class.StudArr); //Free dynamic memory allocations
			_getch();
			exit(1);
			break;
		default:
			printf("Input Error");
		}
		system("cls");
	}

	fclose(in);
	fclose(out);

}

void option1(FILE *in, University *Temp)
{
	Temp->Count = 0;
	char Temp_name[99];
	int i = 0;

	Temp->StudArr = (student*)malloc(sizeof(student));
	if (Temp->StudArr == NULL)
	{
		printf("\nError allocation memory!"); 
		exit(1);
	}
	while (!feof(in))
	{
		fscanf(in, "%s", Temp_name);
		Temp->StudArr[Temp->Count].Name = (char*)malloc((strlen(Temp_name) + 1) * sizeof(char));
		if (Temp->StudArr == NULL)
		{
			printf("\nError allocation memory!");
			exit(1);
		}
		strcpy(Temp->StudArr[Temp->Count].Name, Temp_name);
		fscanf(in, "%ld", &Temp->StudArr[Temp->Count].ID);
		fscanf(in, "%d", &Temp->StudArr[Temp->Count].ExamMark);
		fscanf(in, "%s", Temp->StudArr[Temp->Count].arr);
		fscanf(in, "%s", Temp->StudArr[Temp->Count].NewProg);
		Temp->Count++;

		Temp->StudArr = (student*)realloc(Temp->StudArr, (Temp->Count + 1) * sizeof(student));
		if (Temp->StudArr == NULL)
		{
			printf("\nError reallocating memory");
			exit(1);
		}
	}
	printf("The option you've selected has been complete");
	Temp->Count--; //to get the exact amount of students
}
void option2(University *Temp, FILE *out)
{
	int i, j, counter = 0;
	for (i = 0; i < Temp->Count; i++)
	{
		fprintf(out, "Student %d: %s %ld %d ", i + 1, Temp->StudArr[i].Name, Temp->StudArr[i].ID, Temp->StudArr[i].ExamMark);
		for (j = 0; j < 5; j++)
		{
			if (Temp->StudArr[i].arr[j] == '1')
				counter++;
		}
		if (counter >= 3) {
			fprintf(out, "%d", 1);
			Temp->StudArr[i].OneOrZero = 1;
		}
		else {
			fprintf(out, "%d", 0);
			Temp->StudArr[i].OneOrZero = 0;
		}
		fprintf(out, " %s\n", Temp->StudArr[i].NewProg);
		counter = 0;
	}
	printf("The option you've selected has been completed check your Output file in the originated folder ");
}
void option3(University *Temp, FILE *out)
{
	int i, j, HMGRD, counter = 0, GRDY,GRDN; //HMGRD - home work grade, GRDY - grades of the students in the new program
	//GRDN - grades of the students in the old program
	fprintf(out, "BEFORE:\n");
	for (i = 0; i < Temp->Count; i++)
	{
		fprintf(out, "Student %d: %s %ld %d ", i + 1, Temp->StudArr[i].Name, Temp->StudArr[i].ID, Temp->StudArr[i].ExamMark);
		for (j = 0; j < 5; j++)
		{
			if (Temp->StudArr[i].arr[j] == '1')
				counter++;
		}
		if (counter >= 3)
			fprintf(out, "%d", 1);
		else if (counter < 3)
			fprintf(out, "%d", 0);
		counter = 0;
		fprintf(out, " %s\n", Temp->StudArr[i].NewProg);
	}
	fprintf(out, "\nAFTER:\n");
	for (i = 0; i < Temp->Count; i++)
	{
		fprintf(out, "Student %d: %s %ld %d ", i + 1, Temp->StudArr[i].Name, Temp->StudArr[i].ID, Temp->StudArr[i].ExamMark);
		for (j = 0; j < 5; j++)
		{
			if (Temp->StudArr[i].arr[j] == '1')
				counter++;
		}
		if (counter >= 3)
		{
			fprintf(out, "%d ", 1);
			HMGRD = 100;
		}

		else if (counter < 3)
		{
			fprintf(out, "%d ", 0);
			HMGRD = 0;
		}
		if ((Temp->StudArr[i].ExamMark) >= 55)
		{
			if (HMGRD == 100)
			{
				if (!strcmp(Temp->StudArr[i].NewProg, "Y")) {
					GRDY = (int)(Temp->StudArr[i].ExamMark*0.8) + 20;  //GRDY = (ExamMark*0.8)+20 for the new program 
					fprintf(out, " final: %d\n", GRDY);
				}
				if (!strcmp(Temp->StudArr[i].NewProg, "N")) {
					GRDN = (int)(Temp->StudArr[i].ExamMark*0.9) + 10;  ////GRDY = (ExamMark*0.9)+10 for the old program 
					fprintf(out, " final: %d\n", GRDN);
				}
			}
			else 
				fprintf(out, " final: %d\n", (Temp->StudArr[i].ExamMark));
		}
		if ((Temp->StudArr[i].ExamMark) < 55)
			fprintf(out, " final: %d\n", (Temp->StudArr[i].ExamMark));
		counter = 0;
	}
	printf("The option you've selected has been completed check your Output file in the originated folder ");
}
void option4(University *Temp, FILE *out)
{
	int i, countNew=0,countOld=0,Range = 0, MAX = 0, MIN = 0;
	float average=0;
	double SD = 0;  //Standart Deviation
	fprintf(out, "The statistics data is:\n");
	average = AVG(Temp);
	fprintf(out, "[1]-> The average is %.2f\n", average);
	for (i = 0; i < Temp->Count; i++)
	{
		SD += pow(Temp->StudArr[i].ExamMark - average, 2);
	}
	SD /= (Temp->Count);
	SD = sqrt(SD);
	fprintf(out, "[2]-> The Standart Deviation is %.2f\n", SD);
	fprintf(out, "[3]-> The amount of students is %d\n", Temp->Count);
	MAX = Temp->StudArr[0].ExamMark;
	MIN = Temp->StudArr[0].ExamMark;
	for (i = 1; i < Temp->Count; i++)
	{
		if (MAX < Temp->StudArr[i].ExamMark)
			MAX = Temp->StudArr[i].ExamMark;
		if (MIN >Temp->StudArr[i].ExamMark)
			MIN = Temp->StudArr[i].ExamMark;
	}
	Range = MAX - MIN;
	fprintf(out, "[4]-> The RANGE is %d\n", Range);
	for (i = 0; i < Temp->Count; i++)
	{
		if (!strcmp(Temp->StudArr[i].NewProg, "Y"))
			countNew++;
		if (!strcmp(Temp->StudArr[i].NewProg, "N"))
			countOld++;
	}
	fprintf(out, "[5]-> The amount of students in the new programm: %d\n", countNew);
	fprintf(out, "[6]-> The amount of students in the old programm: %d\n", countOld);
	printf("The option you've selected has been completed check your Output file in the originated folder ");
}
void option5(University *Temp, FILE *out)
{
	int i;
	char cho;
	float average;
	average = AVG(Temp);
	fprintf(out, "The total average in the course: %.2f\n", average);
	printf("\nPress [1] if you want the new program students and [2] for the old program students: ");
	cho = _getch();
	if (cho == '1')
	{
		for (i = 0; i < Temp->Count; i++)
		{
			if (!strcmp(Temp->StudArr[i].NewProg, "Y")) {

				if (Temp->StudArr[i].ExamMark > average)
					fprintf(out, "Student %d: %s %ld %d %d %s\n", i + 1, Temp->StudArr[i].Name, Temp->StudArr[i].ID, Temp->StudArr[i].ExamMark, 1, "Y");
			}
		}
	}
	else if (cho == '2')
	{
		for (i = 0; i < Temp->Count; i++)
		{
			if (!strcmp(Temp->StudArr[i].NewProg, "N")) {
				if (Temp->StudArr[i].ExamMark > average)
					fprintf(out, "Student %d: %s %ld %d %d %s\n", i + 1, Temp->StudArr[i].Name, Temp->StudArr[i].ID, Temp->StudArr[i].ExamMark, 0,"N");
			}
		}
	}
	else printf("\nInput Error!");
	printf("\nThe option you've selected has been completed check your Output file in the originated folder ");
}
void option6(University *Temp, FILE *out)
{
	fprintf(out, "End Of Program");
	printf("The option you've selected has been completed check your Output file in the originated folder ");
}
FILE* OutOpen(FILE *out)
{
	out = fopen("Output.txt", "w");
	if (out == NULL)
	{
		printf("ERROR opening the file");
		exit(1);
	}
	return out;
}
float AVG(University *Temp)
{
	int i;
	float average = 0;
	for (i = 0; i < Temp->Count; i++)
	{
		average += Temp->StudArr[i].ExamMark;
	}
	return average /= (Temp->Count);
}