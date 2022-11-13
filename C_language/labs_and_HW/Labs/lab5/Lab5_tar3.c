#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

unsigned char check_ms(unsigned char a);
unsigned char change_bit(unsigned char a, int num);
void BinPrint(unsigned char ch);

int main()
{
	unsigned char num1 = 102, num2 = 58;
	int n;

	printf("\nThe first part :");
	printf("\nThe number is %d   ", num1);
	BinPrint(num1);
	num1 = check_ms(num1);
	printf("\nThe new number is: %d   ", num1);
	BinPrint(num1);

	printf("\n\nThe second part :");
	printf("\nThe number is %d   ", num2);
	BinPrint(num2);
	printf("\nEnter a number of the bit to change(1-8)");
	scanf("%d", &n);
	num2 = change_bit(num2, n);
	printf("\nThe new number is: %d   ", num2);
	BinPrint(num2);     /*Binary representation of number*/
	system("pause");
	return 0;
}



void BinPrint(unsigned char ch)
{
	unsigned char mask = 1;   //mask = 00000001
	int length = sizeof(unsigned char) * 8;		//length  = 8
	int arr[sizeof(unsigned char) * 8];		//arr[8]
	int i;
	for (i = length - 1; i >= 0; i--)		
	{
		arr[i] = mask&ch; //save 1 or 0 in arr[i]
		ch >>= 1;		//move ch 1 bit to right
	}
	for (i = 0; i < length; i++)	
		printf("%d", arr[i]);	//print the arr
	printf("\n");
}
unsigned char check_ms(unsigned char a)
{
	unsigned char mask = 1;		//mask = 00000001
		mask <<= sizeof(unsigned char)*8-1;  //move "00000001" 7 bits to left -> "10000000"
	a |= mask;   //a = a OR mask
	return a; 
}
unsigned char change_bit(unsigned char a, int num)
{
	unsigned char mask = 1;
	mask <<= sizeof(unsigned char) * 8 - num; //move "00000001" (8-num) bits to left
	a ^= mask;		// a = a XOR mask
	return a;
}