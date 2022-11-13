#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<math.h>

float func1(int x);
float func2(int x);
double sum_square(int m, int n, float(*f)(int a));
void main()		//main for cheching the functions
{
	printf("The sum of func2: %.5fl\n", sum_square(2, 13, func2));
	printf("The sum of func1: %.5fl\n", sum_square(1, 10000, func1));
	_getch();
}

float func1(int x)
{
	return (float) (1.0 / x);
}
float func2(int x)
{
	return (float) (x / 5.0);
}
double sum_square(int m, int n, float(*f)(int a))
{
	int i, j;
	double sum=0;	
	for (i = m; i <= n; i++)
	{
		sum += pow(f(i),2); //sum = sum + pow(returned value from function (*f),2)
	}
	return sum;
}