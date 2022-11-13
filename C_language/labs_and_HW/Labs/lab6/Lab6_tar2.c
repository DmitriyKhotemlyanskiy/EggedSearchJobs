#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char code[11];
	char *name;
	char Dep[4];
	int marks[3];
	float avg;
	struct node* next;
}std;

void Error_Msg(char* str);//prints Error message
std* FromFileToList(std* head, FILE *in);//gets the data from thef ile and divides it to a linked node
std* Delete_Stud(std* toDel, std* head);//the student with the max average is out of the list
void DeleteList(std* head);//resets the list
void PrintList(std* head);
std* FindMax(std* head);//gets the student with the max average

int main()
{
	int i;
	FILE *f;
	std *Head = NULL, *temp;
	if ((f = fopen("List1.txt", "rt")) == NULL)
		Error_Msg("input error");
	Head = FromFileToList(Head, f);

	printf("\nThe list is:");
	PrintList(Head);

	temp = FindMax(Head);
	printf("\n\nthe student with max average:\n");
	printf("%s %s %s ", temp->code, temp->name, temp->Dep);
	for (i = 0; i<3; i++)
		printf(" %d ", temp->marks[i]);

	printf("\n\nThe list after change:");
	Head = Delete_Stud(FindMax(Head), Head);
	PrintList(Head);
	DeleteList(Head);
	return 0;
}
std* FromFileToList(std* head, FILE *in)
{
	float AVG=0;
	int i;
	std *temp; //we will work on temp in order not to change the address of head
	char TempName[256];  //buffer for reading name from file
	while (!feof(in))//go until you finish reading the file
	{
		temp = (std*)malloc(sizeof(std));
		if (temp == NULL)
		{
			printf("ERROR ALLOCATING");
			exit(1);
		}
		
		fscanf(in, " %s %s %s ", temp->code, TempName, temp->Dep);
		temp->name = (char*)malloc(strlen(TempName) + 1);//TempName is a temporary string in order to allocate the memory exactly for the name entered.
		if(temp->name==0)
		{
			printf("ERROR ALLOCATING");
			exit(1);
		}

		strcpy(temp->name, TempName);
		for ( i = 0; i < 3; i++)//there are 3 marks for each person so we sum them up in AVG and then divied it by 3 to get the average.
		{
			fscanf(in, "%d", &temp->marks[i]);//we put & because it is an int variable.
			AVG += temp->marks[i];
		}
		AVG /= 3.0;
		temp->avg = AVG;
		AVG = 0;
		temp->next = head;
		head = temp;
	}
	return head;
}

void PrintList(std* head)
{
	std *temp = head;
	while (temp != NULL)
	{
		int i;
		printf("\n%s %s %s ",temp->code,temp->name,temp->Dep);
		for ( i = 0; i < 3; i++)
			printf("%d ", temp->marks[i]);
		temp = temp->next;//go ahead to the next linked node
	}
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}
std* FindMax(std* head)
{
	std *temp = head;
	std *MAX = head;
	while (temp->next!=NULL)
	{
		temp = temp->next;
		if (MAX->avg < temp->avg)
			MAX = temp;		
	}
	return MAX;
}


std* Delete_Stud(std* toDel, std* head)
{
	std *temp,*ptr=NULL;//we use ptr as a pointer to toDel in order to free toDel
	if (head == NULL)
		return NULL;

	if (toDel == head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	else
	{
		temp = head;
		while (temp->next != NULL)
		{
			if (temp->next == toDel)
			{
				ptr = toDel;
				temp->next = temp->next->next;
				free(ptr);
				break;
			}
			temp = temp->next;
		}
	}
	return head;
}

void DeleteList(std* head)
{
	std *temp = head;
	std *next;//we use this pointer in order to give it the address
	while (temp != NULL)
	{
		next = temp->next; 
		free(temp);
		temp = next;
	}
	head = NULL;
}
