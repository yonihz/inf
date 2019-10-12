/****************************************************************
* 																*
* FILE NAME: sorted_list.c										*
* 																*
* PURPOSE: Sorted List (using DList) functions source file		*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h>

#include "sorted_list.h"
#include "dlist.h"

struct sorted_list
{
	is_before_t is_before;
	dlist_t* dlist;
	const void* param;
};

/* in case of failure return NULL, complexity o(1) */
srlist_t* SortedListCreate(is_before_t is_before, const void* param)
{
	srlist_t* new_srlist = malloc(sizeof(srlist_t));

	assert(new_srlist);

	if (NULL == new_srlist)
	{
		return (NULL);
	}

	new_srlist->dlist = DListCreate();

	if (NULL == new_srlist->dlist)
	{
		free(new_srlist);
		return (NULL);
	}

	new_srlist->is_before = is_before;
	new_srlist->param = param;

	return (new_srlist);
}
/* complexity o(1) */
void SortedListDestroy(srlist_t* srlist)
{
	assert(srlist);

	srlist->is_before = NULL;
	DListDestroy(srlist->dlist);
	srlist->dlist = NULL;
	free(srlist);
	srlist = NULL;
}

/* complexity o(n)*/
size_t SortedListSize(const srlist_t* srlist)
{
	assert(srlist);

	return (DListSize(srlist->dlist));
}

/* complexity o(1) */
int SortedListIsEmpty(const srlist_t* srlist)
{
	assert(srlist);

	return (DListIsEmpty(srlist->dlist));
}

/* complexity o(1) */
void* SortedListGetData(sorted_list_iter_t iter)
{
	return (DListGetData(iter.internal_itr));
}

/* return the first node */
sorted_list_iter_t SortedListBegin(srlist_t* srlist)
{
	sorted_list_iter_t iter;

	assert(srlist);

	iter.internal_itr = DListBegin(srlist->dlist);
	return (iter);
}

/* complexity o(1) */
sorted_list_iter_t SortedListEnd(srlist_t* srlist)
{
	sorted_list_iter_t iter;

	assert(srlist);

	iter.internal_itr = DListEnd(srlist->dlist);
	return (iter);
}

/* complexity o(1) */
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_prev;
	iter_prev.internal_itr = DListPrev(iter.internal_itr);
	return (iter_prev);
}

/* complexity o(1) */
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_next;
	iter_next.internal_itr = DListNext(iter.internal_itr);
	return (iter_next);
}

/* return the inserted iter, complexity o(1) */
sorted_list_iter_t SortedListInsert(srlist_t* srlist, void* data)
{
	sorted_list_iter_t iter;
	assert(srlist);

	iter = SortedListBegin(srlist);
	while (!SortedListIsSameIter(iter, SortedListEnd(srlist)) &&
		!srlist->is_before(data, DListGetData(iter.internal_itr), srlist->param))
	{
		iter = SortedListNext(iter);
	}
	iter.internal_itr = DListInsert(srlist->dlist, iter.internal_itr, data);
	return (iter);
}

/* complexity o(1). return the next iter affter the removed one */
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_remove;
	iter_remove.internal_itr = DListRemove(iter.internal_itr);
	return (iter_remove);
}

/* complexity o(1) */
void* SortedListPopFront(srlist_t* srlist)
{
	assert(srlist);

	return (DListPopFront(srlist->dlist));
}

/* complexity o(1) */
void* SortedListPopBack(srlist_t* srlist)
{
	assert(srlist);

	return (DListPopBack(srlist->dlist));
}

/* complextiy o(1) */
int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return (DListIsSame(iter1.internal_itr, iter2.internal_itr));
}

/* complexity o(n) */
int SortedListForEach(sorted_list_iter_t start, sorted_list_iter_t stop, 
                            int(*operation)(void* data, void* param), void* param)
{
	return DListForEach(start.internal_itr,
			stop.internal_itr, operation, param);
}

/* empties the src list, complexity o(n+m) */
void SortedListMerge(srlist_t* dest, srlist_t* src)
{
	sorted_list_iter_t iter_src = SortedListBegin(src);
	sorted_list_iter_t iter_dest = SortedListBegin(dest);

	assert(dest && src);

	/* if dest is empty and src is non-empty, splice all src to dest */
	if (SortedListIsSameIter(iter_dest, SortedListEnd(dest)) &&
		!SortedListIsSameIter(iter_src, SortedListEnd(src)))
	{
		DListSplice(iter_dest.internal_itr, iter_src.internal_itr,
		SortedListEnd(src).internal_itr);
		return;
	}

	/* run until src list reaches end */
	while (!SortedListIsSameIter(iter_src, SortedListEnd(src)))
	{

		/* increment dest until src node is after dest node */
		while (!(dest->is_before(SortedListGetData(iter_src),
				SortedListGetData(iter_dest), src->param)))
		{
			iter_dest = SortedListNext(iter_dest);
			
			/* if reached dest end, splice rest of src to end of dest */
			if (SortedListIsSameIter(iter_dest, SortedListEnd(dest)))
			{
				DListSplice(iter_dest.internal_itr, iter_src.internal_itr,
				SortedListEnd(src).internal_itr);
				return;
			}
		}

		/* splice one node of src to dest and increment src */
		DListSplice(iter_dest.internal_itr, iter_src.internal_itr,
		SortedListNext(iter_src).internal_itr);
		iter_src = SortedListBegin(src);
	}
	return;
}

/* complexity o(n), if found- return the first that found. else- return the stop*/
sorted_list_iter_t SortedListFind(srlist_t* srlist, sorted_list_iter_t start,
                            sorted_list_iter_t stop, const void* to_find)
{
	assert(srlist);

	while (!SortedListIsSameIter(start,stop))
	{
		if (!srlist->is_before(to_find, SortedListGetData(start), srlist->param) &&
			!srlist->is_before(SortedListGetData(start), to_find, srlist->param))
		{
			break;
		}
		start = SortedListNext(start);
	}
	return (start);
}

/*complexity o(n),  if found- return the first that found. else- return the stop*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t start, sorted_list_iter_t stop,
                            int(*match)(const void* data,const void* param), const void* param)
{
	sorted_list_iter_t iter_find;
	iter_find.internal_itr =
	DListFind(start.internal_itr, stop.internal_itr, match, (void*)param);
	return (iter_find);
	
}
