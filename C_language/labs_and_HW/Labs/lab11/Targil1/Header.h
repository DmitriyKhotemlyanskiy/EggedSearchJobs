#define _CRT_SECURE_NO_WARNINGS
#ifndef _Implementation
#define _Implementation
#include <stdio.h>
#include <stdlib.h>

typedef struct node *PSTACKNODE; //setting a general ADT struct

void push(void *key, PSTACKNODE *stack);
void pop(PSTACKNODE **stack, void(*free_data)(void*));
int isempty(PSTACKNODE stack);
void* top(PSTACKNODE stack);
#endif