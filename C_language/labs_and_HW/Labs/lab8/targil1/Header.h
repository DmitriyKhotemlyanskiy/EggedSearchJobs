#define _CRT_SECURE_NO_WARNINGS
#ifndef Implementation
#define Ipmlementation
#include <conio.h>
#include <stdio.h>
#define NUM 5

typedef struct Item {
	int num;
	struct Item* next;
}Item;

typedef struct Stack {
	Item* head;
	int size;         //a current number of items
}Stack, *PStack;

void Push(PStack s, int   new_elem);    //add a new member to list of the stack
int Pop(PStack s, int * del_value);       //delete member from the stack and  return the deleted value  using  int * del_value
void Del_List(PStack s);

#endif
