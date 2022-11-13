#include<stdio.h>
#include<stdlib.h>


void set_2d(float** a, int m, int n);
void print_2d(float** a, int m, int n);

int main( )
{
	int m, n, i;
	float** a;
	printf("\nenter m and n, for m*n array: \n");
	scanf("%d %d", &m, &n);   
	
	set_2d(a,m,n);
        print_2d(a,m,n);

        return 0;   
}

