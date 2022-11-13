#include "Header.h"

void Enqueue(PQue Q, int   new_elem)
{
	Item *temp;
	if (Q->size >= NUM)   //check if the stack is full
	{
		printf("\nThe Queue is full!");
		return;
	}
	temp = (Item*)malloc(sizeof(Item));		//memory allocation for new item of data
	if (!temp)
	{
		printf("\nError allocation memory");
		Del_List(Q);
		exit(1);
	}

	temp->num = new_elem;
	temp->next = NULL;
	Q->size++;  //counter for size of the Queue
	if (Q->head == NULL && Q->tail == NULL)	//if the Queue is empty 
	{
		temp->next = Q->head;	//connect the first item to the head 
		Q->head = Q->tail = temp;
	}
	temp->next = Q->head;	//if the Queue is not empty connect a new item to the head of list
	Q->head = temp;

}
int Dequeue(PQue Q, int *del_value)
{
	Item *temp = Q->tail, *pt = Q->head;  
	if (Q->size == 0)	//check if the Queue is empty
	{
		printf("\nThe Queue is empty");
		return 0;
	}
	else {
		while (pt != NULL)
		{
			if (Q->head == Q->tail) //check if the list have only one item
			{
				Q->tail = pt;   //we used a pointer in order to get the "latest" tail
				*del_value = temp->num;  //gets the first entered number 
				free(Q->head);		//frees the memory
				Q->size--;
				return 1;
			}
			if (pt->next == Q->tail)  //check if we are one before the last
			{
				Q->tail = pt;		//we used a pointer in order to get the "latest" tail
				*del_value = temp->num;		//gets the first entered number 
				free(pt->next);		//frees the memory
				Q->size--;
				return 1;
			}
			pt = pt->next;	
		}

	}
}
void Del_List(PQue Q)
{
	Item *temp;
	while (Q->head != NULL) {	//runs in a loop until the end
		temp = Q->head;		//disconects the item from the list
		Q->head = Q->head->next;
		free(temp);  //frees the memory
	}
	Q->head = NULL;
	Q->tail = NULL;
}