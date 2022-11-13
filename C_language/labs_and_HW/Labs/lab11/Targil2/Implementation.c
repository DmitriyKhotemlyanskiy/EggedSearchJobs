#include "Header.h"


int Do_It(void *sum, void** array, void(*p_Init)(void *), void(*p_Sum)(void*, void*), void(*p_Sub)(void*, void*), int(*p_Comp)(void*, void*))
{
	int i;
	p_Sum(sum, array[0]);  //initialazing of first two elements of the array
	p_Sub(sum, array[1]);
	for (i = 2; i < N; i++)	 
	{
		if (i == 2)  //this is the point we start checking
		{
			if (p_Comp(sum, array[i]) == 1)	//if p_Comp returns 1, we found the answer
				return 1;
		}
		else {
			if ((i % 2) == 0)  //even index in the array
				p_Sub(sum, array[i - 1]);	//substruction
			if ((i % 2) == 1)	//odd index in the array
				p_Sum(sum, array[i - 1]); //sum
			if (p_Comp(sum, array[i]) == 1)	//compares sum with the element, if the value returned is 1 then we found the answer
				return 1;  
		}
	}
	return 0;
}
