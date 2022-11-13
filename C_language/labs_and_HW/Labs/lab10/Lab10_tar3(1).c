#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  N  5
typedef enum { FALSE, TRUE } BOOL;

void Insert(BOOL(*f)(void *, void *), void *Element, void ** Parray);
BOOL Int_Comp(void *FirstElement, void *SecondElement);
BOOL IsFull();


int CurrentCount = 0;  /*global variable - only for the first ADT lab!Please,don't use!*/


int main()
{
	int Array[N], Value, i;
	void* PArray[N];                        /*pointers array*/

	printf("Enter numbers, -999 to stop  ");
	scanf("%d", &Value);

	while (Value != -999)
	{
		if (!IsFull())
		{
			Array[CurrentCount] = Value;
			Insert(Int_Comp, &Array[CurrentCount], PArray);  /*call the general function*/
			scanf("%d", &Value);
		}
		else
		{
			printf("\nThe array is full");
			break;
		}
	}
	printf("\n Your sorted array is:\n");             /*print the array in sorted order*/
	for (i = 0; i < CurrentCount; i++)
		printf(" %d ", *(int*)PArray[i]);
	printf("\n");
	system("pause");
	return 0;
}



BOOL IsFull()
{
	if (CurrentCount == N)
		return TRUE;
	return FALSE;
}


BOOL Int_Comp(void *FirstElement, void *SecondElement)
{
	if (*(int*)FirstElement > *(int*)SecondElement)
		return TRUE;
	return FALSE;
}


void Insert(BOOL(*f)(void *, void *), void *Element, void **Parray)
{
	int i,j;
	void **temp;  //for point on Parray
	if (CurrentCount == 0)
	{
		Parray[CurrentCount] = Element;  //if the array is empty insert the first value to Parray[0]
	}
	else
	{
		Parray[CurrentCount] = Element;  //inser to the Parray[CurrentCount]
		for (i = 0; i < CurrentCount; i++) //two loops for bubble sorting
		{
			for (j = 1; j <= CurrentCount; j++)
			{
				if (f(Parray[j - 1], Parray[j])) //if Parray[j-1]>Parray[j] do swap
				{
					temp = Parray[j];
					Parray[j] = Parray[j-1];
					Parray[j-1] = temp;
				}
			}
		}
	}
	CurrentCount++;  //counter of number of values in the array
}
	