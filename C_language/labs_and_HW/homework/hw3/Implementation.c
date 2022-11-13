#include "Header.h"
//The function gets a double pointer in order to work on the original address and we add a node to the end of the list
void CreateProducts(KitList **head, KitList **tail, char *Name, int Quant, int Price, char *Prem)
{
	KitList *temp = NULL;
	temp = (KitList*)malloc(sizeof(KitList));
	if (!temp) {
		printf("\nAllocation memory error!");
		del_Kitlist(*head);
		return;
	}
	temp->next = NULL;
	temp->prev = NULL;
	temp->Mana = (KitItem*)malloc(sizeof(KitItem));
	if (!temp->Mana) {
		printf("\nAllocation memory error!");
		del_Kitlist(*head);
		return;
	}
	temp->Mana->Name = (char*)malloc((strlen(Name) + 1));
	if (!temp->Mana->Name) {
		printf("\nAllocation memory error!");
		del_Kitlist(*head);
		return;
	}
	strcpy(temp->Mana->Name, Name);
	temp->Mana->Stock = Quant;
	temp->Mana->Price = Price;
	strcpy(temp->Mana->Prem, Prem);
	if (*head == NULL)
		*head = *tail = temp;
	else
	{
		(*tail)->next = temp;
		temp->prev = *tail;
		*tail = (*tail)->next;
	}
}
void AddItems(KitList *head, char *PName, int Quantity)
{
	KitList *temp = head;
	while (temp)
	{
		if (!strcmp(temp->Mana->Name, PName))
		{
			temp->Mana->Stock += Quantity;
			return;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("\nThere is no such product");
	}
}
void del_Tablist(TabList *Array, int Length)
{
	int i=1;
	while ((i - 1) < Length) {
		if (Array[i - 1].Mana != NULL)
			RemoveTable(i, Array);
		i++;
	}
	printf("\nThe Table List was deleted successfully!\n");
}
int del_Kitlist(KitList *head)
{
	KitList *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->Mana->Name);
		free(temp->Mana);
		free(temp);
	}
	if (head == NULL) {
		printf("\nThe Kitchen List was deleted successfully!");
		return 1;
	}
	else
	{
		printf("\nError deleting Kitchen List!\n");
		system("pause");
		return 0;
	}
}
TabList* MallocNumOfTables(int a, TabList *parr)
{
	int i;
	parr = (TabList*)malloc(a * sizeof(TabList));
	if (!parr) {
		printf("\nError Allocating Table Array\n");
		return NULL;
	}
	for (i = 0; i < a; i++) {
		parr[i].Mana = NULL;
		parr[i].Bill = 0;
		parr[i].next = NULL;
	}
	return parr;
}
int OrderItem(int Num, char *Name, int Q, TabList *arr, KitList *head)
{
	TabList *temp,*temp_arr = NULL;
	while (head != NULL)
	{
		if (!strcmp(Name, head->Mana->Name))
		{
			if (Q <= head->Mana->Stock)
			{
				temp = malloc(sizeof(TabList));
				if (!temp) {
					printf("\nError Allocating memory for temp");
					RemoveTable(Num, arr);
					return 0;
				}
				temp->Mana = (KitItem*)malloc(sizeof(KitItem));
				if (!temp->Mana)
				{
					printf("\nError allocating memory!!\n");
					exit(1);
				}
				if (!(temp->Mana->Name = (char*)malloc(strlen(Name) + 1))) {
					printf("\nError allocating for Name");
					RemoveTable(Num, arr);
					return 0;
				}
				strcpy(temp->Mana->Name, Name);
				temp->Mana->Stock = Q;
				temp->Mana->Price = head->Mana->Price;
				strcpy(temp->Mana->Prem, head->Mana->Prem);
				head->Mana->Stock -= Q;
				temp_arr = &arr[Num-1];
				if ((*temp_arr).Bill == 0)
				{
					(*temp_arr) = *temp;
					(*temp_arr).next = NULL;
					(*temp_arr).Bill = Q*temp->Mana->Price;
					return 1;
				}
				else {
					while ((*temp_arr).next != NULL)
						temp_arr = (*temp_arr).next;
					(*temp_arr).next = temp;
					temp_arr = (*temp_arr).next;
					(*temp_arr).next = NULL;
					(*temp_arr).Bill = Q*temp->Mana->Price;
					return 1;
				}
			}
			else {
				printf("\nSorry, out of stock");
				return 0;
			}
		}
		head = head->next;
	}
	printf("\nWe don't serve any %s , sorry.\n", Name);
	return 0;
}
void RemoveItem(int TableNumber, char* ProductName, int Quantity, TabList* Table)
{
TabList* TableHead = &Table[TableNumber - 1];
int flag = 0;
if (Quantity < 0)
{
	printf("\nYou can't cancel a nagative number of items!");
	return;
}
	if (!(TableHead))
		printf("\nNo active order exists");
	while (TableHead)
	{
		if (strcmp(ProductName, TableHead->Mana->Name) == 0)
		{
			if (Quantity > TableHead->Mana->Stock) {
				printf("\nThe amount of items canceled is bigger than the number of items ordered.");
				return;
			}
			else {
				flag = 1;
				TableHead->Mana->Stock -= Quantity;
				TableHead->Bill -= (TableHead->Mana->Price * Quantity);
				if (TableHead->Bill == 0)
					RemoveTable(TableNumber, Table);
				return;
			}
		}
			printf("\n%d of the product [%s] was successfully deleted\n", Quantity, ProductName);
	TableHead = TableHead->next;
	}
	if (flag== 0)
		printf("\nThis product was not ordered by this table");
}
void RemoveTable(int Num_of_Table, TabList *arr)
{
	TabList *temp = &arr[Num_of_Table - 1], *del_table;
	int sum_to_pay = 0, i = 1;
	if (arr[Num_of_Table - 1].Mana != NULL) {
		while (temp != NULL)
		{
			printf("\n[%d]-> %s amount = %d price = %d "
				"premium->(%s)", i, temp->Mana->Name, (temp->Bill / temp->Mana->Price), temp->Mana->Price, temp->Mana->Prem);
			sum_to_pay += temp->Bill;
			temp = temp->next;
			i++;
		}
		if (Prem_or_Not(&arr[Num_of_Table - 1]))
			printf("\n----Your bill is: %.2f", ((float)sum_to_pay * 1.15));
		else
			printf("\n----Your bill is: %d", sum_to_pay);
		printf("\nTHANK YOU, COME AGAIN :)");
		temp = &arr[Num_of_Table - 1];
		while (temp != NULL)
		{
			del_table = temp;
			temp = temp->next;
			free(del_table->Mana->Name);
			free(del_table->Mana);
		}
		arr[Num_of_Table - 1].Mana = NULL;
		arr[Num_of_Table - 1].next = NULL;
		arr[Num_of_Table - 1].Bill = 0;
		if (temp == NULL)
			printf("\nThe table number %d was removed successfully!\n", Num_of_Table);
	}
	else printf("\n SORRY! There is no such table.");
}
int Prem_or_Not(TabList *Table)
{
	int count_of_prem = 0;
	TabList *temp = Table;
	while (temp != NULL)
	{
		if ((int)temp->Mana->Prem[0] == 89)
			count_of_prem++;
		temp = temp->next;
	}
	if (count_of_prem > 0)
		return 1;
	return 0;
}
int Report(TabList *arr, KitList *head, int NumOfTable)
{
	TabList *temp_tab = &arr[NumOfTable-1];
	KitList *temp_kit = head;
	if (NumOfTable == 0)
	{
		printf("\nShowning the exsisting stock:");
		while (temp_kit != NULL)
		{
			printf("\nProduct Name is: %s, the stock is: %d, it's price is: %d, "
				"is it a premium? [%s]", temp_kit->Mana->Name, temp_kit->Mana->Stock, temp_kit->Mana->Price, temp_kit->Mana->Prem);
			temp_kit = temp_kit->next;
		}
	}
	if (NumOfTable != 0)
	{
		printf("\nShownig table report:");
		if (temp_tab->Bill == 0)
		{
			printf("\nThis table has not made an order yet");
			return;
		}
		while (temp_tab != NULL)
		{
			printf("\nProduct Name is: %s, the order amount is: %d", temp_tab->Mana->Name, temp_tab->Mana->Stock);
			temp_tab = temp_tab->next;
		}
		if (&arr[NumOfTable-1] == NULL)
			printf("\nThe table is not occupied");
	}
}