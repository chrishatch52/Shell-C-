#include "linkedList.h"



LinkedList * linkedList()
{
	LinkedList * temp = (LinkedList*)calloc(1, sizeof(LinkedList));
	temp->head = (Node*)calloc(1, sizeof(Node));
	temp->head->next = NULL;
	temp->head->prev = NULL;
	temp->size = 0;
	return temp;
}//end linkedList
Node * buildNode(int argc, char ** argv, void *(*buildData)(int argc, char ** argv) )
{
	Node * tmp = (Node*)calloc(1, sizeof(Node));

	tmp->data = buildData(argc, argv);
	tmp->next = NULL;
	tmp->prev = NULL;

	return tmp;
}//end buildNode
void addLast(LinkedList * theList, Node * nn)
{
	Node * dummy_head = theList->head, * cur = dummy_head->next;
	static int num_commands = 1;
	
	((Commands*)nn->data)->num = num_commands++;
	if(cur == NULL)
	{
		nn->prev = dummy_head;
		dummy_head->next = nn;
		cur = nn;
	}
	else
	{
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = nn;
		nn->prev = cur;
	}
	theList->size++;	
}//end addLast
void addFirst(LinkedList * theList, Node * nn)
{
	Node * dummy_head = theList->head, * cur = dummy_head->next;

	if(cur == NULL)
	{
		nn->prev = dummy_head;
		dummy_head->next = nn;
		cur = nn;
	}
	else
	{
		dummy_head->next = nn;
		nn->next = cur;
		nn->prev = dummy_head;
		cur->prev = nn;
	}
	theList->size++;
}//addFirst
void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	Node * prv = theList->head, * cur, * nxt;
	
	for(cur = prv->next; cur != NULL; cur = nxt)
	{
		nxt = cur->next;
		
		if(compare(cur->data, nn->data)==0)
		{			
			if(cur->next != NULL)
			{
				prv->next = cur->next;
				cur->next->prev = prv;
			}
			else
			{
				prv->next = NULL;
			}
			removeData(cur->data); cur->data = NULL;
			cur->next = NULL;
			cur->prev = NULL;
			free(cur); cur = NULL;
			removeData(nn->data);			
			nn->data = NULL;
			free(nn); nn = NULL;
			theList->size--;
			break;
		}
		prv = prv->next;
	}
	
}//removeItem
void clearList(LinkedList * theList, void (*removeData)(void *))
{
	Node * prv = theList->head, * cur, * tmp;
	if(prv->next == NULL)
	{
		free(theList->head);
		theList->head = NULL;
		fprintf(stdout, "head pointer: %p", theList->head);
		fprintf(stdout, "The List is Empty\n");
	}
	else if(prv->next != NULL)
	{
		for(cur = prv->next; cur != NULL; cur = tmp)
		{
			tmp = cur->next;
			theList->head->next = tmp;
			removeData(cur->data);
			cur->data = NULL;
			cur->next = NULL;
			cur->prev = NULL;
			free(cur);
			cur = NULL;
		}
		free(theList->head);
		theList->head = NULL;
	}
}//end clearList
void printList(const LinkedList * theList, void (*convertData)(void *))
{
	Node * cur = theList->head;

	while(cur->next != NULL)
	{
		cur = cur->next;
		convertData(cur->data);
	}
}//end printList
void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
	Node * prv = theList->head, * cur, * nxt;
	void * tmp_data;
	int i, j;
	if(theList->size == 0)
	{
		fprintf(stdout, "Empty List cannot be sorted\n");
	}
	else
	{
		prv = prv->next;
		for(i = 0; i < theList->size - 1; i++)
		{
			cur = prv->next;
			for(j = i + 1; j < theList->size; j++)
			{
				if(compare(prv->data, cur->data) > 0)
				{
					tmp_data = prv->data;
					prv->data = cur->data;
					cur->data = tmp_data;
				}
				cur = cur->next;
			}
			prv = prv->next;
		}
	}
}//end sort
