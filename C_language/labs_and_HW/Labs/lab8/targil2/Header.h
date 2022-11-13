#pragma once
#ifndef lab8_2
#define lab8_2
#include <stdio.h>
#include <stdlib.h>
typedef struct Stack {
	int top;         //index of the last member in array of a stack;
	int* Array;   //pointer to array of members of a stack
	int size;      //size of the array of a stack
	int count;   //the current number of members
}Stack, *PStack;

void InitStack(PStack s, int size);    //initialization of a new stack with capacity of size elements
void Push(PStack s, int new_elem);  //add a new member to array of the stack 
int Pop(PStack s, int *del_value); //delete member from the array of the stack and  return the deleted value  using  int * del_value

#endif
