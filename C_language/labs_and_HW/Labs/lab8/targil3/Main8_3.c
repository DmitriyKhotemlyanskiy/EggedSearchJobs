#include "Header.h"


void main()
{
	Queue St;
	St.head = NULL;
	St.tail = NULL;
	St.size = 0;
	int i, del_val;
	int Arr[] = { 1,5,3,7,4,10,9 };		//we chose the Array to check the queue
	for (i = 0; i < 7; i++)
	{
		Enqueue(&St, Arr[i]);
	}
	Dequeue(&St, &del_val);
	printf("\nDel_val = %d", del_val);
	Enqueue(&St, Arr[5]);
	Enqueue(&St, Arr[6]);
	while (Dequeue(&St, &del_val))
	{
		printf("\nDel_val = %d", del_val);  //we free the memory using dequeue function
	}
	printf("\n");
	system("pause");

}