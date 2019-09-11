#ifndef _SORT_LIST_H_
#define _SORT_LIST_H_

/* Rev. 0.5*/ 
/* 11.09.19  16:25 */
#include <stddef.h> /*size_t, NULL*/

#include "dlist.h"

typedef struct sorted_list srlist_t;

typedef struct srlist_iter srlist_iter_t;


/* return 1 in if data1 is before data2, else 0 */
typedef int(*is_before_t)(const void* data1, const void* data2);

/* in case of failure return NULL, complexity o(1) */
srlist_t* SortedListCreate(is_before_t is_before);

/* complexity o(1) */
void SortedListDestroy(srlist_t* srlist);

/* complexity o(n)*/
size_t SortedListSize(const srlist_t* srlist);

/* complexity o(1) */
int SortedListIsEmpty(const srlist_t* srlist);

/* complexity o(1) */
void* SortedListGetData(srlist_iter_t iter);

/* return the first node */
srlist_iter_t SortedListBegin(srlist_t* srlist);

/* complexity o(1) */
srlist_iter_t SortedListEnd(srlist_t* srlist);

/* complexity o(1) */
srlist_iter_t SortedListPrev(srlist_iter_t iter);

/* complexity o(1) */
srlist_iter_t SortedListNext(srlist_iter_t iter);

/* return the inserted iter, complexity o(1) */
srlist_iter_t SortedListInsert(srlist_t* srlist, void* data);

/* complexity o(1). return the next iter affter the removed one */
srlist_iter_t SortedListRemove(srlist_iter_t iter);

/* complexity o(1) */
void* SortedListPopFront(srlist_t* srlist);

/* complexity o(1) */
void* SortedListPopBack(srlist_t* srlist);

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
                            int(*match)(const void* data,const void* param), void* param);

#endif

