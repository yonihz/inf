/****************************************************************
* 																*
* FILE NAME: dlist.c											*
* 																*
* PURPOSE: Doubly Linked List functions source file				*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 10.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h>

#include "dlist.h"

#define UNUSED(x) (void)(x)

typedef struct dlist_node_t dlist_node_t;

struct dlist
{
	dlist_node_t* front;
	dlist_node_t* back;
};

struct dlist_node_t
{
	void* data;
	dlist_node_t* next;
	dlist_node_t* prev;
};

int DListOpSize(void* data, void* size);
dlist_node_t* DListCreateNode(void* data);

dlist_t* DListCreate(void)
{
	dlist_t* new_dlist = NULL;
	new_dlist = malloc(sizeof(dlist_t));
	assert(new_dlist);

	new_dlist->front = DListCreateNode(NULL);
	new_dlist->back = DListCreateNode(NULL);

	(new_dlist->front)->next = new_dlist->back;
	(new_dlist->front)->prev = NULL;
	(new_dlist->back)->next = NULL;
	(new_dlist->back)->prev = new_dlist->front;

	return (new_dlist);
}

void DListDestroy(dlist_t* dlist)
{
	dlist_iter_t iter = (dlist->front)->next;
	while (iter != dlist->back)
	{
		iter = DListRemove(iter);
	}
		free(dlist->front);
		free(dlist->back);
		free(dlist);

	dlist->back = NULL;
	dlist->front = NULL;
	dlist = NULL;
}

size_t DListSize(const dlist_t* dlist)
{
	size_t size = 0;
	
	DListForEach((dlist->front)->next, (dlist->back), &DListOpSize, &size);
	return (size);
}

int DListIsEmpty(const dlist_t* dlist)
{
	return ((dlist->front)->next == (dlist->back));
}

void* DListGetData(dlist_iter_t iter)
{
	return (iter->data);	
}

int DListForEach(dlist_iter_t iter_start, dlist_iter_t iter_end,
                    oper_func_t operation, void* param)
{
	int stop = 0;

	while (iter_start != iter_end)
	{
		stop = (*operation)((iter_start)->data, param);

		if (stop)
		{
			break;
		}
	
		iter_start = iter_start->next;
	}
	return (stop);
}

dlist_iter_t DListFind(dlist_iter_t iter_start, dlist_iter_t iter_end,
                       is_match_func match, void* param)
{
	int found = 0;

	while (iter_start != iter_end || NULL == iter_start)
	{
		found = match(iter_start->data, param);

		if (0 == found)
		{
			break;
		}

		iter_start = iter_start->next;
	}

	return iter_start ? iter_start : iter_end;
}

dlist_iter_t DListSplice(dlist_iter_t dest, dlist_iter_t src_start,
                         dlist_iter_t src_stop)
{
	dlist_node_t* node_temp1 = NULL;
	dlist_node_t* node_temp2 = NULL;

	node_temp1 = dest->prev;
	dest->prev = src_stop->prev;
	node_temp1->next = src_start;
	node_temp2 = src_start->prev;
	src_start->prev = node_temp1;
	node_temp2->next = src_stop;
	(src_stop->prev)->next = dest;
	src_stop->prev = node_temp2;

	return (dest);
}

dlist_iter_t DListBegin(const dlist_t* dlist)
{
	return ((dlist->front)->next);
}

dlist_iter_t DListEnd(const dlist_t* dlist)
{
	return (dlist->back);
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
	return ((iter->next) ? (iter->next) : (iter));
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	return ((iter->prev) ? (iter->prev) : (iter));
}

int DListIsSame(dlist_iter_t iter1, dlist_iter_t iter2)
{
	return (iter1 == iter2);
}

dlist_iter_t DListInsert(dlist_t* dlist, dlist_iter_t iter, void* data)
{
	dlist_node_t* new_node = DListCreateNode(data);
	
	if (NULL == new_node)
	{
		return DListEnd(dlist);
	}
	
	new_node->prev = iter->prev;
	new_node->next = iter;
	(iter->prev)->next = new_node;
	iter->prev = new_node;
	return (new_node);
}

/* return the iter after removed one or DListEnd in case of last iter,
complexity O(1) */
dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_iter_t target = NULL;

	if (iter->next == NULL)
	{
		return (NULL);	
	}

	(iter->next)->prev = (iter->prev);
	(iter->prev)->next = (iter->next);
	target = iter;
	iter = iter->next;
	free(target);
	target = NULL;
	return iter;
}

dlist_iter_t DListPushFront(dlist_t* dlist, void* data)
{
	return(DListInsert(dlist, (dlist->front)->next, data));
}

dlist_iter_t DListPushBack(dlist_t* dlist, void* data)
{
	return(DListInsert(dlist, dlist->back, data));
}

void* DListPopFront(dlist_t* dlist)
{
	void* data = ((dlist->front)->next)->data;
	DListRemove((dlist->front)->next);

	return (data);	
}

void* DListPopBack(dlist_t* dlist)
{
	void* data = ((dlist->back)->prev)->data;
	DListRemove((dlist->back)->prev);

	return (data);
}

dlist_node_t* DListCreateNode(void* data)
{
	dlist_node_t* new_node = malloc(sizeof(dlist_node_t));
	assert(new_node);

	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int DListOpSize(void* data, void* size)
{
	UNUSED(data);

	++(*(size_t*)size);
	return (0);
}


