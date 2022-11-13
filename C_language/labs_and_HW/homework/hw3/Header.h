#define _CRT_SECURE_NO_WARNINGS
#ifndef _Implementation
#define _Implementation
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
typedef struct KitItem
{
	char *Name;
	int Price;
	int Stock;
	char Prem[2];

}KitItem;
typedef struct TabList
{
	KitItem *Mana;
	struct TabList *next;
	int Bill;

}TabList;
typedef struct KitList
{
	KitItem *Mana;
	struct KitList *next, *prev;
}KitList;
//The function creates a new node that contains the kitchen list, we allocate memory for it and get the data from the file to the list
void CreateProducts(KitList **head, KitList **tail, char *Name, int Quant, int Price, char *Prem);
//The function adds items to the kitchen stock through the Kitchen List. We get data from the Instructions file
void AddItems(KitList *head, char *PName, int Quantity);
//We created this function in order to delete the List whenever a wrong memory access happens or whenever we get to the end of the file
int del_Kitlist(KitList *head);
//We created this function in order to delete the List whenever a wrong memory access happens or whenever we get to the end of the file
void del_Tablist(TabList *Array, int Length);
//The function allocates some memory to the Table Array
TabList* MallocNumOfTables(int a, TabList *parr);
//The function create a new node that contains the table list. We get to the relevant index of the array and we update the list with items
int OrderItem(int Num, char *Name, int Q, TabList *arr, KitList *head);
//The function works with the list of the table and it deletes requested items from that list
void RemoveItem(int TableNumber, char* ProductName, int Quantity, TabList* Table);
//The function prints the requested order summary to the user
int Report(TabList *arr, KitList *head, int NumOfTable);
//The function removes a tabel the array, but beforehand it prints the accumulated bill
void RemoveTable(int Num_of_Table, TabList *arr);
//Checks whether the dish is premium or not. Returns 1 if it is Premium, else returns 0
int Prem_or_Not(TabList *Table);
#endif