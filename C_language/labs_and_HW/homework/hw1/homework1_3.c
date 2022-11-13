#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

typedef struct Clock
{
	int hour, minute;
}clock_t;

clock_t watch(clock_t a, int b);//function that gets clock struct and the added time, 
								//takes the added time divides it by 60 and adds the right amountof time to the hours section and the minutes section
void main()
{
	clock_t zman;
	int add;
	printf("Enter time and minutes to add: ");
	scanf("%d%d%d", &zman.hour, &zman.minute, &add);
	if (zman.hour > 23 || zman.minute > 59)
	{
		while (zman.hour > 23 || zman.minute > 59)  //check if the input is right
		{
			printf("\nYour input is wrong!!! Please, repeat it: =)\n");
			printf("Enter time and minutes to add: ");
			scanf("%d%d%d", &zman.hour, &zman.minute, &add);
		}
	}
	printf("\nThe time is: %.2d:%.2d", zman.hour, zman.minute);
	zman = watch(zman, add);
	printf("\nThe new time is: %.2d:%.2d\n", zman.hour, zman.minute);
	system("pause");
}
clock_t watch(clock_t a, int b)
{
	clock_t new_time;
	int add_H, add_M;
	new_time.hour = a.hour;
	new_time.minute = a.minute;

	add_H = b / 60;//gets the amount of hours.
	add_M = b % 60;//gets the amount of minutes.

	new_time.hour += add_H;
	new_time.minute += add_M;
	if (new_time.minute > 59)//if the added minutes are more that 59 then add 1 to the hour section.
	{
		new_time.minute -= 60;
		new_time.hour++;
	}
	if (new_time.hour > 23)//so we wont get 24 25 and etc.
		new_time.hour -= 24;

	return new_time;
}
