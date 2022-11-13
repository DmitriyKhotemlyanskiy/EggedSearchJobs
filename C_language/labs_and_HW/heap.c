#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define LENGTH 10

void Heapify_Down(float* arr, int i, int length);
void Build_Heap(float* arr, int length);
void Exchange(float* arr, int i, int j);
float DelMin(float* arr, int *len);
void main() {
	float arr[LENGTH] = { 0 };
	int i;
	printf("Please, enter 10 float numbers to your array:");
	for (i = 0; i < LENGTH; i++)
		scanf_s("%f", &arr[i]);
	system("cls");
	printf("Your array is:\n");
	for (i = 0; i < LENGTH; i++)
		printf("%.2f ", arr[i]);
	Build_Heap(arr, LENGTH);
	printf("\n\nBuilded heap:\n");
	for (i = 0; i < LENGTH; i++)
		printf("%.2f ", arr[i]);
	printf("\n");
	system("pause");

	printf("\n\nHeap sorting:\n");
	int len = LENGTH - 1;
	for (i = 0; i < LENGTH; i++)
		printf("%.2f ", DelMin(arr, &len));
	printf("\n");
	system("pause");
}

void Build_Heap(float* arr, int length) {
	int i;
	for (i = LENGTH / 2; i >= 0; i--)
		Heapify_Down(arr, i, LENGTH);
}

void Heapify_Down(float* arr, int i, int length) {
	int l, r, smallest;
	if (i == 0) i++;
	l = 2 * i;
	r = 2 * i + 1;
	smallest = i;
	l--; r--; i--; smallest--;
	if ((l < length) && (arr[l] < arr[i])) smallest = l;
	if ((r < length) && (arr[r] < arr[smallest])) smallest = r;
	if (smallest != i)
	{
		Exchange(arr, i, smallest);
		Heapify_Down(arr, smallest + 1, length);
	}
}

void Exchange(float* arr, int i, int j)
{
	float temp_val = arr[i];  //temporarily stores the value
	arr[i] = arr[j];	//swaps the values
	arr[j] = temp_val;
}

float DelMin(float* arr, int *len)
{
	float toRet = 0;
	toRet = arr[0];
	Exchange(arr, 0, *len);
	*len = *len - 1;
	Heapify_Down(arr, 0, *len);
	return toRet;
}