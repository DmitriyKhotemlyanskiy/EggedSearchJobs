#include "Header.h"
//definition of the specific functions in the main file
void Int_Sum(void *sum, void *num) //specific function Int_Sum
{
	*(int*)sum += *(int*)num;
}

void Int_Sub(void *sum, void *num)	//specific function Int_Sub
{
	*(int*)sum -= *(int*)num;
}

int Int_Comp(void *a, void *b)	//specific function Int_Comp
{
	if (*(int*)a == *(int*)b)
		return 1;
	return 0;
}

void Init(void *p)	//specific function Init
{
	*(int*)p = 0;
}

int main()
{
	int num[] = { 5,8,23,20,23 }, i, answer;
	void *p_num[N];
	for (i = 0; i < N; i++) //in order to point to the elements of the num[] array we have to do it with the loop
	{
		p_num[i] = &num[i];
	}
	Init(&answer);  //sending "answer" for initializing
	answer = Do_It(&answer, p_num, Init, Int_Sum, Int_Sub, Int_Comp);
	if (answer == 1)
		printf("The answer is 'Yes'\n");
	else
		printf("The answer is 'No'\n");
	system("pause");
	return 0;
	
}
