#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

#define N 3

typedef struct Section
{
	char code[11];
	char *name;
	int num_prod;
	int num_sold;
}Section;
void checkSec_Min(Section **Parr);//finds the address which contains the higher value of selled products
void checkSec_Max(Section **Parr);// finds the address which contains the lowest value of selled products
void enter_data(Section *arr);//gets the needed input
void main()
{
	Section arr[N], *Parr[N];// parr is a pointer the points to an array that contains the struct
	int i;
	enter_data(&arr);
	for (i = 0; i < N; i++)
		Parr[i] = &arr[i];
	checkSec_Max(&Parr);
	checkSec_Min(&Parr);
	printf("\nThe best section is: %s , %s", Parr[0]->name, &Parr[0]->code);
	printf("\nThe worst section is: %s , %s\n", Parr[1]->name, &Parr[1]->code);
	for (i = 0; i < N; i++)
	{
		free(arr[i].name);
	}
	system("pause");
}
void checkSec_Max(Section **Parr)
{
	int i;
	Section *best = Parr[0], *temp;
	for (i = 1; i < N; i++)
	{
		if (best->num_sold < &Parr[i]->num_sold)
		{
			temp = Parr[i];//we swap the adresses in order to get the highest value into the first index of parr
			Parr[i] = Parr[0];
			Parr[0] = temp;
			best = temp;
		}
	}
}
void checkSec_Min(Section **Parr)
{
	int i;
	Section *worst = Parr[0], *temp;
	for (i = 1; i < N; i++)
	{
		if (worst->num_sold > &Parr[i]->num_sold)//we do the same thing here
		{
			temp = Parr[i];
			Parr[i] = Parr[0];
			Parr[0] = temp;
			worst = temp;
		}
	}
}
void enter_data(Section *arr)
{
	char temp_name[21];
	int i;
	for (i = 0; i < N; i++)
	{
		printf("Please enter the code (up to ten letters): ");
		scanf("%s", arr[i].code);
		printf("\nPlease enter the Name of section (up to 20 letters): ");
		scanf("%s", temp_name);
		arr[i].name = (char*)malloc(strlen(temp_name) + 1);
		if (arr[i].name == NULL)
		{
			printf("\nError memory allocation to Name!!");
			exit(1);
		}
		strcpy(arr[i].name, temp_name);
		printf("\nEnter the number of products: ");
		scanf("%d", &arr[i].num_prod);
		printf("\nEnter the number of sold products: ");
		scanf("%d", &arr[i].num_sold);
		if (arr[i].num_prod < arr[i].num_sold)
		{
			while (arr[i].num_prod < arr[i].num_sold)//if the input doesnt make any sense
			{
				printf("\nIt's wrong, you can't sell more than you have...\n"
					"Please, repeat: ");
				printf("\nEnter the number of sold products: ");
				scanf("%d", &arr[i].num_sold);
			}
		}
	}
}
