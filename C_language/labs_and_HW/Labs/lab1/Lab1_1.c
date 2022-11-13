#include<stdio.h>
#include<stdlib.h>

#define SIZE 10


int main()
{
   int i, Arr[SIZE]={3,5,10,1,2,7,6,9,0,8};
   int **Parr;
   if (!Parr = (int**)malloc(SIZE * sizeof(int*)))
   {
	   printf("Error!!!");
	   free Parr;
   }
   else {
	   Parr = &Arr;
	   for (i = 0; i < SIZE; i++) {
		   Parr[i] = Arr[(SIZE - 1) - i];
	   }
	   for (i = 0; i < SIZE; i++)
		   printf("\nParr[%d] = %d", i, **Parr[i]);
   }
   return 0;

}

