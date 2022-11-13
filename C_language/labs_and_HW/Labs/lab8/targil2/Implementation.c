#include "Header.h"

void InitStack(PStack s, int size)
{
	s->Array = malloc(sizeof(int)*size);
	if (s->Array == NULL)
	{
		printf("\nERROR ALLOCATING");
		exit(1);
	}
	s->count = 0;
	s->size = size;
	s->top = 0;
}
void Push(PStack s, int new_elem)
{
	if (s->size == s->top)
	{
		printf("\nThe Stack is full");
		return;
	}
	s->Array[s->top] = new_elem;
	s->count++;
	s->top++;
}
int Pop(PStack s, int *del_value)
{
	if (s->top == 0) {
		printf("\nThe Stack is empty");
		return 0;
	}

	*del_value = s->Array[s->top - 1];
	s->top--;
	s->count--;
	return 1;
}