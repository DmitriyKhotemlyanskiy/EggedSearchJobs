#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Bit_Count(unsigned int x);
void Bin_Print(unsigned int x);

int main()
{
	unsigned int x;

	printf("Enter a number");
	scanf("%d", &x);
	printf("There are %d bits equal to one in %d\n", Bit_Count(x), x);
	printf("The binary representation of %d is ", x);
	Bin_Print(x);

	system("pause");
	return 0;
}


int Bit_Count(unsigned int x)
{
	unsigned int mask = 1;		//mask = 0000...01
	int count = 0;		//counter for bit 1
	while (x != 0)	
	{
		if (mask & x)		//if bit in mask and bit in x is 1
			count++;	
		x >>= 1;		//move x 1 bit to right 
	}
	return count;   //return the number of 1 bits in x
}



void Bin_Print(unsigned int x)
{
	unsigned int mask = 1;		//mask = 000...01
	int length = sizeof(unsigned int) * 8;	//length = 32 for arr
	int arr[sizeof(unsigned int) * 8];		//arr[32]
	int i;
	for (i = length-1; i >= 0; i--)
	{
		arr[i] = mask&x;		//save 1 or 0 in arr[i]
		x >>= 1;		//move x 1 bit to right 
	}
	for (i = 0; i < length; i++)
		printf("%d", arr[i]);		//print the arr
	printf("\n");
}
