#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 256

typedef struct Book
{
	char code[11];		//save book code
	char *Book_Name;	//save book name
}Book;
typedef struct Library
{
	char Name[MAX + 1];	//save Library name
	int num_books;		//save books number in library
	Book *book_array;	//array for saving book structure
}Library;

void Get_Lost(char* str);
void input_book(Book* B, FILE *in);
void input_library(Library *L, FILE *in);
void output_book(Book* B, FILE *out);
void output_library(Library* L, FILE *out);

int main()
{
	FILE *in, *out;
	Library Libr;
	int i;
	if (!(in = fopen("input.txt", "r")))	//if file wasn't opened call Get_Lost function
		Get_Lost("Error opening file input.txt");
	input_library(&Libr, in);		//call input_library function
	fclose(in);			//close text file
	if (!(out = fopen("output.txt", "w")))	//if file wasn't opened call Get_Lost function
		Get_Lost("Error opening file output.txt");
	output_library(&Libr, out);		//call output_library function
	fclose(out);			//close text file
	for (i = 0; i < Libr.num_books; i++)	//loop to free allocated memory of book name
		free(Libr.book_array[i].Book_Name);		//free memory
	free(Libr.book_array);		//free memory of array
	system("pause");
	return 0;
}


void Get_Lost(char* str)
{
	printf("\n%s", str);
	exit(1);
}

void input_library(Library *L, FILE *in)
{
	int i = 0;
	if (fscanf(in, "%s %d", L->Name, &L->num_books) == EOF)		//if Library is empty
		Get_Lost("The input file is empty");		//print error
	L->book_array = (Book*)malloc((L->num_books) * sizeof(Book));	//allocating memory for book array
	if ((L->book_array) == NULL)	//if memory allocating was not success print error
		Get_Lost("Error memory allocation for book_array");
	while (i < L->num_books)	//loop for input data to array
	{
		input_book(&L->book_array[i], in);	//call function for input data
		i++;		//books numder counter
	}
}
void input_book(Book* B, FILE *in)
{
	char temp[MAX + 1];		//save temporary book name
	fscanf(in, "%s %s", B->code, temp);		//read book code from file
	B->Book_Name = (char*)malloc(strlen(temp) + 1);		//allocating memory for book name
	if (B->Book_Name == NULL)		//if memory allocating was not success print error
		Get_Lost("Error memory allocation for Book_Name!!!");
	strcpy(B->Book_Name, temp);		//copy book name to allocated memory
}
void output_book(Book* B, FILE *out)
{
	fprintf(out, "\n%s \t %s", B->code, B->Book_Name);		//print data to output file
}
void output_library(Library* L, FILE *out)
{
	int i;
	fprintf(out, "%s", L->Name);		//print library name to output file
	for (i = 0; i < L->num_books; i++)
		output_book(&L->book_array[i], out);	//call function for output data
}