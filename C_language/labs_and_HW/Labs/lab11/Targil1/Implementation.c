#include "Header.h"

typedef struct node
{
	void *data;                        /* Store the keystroke by the user */
	struct node *next;                /* Pointer to the next node */
} STACKNODE;

void* top(STACKNODE *stack)
{
	return stack->data;
}

void push(void *key, STACKNODE **stack)
{
	STACKNODE *newnode;
	newnode = (STACKNODE *)malloc(sizeof(STACKNODE));
	newnode->data = key;
	newnode->next = (*stack);
	(*stack) = newnode;
}

void pop(STACKNODE **stack, void(*free_data)(void*))
{
	STACKNODE *oldnode;
	oldnode = (*stack);
	(*stack) = (*stack)->next;
	free_data(oldnode->data);  //we added free_data in order to delete first the data in the node
	free(oldnode);
}

int isempty(STACKNODE *stack)
{
	return (stack == NULL);
}
