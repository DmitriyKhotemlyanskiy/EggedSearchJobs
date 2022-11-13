#include "Header.h"

void main()
{
	char ch = 0,cha='y', op = 0, RepOp = 0 , Name[20], Premium[2];
	int p_num = 0;
	int MnumT = 0, TableNumber, Quant;
	KitList *head = NULL, *tail = NULL;
	TabList *arr = NULL;
	FILE *Inst = NULL, *Manot = NULL;
	printf("Enter the number of tables: ");
	scanf("%d", &MnumT);
	if (!(arr = MallocNumOfTables(MnumT, arr))) {
		printf("\nError allicating memory to Array");
		exit(1);
	}
	Inst = fopen("Instructions.txt", "r");
	if (Inst == NULL)
	{
		printf("ERROR opening the file");
		free(arr);
		exit(1);
	}
	Manot = fopen("Manot.txt", "a+");
	if (Manot == NULL)
	{
		printf("\nERROR opening the file");
		fclose(Inst);
		free(arr);
		exit(1);
	}
	while (cha == 'y' || cha == 'Y')
	{
		printf("Enter '0' in order to start your order\n");
		ch = _getch();
		if (ch == '0') {
			system("cls");
			printf("What else do you want to do?\n");
			printf("(1). Kitchen dishes input.\n");
			printf("(2). Add to an existing dish stock in the kitchen\n");
			printf("(3). Dish orders to a table\n");
			printf("(4). Order canceling\n");
			printf("(5). Close a table\n");
			printf("(6). Print a report\n\n");
			op = fgetc(Inst);
			switch (op)
			{
			case '1':
				while ((fscanf(Manot, "%s", Name)) != EOF)
				{
					fscanf(Manot, "%d %d %s", &Quant, &TableNumber, Premium);
					CreateProducts(&head, &tail, Name, Quant, TableNumber, Premium);
				}
				fclose(Manot);
				break;
			case '2':
				fscanf(Inst, "%s %d", Name, &p_num);
				if (p_num < 0)
				{
					printf("\nError: A negative nubmer was enterd");
					break;
				}
				AddItems(head, Name, p_num);
				break;
			case '3':
				fscanf(Inst, "%d", &TableNumber);
				if (TableNumber > MnumT)
				{
					printf("\nError: The table number has to be lower than %d", MnumT);
					break;
				}
				fscanf(Inst, "%s %d", Name, &Quant);
				if (TableNumber > MnumT)
				{
					printf("\nError: The table number has to be lower than %d", MnumT);
					break;
				}
				if (Quant < 0) {
					printf("\nError: You can't order a negative amount");
					break;
				}
				if (!OrderItem(TableNumber, Name, Quant, arr, head))
				{
					printf("\nError: The order has not been added to the table %d",TableNumber);
					break;
				}
				printf("\nOrder #3 was done");
				break;
			case '4':
				fscanf(Inst, "%d %s %d", &TableNumber, Name, &Quant);
				if (TableNumber > MnumT)
				{
					printf("\nError: The table number has to be lower than %d", MnumT);
					break;
				}
				RemoveItem(TableNumber, Name, Quant, arr);
				break;
			case '5':
				fscanf(Inst, "%d", &TableNumber);
				if (TableNumber > MnumT)
				{
					printf("\nError: The table number has to be lower than %d", MnumT);
					break;
				}
				RemoveTable(TableNumber, arr);
				break;
			case '6':
				fseek(Inst, 1, 1);
				RepOp = fgetc(Inst);
				if (RepOp == 'A') {
					fseek(Inst, 5, 1);
					Report(arr, head, 0);
				}
				if (RepOp == 'B') {
					fscanf(Inst,"%d", &TableNumber);
					Report(arr, head, TableNumber);
				}
				break;
			default:
				printf("\nInput Error\n");
			}
			printf("\nDo you want to continue? (y/n):");
			cha = _getch();
			if (cha == 'n' || cha == 'N') {
				printf("\nBye Bye");
				break;
			}
			 if (cha != 'y' && cha != 'Y') {
				 printf("\nInput Error Please Try Again");
				 printf("\nIt seems that you want to exit the program, Do you want to continue ? (y / n) : ");
				 cha = _getch();
			}
			if (feof(Inst)) {
				printf("\nEnd of Instruction file\nThe program will be closed.");
				break;
			}
			fseek(Inst, 2, 1);  // in order to read the correct option number we jump above a letter and then we go to a new line
			system("cls");
		}
	}
	del_Kitlist(head);
	del_Tablist(arr,MnumT);
	free(arr);
	fclose(Inst);
	system("pause");
}