/****************************************************************
* 																*
* FILE NAME: SList.c											*
* 																*
* PURPOSE: SList functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 02.09.19												*
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

#include "SList.h"

#ifndef NDEBUG
#define ACTIVE 0xDEADBEEF
#define ALLOCATED 0xBADDCAFE
#endif

SList_node_t *SListCreateNode(void *data, SList_node_t *next)
{
	node_t new_node = NULL;

	new_node = malloc(sizeof(node_t));

	assert(new_node);

	if (NULL == next)
	{
		new_node->next = NULL;
	}

	new_node->data = data;
	new_node->next = next;

	return (new_node);
}	

SList_node_t* SListInsertAfter(SList_node_t *target, SList_node_t *new_node)
{
	new_node->next = target->next;
	target->next = new_node;

	return(new_node);
}

SList_node_t* SListInsert(const SList_node_t *target, SList_node_t *new_node)
{
	void* temp = target->data;
	target->data = new_node->data;
	new_node->data = temp;	

	new_node->next = target->next;
	target->next = new_node;

	return(new_node);
}

SList_node_t* SListRemoveAfter(SList_node_t *target)
{
	node_t* after_target = target->next;

	if (NULL == target->next)
	{
		return NULL;
	}

	
	target->next = (target->next)->next;

	free(after_target);

	return (target);
}

SList_node_t* SListRemove(const SList_node_t *target)
{
	node_t* after_target = target->next;
	
	target->data = after_target->data;
	target->next = after_target->next;

	free(after_target);
	
}

size_t SListCount(const SList_node_t *head);
void SListFreeAll(SList_node_t *head);
SList_node_t *SListFind(SList_node_t *head, is_match_func *match, void *param);
void SListForEach(SList_node_t* head, operation_func* operation, void* param);
SList_node_t* SListFlip(SList_node_t* head);
int SListHasLoop(const SList_node_t* head);
SList_node_t* SListFindIntersection(SList_node_t* head1, SList_node_t* head2);

