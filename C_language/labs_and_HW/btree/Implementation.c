#include "Header.h"

//structs definitions//
typedef struct TreeNode {	//struct of nodes
	void *key;
	struct Tree *left, *right;
} TreeNode;

typedef struct TreeADT { //main struct with root pointer and functions pointers
	struct TreeNode *root;
	/*pointers to functions*/
	void*(*compare)(void*, void*);
	void*(*input)(void*);
	void(*output)(void*);
} TreeADT;

//functions implementations//
pTreeADT CreateTree(void *cmp(void), void *input(void), void *output(void))
{
	TreeADT* temp = (TreeADT*)malloc(sizeof(TreeADT)); //memory allocation
	if (!temp) Error_Msg("Error: Memory Allocation could not be completed.\n"); //check
	else {
		temp->root = NULL; //make root null
		temp->compare = cmp; //save compare function pointer
		temp->input = input; //save input function pointer
		temp->output = output; //save output function pointer
		return temp;
	}
}

pTreeNode CreateNode(void *key)
{
	pTreeNode temp;
	temp = (TreeNode*)malloc(sizeof(TreeNode)); //memory allocation
	if (!temp) Error_Msg("Error: Memory Allocation could not be completed.\n"); //check
	else { //set left and right null, save the key
		temp->left = NULL;
		temp->right = NULL;
		temp->key = key;
		return temp;
	}
}

pTreeADT AddKeys(pTreeADT PTree, pTreeNode temp, void* key)
{
	void* cmp; //for results of compare function
	int k = 0; //flag
	if (key == NULL) { //if key was null so...
		key = PTree->input(key); //ask to input key
		if (PTree->root == NULL) { //if there's no tree
			PTree->root = CreateNode(key); //save key to root
			k = 1; //make flag = 1
		}
		temp = PTree->root;//put root to temp
	}
	if (k == 0) { //check flag
		if (temp) { //if temp is exist
			cmp = PTree->compare(key, temp->key); //send key's to compare and check results
			if ((int)cmp == -1) temp->left = (pTreeNode)AddKeys(PTree, temp->left, key);
			else if ((int)cmp == 1) temp->right = (pTreeNode)AddKeys(PTree, temp->right, key);
			else if ((int)cmp == 0) printf("Node with this key already exist.\n");
		}
		else temp = CreateNode(key); //if key wasn't found, create node with this key
	}
	if (PTree->root != temp) return temp; //return temp only if it's not equal to root (for recursion)
	else { //otherway save temp to root, and return pointer to manager
		PTree->root = temp;
		return PTree;
	}
}

void inorderPrint(pTreeADT PTree, pTreeNode temp)
{
	if (!temp) temp = PTree->root; //if temp not yet exist
	if (temp) { //else* if exist
		if (temp->left) inorderPrint(PTree, temp->left); //if left exist send first
		PTree->output(temp->key); //print "root" of sub-tree
		if (temp->right) inorderPrint(PTree, temp->right); //if right exist send then
	}
	else printf("There's no tree.\n"); //if temp still doesn't exist
	if (PTree->root != temp) return; //compare root and temp and go back
	printf("\n-=-=-=-=-=-Tree is printed inorder.-=-=-=-=-=-\n");
}

void* CountHeight(pTreeADT PTree, pTreeNode temp, void* key)
{
	void *cmp;
	int height_l = 0, height_r = 0, height_m = 0;
	if (!temp && !key) { //if not exist
		key = PTree->input(&key); //input key
		if (PTree->root) { //if root exist
			temp = PTree->root;
			do { //search node with given key
				cmp = PTree->compare(key, temp->key); //compare keys
				if (((int)cmp == -1)) temp = temp->left; //move left
				if (((int)cmp == 1)) temp = temp->right; //move right
			} while (temp && (int)cmp != 0);
		}
		else return -1; //if tree is empty
	}
	if (temp) { //if temp exist
		if (temp->left) height_l = (int)CountHeight(PTree, temp->left, key);
		else height_l = -1;
		if (temp->right) height_r = (int)CountHeight(PTree, temp->right, key);
		else height_r = -1;
		if (height_l >= height_r) height_m = height_l;
		else height_m = height_r;
		return (1 + height_m);
	}
	else return 0;
}

void LFMax(pTreeADT PTree, pTreeNode temp)
{
	if (PTree->root) { //if tree exist
		temp = PTree->root; //copy root to temp
		printf("Maximal key tree is: ");
		while (temp) { //while temp exist
			if (temp->right) temp = temp->right; //move right if exist
			else { //else output node
				PTree->output(temp->key);
				temp = NULL; //make temp null
			}
		}
	}
	else printf("Tree does not exist.\n");
	printf("\n");
}

void* printKmax(pTreeADT PTree, pTreeNode temp, int k)
{
	if (!temp && !k) { //if k is null
		printf("Please input how much max. nodes you wanna see? ");
		scanf("%d", &k); //input k
		temp = PTree->root;//if temp doesn't exist copy root to temp
	}
	if (temp) {
		if (temp->right && k > 0) k = (int)printKmax(PTree, temp->right, k);
		if (k > 0) {
			PTree->output(temp->key);
			k--;
		}
		if (temp->left && k > 0) k = (int)printKmax(PTree, temp->left, k);
		if (PTree->root != temp) return k;
	}
	else printf("Tree doesn't exist\n");
	printf("\n-=-=-=-=-=-Tree is printed inorder.-=-=-=-=-=-\n");
}

void free_treenodes(pTreeNode temp)
{
	if (temp->left) free_treenodes(temp->left); //move left
	if (temp->right) free_treenodes(temp->right); //move right
	free(temp); //free temp
}

void free_treemanager(pTreeADT PTree)
{
	free_treenodes(PTree->root); //send root to free
	free(PTree); //free manager
}