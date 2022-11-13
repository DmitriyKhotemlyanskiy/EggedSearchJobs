#define _CRT_SECURE_NO_WARNINGS
#ifndef Implementation   //if not define in header file
#define Implementation
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM 5		//the size of the stack

typedef struct Item {
	int num;
	struct Item* next;
}Item;
typedef struct Que {
	Item* head, *tail;
	int size;      //a current number of items
}Queue, *PQue;

void Enqueue(PQue Q, int   new_elem);   //add a new member to list of the queue 
int Dequeue(PQue Q, int * del_value);     //delete member from the queue and  return the deleted value  using int *del_value
void Del_List(PQue s);   //function for delete the list
#endif