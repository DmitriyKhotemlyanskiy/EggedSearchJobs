#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

#define true 1
#define false 0

#define Max(a,b) ((a) > (b)? (a): (b)) 

typedef struct
{
	int key;
	float val;
} Data;

typedef struct TreeNode
{
	struct TreeNode *left;	 //left child
	struct TreeNode *right; //right child

	Data TreeNode_info;	 //info data in node
} TreeNode;

typedef struct ListNode
{
	struct ListNode * next;
	Data ListNode_info;	 //info data in node
} ListNode;


// TREE Handling prototypes
int treeHight(TreeNode *); // returns the hight of a given tree
float sum_tree(TreeNode *); //returns the sum of values on all tree nodes
void empty_tree(TreeNode **); // frees all the allocated memory and sets the root to NULL
TreeNode * create_tree_node(Data);
void insert_info_by_key(TreeNode **, TreeNode **, Data);
TreeNode * create_search_tree();

// LIST Handling prototypes
void empty_list(ListNode **);// frees all the allocated memory and sets the head to NULL
ListNode * create_list_node(Data);
void print_list(ListNode *);   // Prints the elements of the list from head to tail
ListNode * append_lists(ListNode *, ListNode *);

// LIST <-> TREE conversions
ListNode * tree_to_inorder_list(TreeNode *);
ListNode * tree_to_preorder_list(TreeNode *);


int main()
{
	TreeNode * inputTree = NULL;
	ListNode * preList = NULL, *inList = NULL;

	printf("\n getting the input tree");
	inputTree = create_search_tree(); // get the tree from user
	printf("\nhight of tree is %d\n", treeHight(inputTree)); // print hight
	printf("\nsum of values of tree is %f\n", sum_tree(inputTree));

	printf("\n printing input tree inorder");
	inList = tree_to_inorder_list(inputTree); // inorder traverse the tree
	print_list(inList);

	printf("\n printing input tree preorder");
	preList = tree_to_preorder_list(inputTree); // preorder traverse the tree
	print_list(preList);

	empty_tree(&inputTree);
	empty_list(&preList);
	empty_list(&inList);
	printf("\n");
	system("pause");
	return 0;
}

int treeHight(TreeNode * tree) // returns the hight of a given tree
{
	int HightLeft = -1;  //starting point
	int HightRight = -1;
	if (tree == NULL) return -1;  //if the tree still empty
	if (tree->left) HightLeft = treeHight(tree->left);  //if there is an option to advance to the left side 
	if (tree->right) HightRight = treeHight(tree->right); ////if there is an option to advance to the right side
	return (Max(HightLeft, HightRight)+1);  //returns the higher count of the nodes
}



float sum_tree(TreeNode * tree) //returns the sum of values on all tree nodes
{
	if (tree == NULL)
		return 0;
	return tree->TreeNode_info.val + sum_tree(tree->left) + sum_tree(tree->right);
}



void empty_tree(TreeNode **root)   // frees all the allocated memory and sets the root to NULL
{
	if (*root == NULL)  //if the tree is empty 
		return;
	if (&((*root)->left) != NULL)  //if there is an option to advence -> go left
		empty_tree(&((*root)->left));
	if (&((*root)->right) != NULL) //if there is an option to advence -> go right
		empty_tree(&((*root)->right));
	free(*root);  //free the node
	*root = NULL;
}



TreeNode * create_tree_node(Data data)  //the regular code of creating a node
{
	TreeNode *temp;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (!temp) {
		printf("\nAllocation memory error!");
		return false;
	}
	temp->TreeNode_info = data;
	temp->left = temp->right = NULL;
	return temp;
}




void insert_info_by_key(TreeNode ** root, TreeNode ** root_original, Data data)
{
	static int times;
	if (!(*root))
	{
		*root = create_tree_node(data);			//get new node for tree
		if (times == 0)
			*root_original = *root;
		if (*root == NULL)
		{
			printf("Allocation tree node failed");
			empty_tree(root_original);                    /*deleting the whole tree,since root_original is a pointer to the whole tree*/
			exit(1);
		}
	}
	else
	{
		if (data.key < (*root)->TreeNode_info.key)		//if the new node's key is smaller			
			insert_info_by_key(&((*root)->left), root_original, data); 	//call insert_node with the left child
		else
			insert_info_by_key(&((*root)->right), root_original, data);
	}
	times++;
}



TreeNode * create_search_tree()
{
	Data infoNode;
	char in_char;
	TreeNode * tree = NULL;

	do
	{
		printf("\n Do you want to enter another node? (y/n) :");
		in_char = _getche();
		if (in_char == 'y')
		{
			printf("\nEnter key and value: ");
			scanf("%d %f", &(infoNode.key), &(infoNode.val));
			insert_info_by_key(&tree, &tree, infoNode);     /*sending the same parameter twice for deleting a whole tree*/
		}
	} while (in_char == 'y');
	return tree;
}


void empty_list(ListNode ** head)   // frees all the allocated memory and sets the head to NULL
{
	if ((*head) == NULL)
		return;
	empty_list(&((*head)->next));
	free(*head);
	*head = NULL;
}


ListNode * create_list_node(Data data)
{
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));	//allocate new node in heap

	if (new_node == NULL)
		return NULL;
	else
	{
		new_node->ListNode_info = data;
		new_node->next = NULL;
		return new_node;									//returns intialized node
	}
}



void print_list(ListNode * head)
{
	if (head == NULL)
	{
		printf("\nThe list is EMPTY\n");
		return;
	}
	printf("\nThe list is:\n");
	while (head != NULL)
	{
		printf("\n (key=%d , val=%.01f)", head->ListNode_info.key, head->ListNode_info.val);
		head = head->next;
	}
	printf("\n\n");
}



ListNode * append_lists(ListNode * firstList, ListNode * secondList)
{
	ListNode * res;

	res = secondList;   /*if firstList is empty*/
	if (firstList)
	{
		res = firstList;
		while (firstList->next)
			firstList = firstList->next;
		firstList->next = secondList;
	}
	return res;
}


ListNode * tree_to_inorder_list(TreeNode * root)
{
	ListNode * curr = NULL, *left = NULL, *right = NULL;
	if (root)
	{
		left = tree_to_inorder_list(root->left);
		right = tree_to_inorder_list(root->right);
		curr = create_list_node(root->TreeNode_info);
		curr->next = right;
		left = append_lists(left, curr);
	}
	return left;
}

ListNode * tree_to_preorder_list(TreeNode * root)
{
	ListNode * curr = NULL, *left = NULL, *right = NULL;
	if (root)
	{
		left = tree_to_preorder_list(root->left);   
		right = tree_to_preorder_list(root->right);
		curr = create_list_node(root->TreeNode_info);
		curr->next = left;  
		left = append_lists(curr, right);
	}
	return left;
}