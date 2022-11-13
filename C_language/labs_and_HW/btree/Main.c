#include "Header.h"

//specific functions implementation
void* cmp_int(void *data1, void *data2)
{
	if ((*(int*)data1) > (*(int*)data2)) return 1;
	else if ((*(int*)data1) < (*(int*)data2)) return -1;
	else return 0;
}
void* cmp_string(void *data1, void *data2)
{
	if (strcmp((char*)data1, (char*)data2) > 0) return 1;
	else if (strcmp((char*)data1, (char*)data2) < 0) return -1;
	else return 0;
}
void* input_int(void *data)
{
	int k = 0;
	if ((data = calloc(1, sizeof(int))) != NULL) {
		printf("Please input an integer number as a key: ");
		while (k == 0) {
			if (scanf("%d", data) > 0) k = 1;
			else {
				while (getchar() != '\n');
				printf("Invalid input, repeat\nPlease input an integer number as a key: ");
			}
		}
	}
	else Error_Msg("Error: Can't allocate memory");
	return data;
}
void* input_string(void *data)
{
	char string[255];
	printf("Please input a string as a key: ");
	scanf("%s", string);
	data = (char*)malloc(strlen(string) + 1);
	strcpy(data, string);
	return data;
}
void output_int(void *data)
{
	printf("%d ", (*(int*)data));
}
void output_string(void *data)
{
	printf("%s ", (char*)data);
}
void Error_Msg(char* str)
{
	printf("%s", str); //output message
	system("pause"); //wait
	exit(1); //terminate program
}

int main()
{
	pTreeADT *tree = NULL; //pointer to our manager
	pTreeNode *temp = NULL; //tree helper
	int o, s;
	do {
		printf("1: Int\n2:String\nChoose please type of data: ");
		scanf("%d", &o); //chosing data type and creating tree
		if (o == 1) tree = CreateTree(cmp_int, input_int, output_int);
		else if (o == 2) tree = CreateTree(cmp_string, input_string, output_string);
		else {
			printf("Incorrect input, please repeat.\n");
			getchar();
		}
	} while (o != 1 && o != 2);
	do {
		printf("1: Add keys to tree\n");
		printf("2: Print tree in ascending order\n");
		printf("3: Count height of tree till given key\n");
		printf("4: Searching and output max. key\n");
		printf("5: Output K-biggest nodes in decreasing order\n");
		printf("0: Exit.\n");
		printf("Choose option: ");
		if (scanf("%d", &s) > 0) {
				switch (s) {
				case 1: tree = AddKeys(tree, temp, NULL); break;
				case 2: inorderPrint(tree, temp); break;
				case 3: printf("Height of sub-tree with given key is %d\n", CountHeight(tree, temp, NULL)); break;
				case 4: LFMax(tree, temp); break;
				case 5: printKmax(tree, temp, NULL); break;
				case 0: printf("Have a nice day!\n"); break;
				default: printf("Invalid input, please repeat.\n");
				}
			}
		else {
			printf("Invalid input, please repeat.\n");
			getchar();
		}
	} while (s != 0);
	free_treemanager(tree); //send to free
	system("pause");
	return 0;
}