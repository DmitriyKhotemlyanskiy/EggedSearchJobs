#include "ex.h"

typedef struct ListNode
{
	void *ch;
	struct ListNode *next;
}ListNode;

compare_func  cmp_char;
print_func  prnt_char;
free_func  free_char;

BOOL insertEntry(PNode* head, PNode* tail, void *data, compare_func func)
{
	PNode temp = NULL, pt = *head;
	temp = (PNode)malloc(sizeof(ListNode));
	if (NULL == temp)
	{
		printf("\nCan't allocate data memory");
		return FALSE;
	}
	temp->next = NULL;
	temp->ch = data;
	
	if (*head == NULL)
	{
		*head = *tail = temp;
		return TRUE;
	}
	else {
		while (pt != NULL)
		{
			if (func(pt->ch, data) == FALSE)
			{
				if (pt == *tail)
				{
					(*tail)->next = temp;
					(*tail) = (*tail)->next;
					return TRUE;
				}
				pt = pt->next;
			}
			 else return FALSE;
		}
	}
	return FALSE;
}

void printAll(PNode head, print_func func)
{
	PNode temp = head;
	while (temp != NULL)
	{
		func(temp->ch);
		temp = temp->next;
	}
}

BOOL deleteNode(PNode* head, PNode* tail, void *todel, compare_func func1, free_func func2)
{
	PNode temp = NULL, pt = *head;
	while (pt != NULL)
	{
		if ((pt == *head) && (func1(pt->ch, todel) == TRUE))
		{
			temp = *head;
			*head = (*head)->next;
			func2(temp->ch);
			free(temp);
			return TRUE;
		}
		if (func1(pt->next->ch, todel) == TRUE)
		{
			temp = pt->next;
			pt->next = pt->next->next;
			func2(temp->ch);
			free(temp);
			return TRUE;
		}
		pt = pt->next;
	}
	if (pt->next == *tail)
	{
		if (func1((*tail)->ch, todel) == TRUE)
		{
			temp = *tail;
			*tail = pt;
			func2(temp->ch);
			free(temp);
			return TRUE;
		}
	}
	return FALSE;
}

void freeAll(PNode* head, free_func func)
{
	PNode temp = NULL;
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		func(temp->ch);
		free(temp);
	}
}