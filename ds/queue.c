/****************************************************************
* 																*
* FILE NAME: queue.c											*
* 																*
* PURPOSE: Queue functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 04.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "queue.h"
#include "slist.h"

struct queue
{
	slist_node_t* first;
	slist_node_t* last;
};

queue_t* QCreate()
{
	queue_t* new_queue = NULL;

	new_queue = malloc(sizeof(queue_t));
	assert(new_queue);

	new_queue->first = SListCreateNode(NULL, NULL);	

	assert(new_queue->first);

	new_queue->last = new_queue->first;

	return (new_queue);
}

void QDestroy(queue_t* queue)
{
	assert(queue);

	SListFreeAll(queue->first);
	free(queue);
}

void QDequeue(queue_t* queue)
{
	assert(queue);

	(queue->first)->next = SListRemoveAfter(queue->first);

	if ((queue->first)->next == NULL)
	{
		queue->last = queue->first;
	}

}

/* return 0=success, 1=failur no check if data=null */
int QEnqueue(queue_t* queue, void *data)
{
	slist_node_t* new_node = NULL;

	assert(queue);
	
	new_node = SListCreateNode(data, NULL);
	SListInsertAfter(queue->last, new_node);
	queue->last = new_node;

	if (!(queue->last))
	{
		return (1);
	}
	
	return (0);
}

/* if empty return null, return pointer to node->data */
void *QPeek(const queue_t* queue)
{
	assert(queue);

	if (QIsEmpty(queue))
	{
		return NULL;
	}
	
	return (((queue->first)->next)->data);		
}

size_t QSize(const queue_t* queue)
{
	if (QIsEmpty(queue))
	{
		return (0);
	}

	return (SListCount((queue->first)->next));
}

/* 1= empty. 0=full */
int QIsEmpty(const queue_t* queue)
{
	assert(queue);

	return (((queue->first)->next) == NULL);
}

void QAppend(queue_t* dest, queue_t* src)
{
	(src->last)->next = (dest->first)->next;
	(dest->first)->next = NULL;
}

