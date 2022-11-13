#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef struct Item
{
	char Name[10];
	int code;
	struct Item *next;
}item;

item* add_to_List(item *head);
int main()
{
	int i;
	item *Head = NULL, *temp;
	for (i = 1; i <= N; i++)
	{
		temp = add_to_List(Head);
		Head = temp;
	}
	temp = Head;
	printf("\n\nThe List is:  ");
	while (temp != NULL) {
		printf("%d %s --> ",temp->code,temp->Name);
		temp = temp->next;
	}
	temp = Head;
	while (Head != NULL) {
		temp = Head;
		Head = Head->next;
		free(temp);
	}
	printf("\n");
	system("pause");
	return 0;
}
item* add_to_List(item *head)
{
	char name[11];  //buffer for name
	int num;
	item *temp = (item*)malloc(sizeof(item));  //memory allocation for new node
	if (!temp)
		printf("\nError allocation memory for Item!!");
	printf("Enter a new code and Name: ");
	scanf("%d%s", &num, name);
	strcpy(temp->Name,name);
	temp->code = num;
	temp->next = head;	//temp->next gets the address of head of linked list
	head = temp;	//move the pointer of head to the new node that we created
	return head;
}