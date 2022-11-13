#include "Header.h"

void main()
{
	Stack St;
	St.head = NULL;
	St.size = 0;
	int i,del_val;
	int Arr[] = { 1,5,3,7,4,10,9 };
	for (i = 0; i < 7; i++)
	{
		Push(&St, Arr[i]);
	}
	Pop(&St, &del_val);
	printf("\nDel_val = %d", del_val);
	Push(&St, Arr[5]);
	Push(&St, Arr[6]);
	while (Pop(&St, &del_val))
	{
		printf("\nDel_val = %d", del_val);
	}
	printf("\n");
	system("pause");

}