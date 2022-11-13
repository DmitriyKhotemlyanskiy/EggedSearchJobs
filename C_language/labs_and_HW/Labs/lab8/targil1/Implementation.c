#include "Header.h"

void Push(PStack s, int   new_elem)
{
	Item *temp;
	if (s->size >= NUM)  //check if the stack is full
	{
		printf("\nThe Stack is full!");
		return;
	}
	temp = (Item*)malloc(sizeof(Item));  //memory allocation for a new item
	if (!temp)
	{
		printf("\nError allocation memory");
		Del_List(&s);		//if the memory was not allocated we are earase the list
		exit(1);
	}
	temp->num = new_elem;
	temp->next = NULL;
	s->size++;
		temp->next = s->head;
		s->head = temp;
	
}
int Pop(PStack s, int * del_value)		
{
	Item *temp;
	if (s->size == 0)  //check if the stack is empty
	{
		printf("\nThe Stack is empty");
		return 0;
	}
	else {
		temp = s->head;  //temp gets the disconected item from the head
		*del_value = temp->num;  //gets the deleted value
		s->head = s->head->next;
		free(temp);  //frees the memory
		s->size--;
		return 1;
	}
}
void Del_List(PStack s)
{
	Item *temp;
	while (s->head!=NULL){
		temp = s->head;
		s->head = s->head->next;
		free(temp); //frees the memory
	}
}
