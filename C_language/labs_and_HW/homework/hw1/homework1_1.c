#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define X 10 

typedef struct fraction
{
	int mone, mehane;
}fraction;

void Enter_fraction(fraction *arr, int length);//gets the input and prints it if you've entered 9 fractions or 0 0.
int calc_fraction(fraction *arr, int length);//calculates the common denominator by multiplyingthe input deniminators,
//and sums up the numerators
int gcd(int a, int b);//greatest common divisor,swapps between the larger numbers the get into the function and
//finds the remainder
void main()
{
	fraction frac_arr[X];
	printf("Enter fractions (max 9) by pairs of integers (0 0 to finish):\n");
	Enter_fraction(frac_arr, X);
	calc_fraction(frac_arr, X);
	printf("");
	system("pause");
}

void Enter_fraction(fraction *arr, int length)
{
	int i = 0;
	do {
		
			printf("%d (mone mehane): ", i + 1);
			scanf("%d%d", &arr[i].mone, &arr[i].mehane);
			if (arr[i].mone != 0 && arr[i].mehane == 0)
			{
				while (arr[i].mone != 0 && arr[i].mehane == 0)
				{
					printf("\nError! Mehane can't be zero! Please, repeat: \n");
					printf("%d (mone mehane): ", i + 1);
					scanf("%d%d", &arr[i].mone, &arr[i].mehane);
				}
			}
		i++;
		if (i == 9) break;
	} while (arr[i - 1].mone != 0 || arr[i - 1].mehane != 0);
	i = 1;
	while (arr[i - 1].mone != 0 || arr[i - 1].mehane != 0)
	{
		printf("%d/%d", arr[i - 1].mone, arr[i - 1].mehane);
		
		if (i < 9)
		{
			if (arr[i].mone != 0 || arr[i].mehane != 0)
				printf(" + ");
			else
				printf(" = ");
		}
		else
			printf(" = ");
		i++;
		if (i > 9) break;
	}
}
int calc_fraction(fraction *arr, int length)
{
	int i = 1, a;
	fraction sum;
	sum.mehane = arr[0].mehane;
	sum.mone = 0;
	while (arr[i].mone != 0 || arr[i].mehane != 0)
	{
		sum.mehane *= arr[i].mehane;//finds the common denominator
		i++;
		if (i == 9) break;
	}

	i = 0;
	while (arr[i].mone != 0 || arr[i].mehane != 0)
	{

		sum.mone += (sum.mehane / arr[i].mehane)*arr[i].mone;//sums up the numerator after we've calculated the denominator
		i++;
		if (i == 9) break;

	}
	a = gcd(sum.mone, sum.mehane);
	sum.mone /= a;
	sum.mehane /= a;
	printf("%d/%d", sum.mone, sum.mehane);
	printf(" = %d AND %d/%d\n", sum.mone / sum.mehane, sum.mone%sum.mehane, sum.mehane);
}
int gcd(int a, int b)
{
	int temp = 1, c;
	while (temp != 0) {
		if (b > a)//finds the larger number and swapps them
		{
			c = a;
			a = b;
			b = c;
		}
		else {
			temp = a % b;
			a = b;
			b = temp;
		}
	}
	return a;
}
