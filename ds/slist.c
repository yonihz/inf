/****************************************************************
* 																*
* FILE NAME: slist.c											*
* 																*
* PURPOSE: slist functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 03.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "slist.h"

slist_node_t *SListCreateNode(void *data, slist_node_t *next)
{
	slist_node_t* new_node = NULL;

	new_node = malloc(sizeof(slist_node_t));

	assert(new_node);

	if (NULL == next)
	{
		new_node->next = NULL;
	}

	new_node->data = data;
	new_node->next = next;

	return (new_node);
}	

slist_node_t* SListInsertAfter(slist_node_t *target, slist_node_t *new_node)
{
	new_node->next = target->next;
	target->next = new_node;

	return(new_node);
}

slist_node_t* SListInsert(slist_node_t *target, slist_node_t *new_node)
{
	void* temp = target->data;
	target->data = new_node->data;
	new_node->data = temp;	

	new_node->next = target->next;
	target->next = new_node;

	return(new_node);
}

slist_node_t* SListRemoveAfter(slist_node_t *target)
{
	slist_node_t* after_target = target->next;

	if (NULL == target->next)
	{
		return NULL;
	}

	target->next = (target->next)->next;

	free(after_target);

	return (target->next);
}

slist_node_t* SListRemove(slist_node_t *target)
{
	slist_node_t* after_target = target->next;
	
	target->data = after_target->data;
	target->next = after_target->next;

	free(after_target);

	return (target);
}

size_t SListCount(const slist_node_t *head)
{
	size_t i = 0;
	for (i = 0; head; i++, head = head->next) {};
	return i;
}

void SListFreeAll(slist_node_t *head)
{
	slist_node_t* node_current = head->next;
	
	free(head);
	while (node_current)
	{
		head = node_current;
		node_current = node_current->next;
		free(head);		
	}
}

slist_node_t *SListFind(slist_node_t *head, is_match_func *match, void *param)
{
	int found = 0;

	while (head)
	{
		found = (*match)(head->data, param);
		
		if (0 == found)
		{
			return (head);
		}

		head = head->next;
	}

	return NULL;
}

void SListForEach(slist_node_t* head, operation_func* operation, void* param)
{
	int stop = 0;

	while (head)
	{
		stop = (*operation)(head->data, param);
		if (0 == stop)
		{
			return;
		}
		
		head = head->next;
	} 
}

slist_node_t* SListFlip(slist_node_t* head)
{
	slist_node_t* node_next = NULL;
	slist_node_t* node_prev = NULL;

	node_next = head->next;
	head->next = NULL;
	node_prev = head;

	while (node_next)
	{
		head = node_next;
		node_next = head->next;
		head->next = node_prev;
		node_prev = head;
	}

	return (head);
}	

int SListHasLoop(const slist_node_t* head)
{
	slist_node_t* node_2step = head->next;

	while (node_2step)
	{
		if (head == node_2step)
		{
			return (1);
		}
		
		node_2step = node_2step->next;
	
		if (!node_2step)
		{
			return (0);
		}

		if (head == node_2step)
		{
			return (1);
		}

		head = head->next;
		node_2step = node_2step->next;		
	}

	return (0);
}
	
slist_node_t* SListFindIntersection(slist_node_t* head1, slist_node_t* head2)
{
	size_t count1 = 0, count2 = 0;
	slist_node_t* node1 = head1;
	slist_node_t* node2 = head2;

	for (count1 = 1; node1->next; count1++, node1 = node1->next) {};
	for (count2 = 1; node2->next; count2++, node2 = node2->next) {};

	if (node1 != node2)
	{
		return (NULL);
	}

	if (count1 > count)
	{
		count1 = count1 - count2;
		node1 = head1;
		node2 = head2;
	}
	else
	{
		count1 = count2 - count1;
		node1 = head2;
		node2 = head1;				
	}

	while (count1)
	{
		node1 = node1->next;
		count1--;
	}

	while (node1 != node2)
	{
		node1 = node1->next;
		node2 = node2->next;
	}
	
	return (node1);
}

