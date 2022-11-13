#ifndef _Header
#define _Header
//libraries//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//struct pointers//
typedef struct TreeNode* pTreeNode;
typedef struct TreeADT* pTreeADT;
//general functions definitions//
/*--input functions--*/
void* input_int(void *data, void* str);
void* input_string(void *data, void* str);
/*--compare functions--*/
void* cmp_int(void *data1, void *data2);
void* cmp_string(void *data1, void *data2);
/*--output functions--*/
void output_int(void *data);
void output_string(void *data);
/*--other functions--*/
void Error_Msg(char* str);
pTreeADT AddKeys(pTreeADT PTree, pTreeNode temp, void *key);
pTreeADT CreateTree(void *cmp(void), void *input(void), void *output(void));
pTreeNode CreateNode(void *key);
void inorderPrint(pTreeADT PTree, pTreeNode temp);
void* CountHeight(pTreeADT PTree, pTreeNode temp);
void LFMax(pTreeADT PTree, pTreeNode temp);
void* printKmax(pTreeADT PTree, pTreeNode temp, int k);
void free_treenodes(pTreeNode temp);
void free_treemanager(pTreeADT PTree);
#endif // !_Header