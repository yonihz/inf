#include <stdlib.h> /* malloc */
#include <assert.h>

#include "sorted_list.h"
#include "dlist.h"

struct sorted_list
{
	is_before_t is_before;
	dlist_t* dlist;
};

struct srlist_iter
{
	dlist_iter_t dlist_iter;
};


/* in case of failure return NULL, complexity o(1) */
srlist_t* SortedListCreate(is_before_t is_before)
{
	srlist_t* new_srlist = malloc(sizeof(srlist_t));

	assert(new_srlist);

	if (NULL == new_srlist)
	{
		return (NULL);
	}

	new_srlist->dlist = DListCreate();
	new_srlist->is_before = is_before;

	return (new_srlist);
}
/* complexity o(1) */
void SortedListDestroy(srlist_t* srlist)
{
	srlist->is_before = NULL;
	DListDestroy(srlist->dlist);
	srlist->dlist = NULL;
	free(srlist);
	srlist = NULL;
}

/* complexity o(n)*/
size_t SortedListSize(const srlist_t* srlist)
{
	return (DListSize(srlist->dlist));
}

/* complexity o(1) */
int SortedListIsEmpty(const srlist_t* srlist)
{
	return (DListIsEmpty(srlist->dlist));
}

/* complexity o(1) */
void* SortedListGetData(srlist_iter_t iter)
{
	return (DListGetData(iter->dlist_iter));
}

/* return the first node */
srlist_iter_t SortedListBegin(srlist_t* srlist)
{
	srlist_iter_t iter;
	iter->dlist_iter = DListBegin(srlist->dlist);
	return (iter);
}

/* complexity o(1) */
srlist_iter_t SortedListEnd(srlist_t* srlist);
{
	return (DListEnd(srlist->dlist));
}

/* complexity o(1) */
srlist_iter_t SortedListPrev(srlist_iter_t iter)
{
	return (DListPrev(iter->dlist_iter));
}

/* complexity o(1) */
srlist_iter_t SortedListNext(srlist_iter_t iter)
{
	return (DListNext(iter->dlist_iter));	
}

/* return the inserted iter, complexity o(1) */
srlist_iter_t SortedListInsert(srlist_t* srlist, void* data);

/* complexity o(1). return the next iter affter the removed one */
srlist_iter_t SortedListRemove(srlist_iter_t iter)
{
	return (DListRemove(iter->dlist_iter));
}

/* complexity o(1) */
void* SortedListPopFront(srlist_t* srlist)
{
	return (DListPopFront(srlist->dlist));
}

/* complexity o(1) */
void* SortedListPopBack(srlist_t* srlist)
{
	return (DListPopBack(srlist->dlist));
}

/* complextiy o(1) */
int SortedListIsSameIter(srlist_iter_t iter1, srlist_iter_t iter2);

/* complexity o(n) */
int SortedListForEach(srlist_iter_t start, srlist_iter_t stop, 
                            int(*operation)(void* data, void* param), void* param);

/* empties the src list, complexity o(n+m) */
void SortedListMerge(srlist_t* dest, srlist_t* src);

/* complexity o(n), if found- return the first that found. else- return the stop*/
srlist_iter_t SortedListFind(srlist_t* srlist, srlist_iter_t start,
                            srlist_iter_t stop, const void* to_find);

/*complexity o(n),  if found- return the first that found. else- return the stop*/
srlist_iter_t SortedListFindIf(srlist_iter_t start, srlist_iter_t stop,
                            int(*match)(const void* data,const void* param), const void* param);
