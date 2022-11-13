#define _CRT_SECURE_NO_WARNINGS
#ifndef _Implementation
#define _Implementation
#include<stdio.h>

#define N 5
//declaration of Do_It the general function 
int Do_It(void *sum, void** array, void(*p_Init)(void *), void(*p_Sum)(void*, void*), void(*p_Sub)(void*, void*), int(*p_Comp)(void*, void*));

#endif 