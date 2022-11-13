#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
	int num;
	struct Item* next;
}Item;

typedef struct List
{
	Item *head,*tail;
	int count;
}List;

void Error_Msg(char*);
void AddAsFirst(Item*, List*);
void AddAsLast(Item*, List*);
void MoveToAnotherList(List*, List*, List*);
void CreateList(List*, FILE *);
void PrintItem(Item*);
void PrintList(List*, char*);
void DeleteList(List*);

int main()
{
	List L, Posit, Negat;
	FILE *in = fopen("ThreeLists.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	L.head = NULL;
	L.tail = NULL;
	L.count = 0;

	Posit.head = NULL;
	Posit.tail = NULL;
	Posit.count = 0;

	Negat.head = NULL;
	Negat.tail = NULL;
	Negat.count = 0;

	CreateList(&L, in);
	PrintList(&L, "\nMy List:\n");
	MoveToAnotherList(&L, &Posit, &Negat);
	PrintList(&Posit, "\n\nThe Positive List:\n");
	PrintList(&Negat, "\n\nThe Negative List:\n\n");

	fclose(in);
	DeleteList(&Posit);
	DeleteList(&Negat);
	system("pause");
	return 0;
}

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}

void CreateList(List* L, FILE *f)
{
	int value;
	Item *temp;
	while (fscanf(f, "%d", &value) == 1)
	{
		temp = (Item*)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(L);
			Error_Msg("Memmory!");
		}

		temp->num = value;
		temp->next = NULL;
		if (L->head == NULL)
			L->head = temp;
		else
			L->tail->next = temp;
		L->tail = temp;
		L->count++;
	}
}


void PrintItem(Item* node)
{
	printf("%d--> ", node->num);
}

void PrintList(List* L, char* title)
{
	Item* temp = L->head;
	printf("%s", title);
	while (temp)
	{
		PrintItem(temp);
		temp = temp->next;
	}
	printf("\nThere are %d items in the list", L->count);
}

void AddAsFirst(Item* NewItem, List* MyList)
{
	if (MyList->head == NULL)  //if the list is empty
		MyList->tail = NewItem;	
	NewItem->next = MyList->head; 
	MyList->head = NewItem;
	MyList->count++;  
}

void AddAsLast(Item* NewItem, List* MyList)
{
	NewItem->next = NULL;  
	if (MyList->head == NULL)	//if the list is empty
		MyList->head = NewItem;  //add to the head of the list
	else	
	   MyList->tail->next = NewItem;  //add to the tail of the list
	MyList->tail = NewItem;  //tail = newItem 
	MyList->count++;
}

void MoveToAnotherList(List* MyList, List* PosList, List* NegList)
{
	Item *temp;
	while (MyList->head != NULL) 
	{
			temp = MyList->head;  
			MyList->head = temp->next;
			if (temp->num >= 0)  //if the num is positive
				AddAsLast(temp, PosList);
			else
				AddAsFirst(temp, NegList);  //if the num is negative
			MyList->count--;

	}
	MyList->tail = NULL;
}

void DeleteList(List* MyList)
{
	Item *temp;
	while (MyList->head != NULL)
	{
		temp = MyList->head;  //pointer to the head
		MyList->head = temp->next;  //move the head to the next Item
		free(temp); //free the Item
		MyList->count--;
	}
}