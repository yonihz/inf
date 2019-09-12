#ifndef _SORTED_LIST_H_
#define _SORTED_LIST_H_

/* Rev. 0.8*/ 
/* 12.09.19  07:50 */
#include <stddef.h> /*size_t, NULL*/

#include "dlist.h"

typedef struct sorted_list srlist_t;

typedef struct 
{
    dlist_iter_t internal_itr;
} sorted_list_iter_t;


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
void* SortedListGetData(sorted_list_iter_t iter);

/* return the first node */
sorted_list_iter_t SortedListBegin(srlist_t* srlist);

/* complexity o(1) */
sorted_list_iter_t SortedListEnd(srlist_t* srlist);

/* complexity o(1) */
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/* complexity o(1) */
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/* return the inserted iter, complexity o(1) */
sorted_list_iter_t SortedListInsert(srlist_t* srlist, void* data);

/* complexity o(1). return the next iter affter the removed one */
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

/* complexity o(1) */
void* SortedListPopFront(srlist_t* srlist);

/* complexity o(1) */
void* SortedListPopBack(srlist_t* srlist);

/* complextiy o(1) */
int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/* complexity o(n) */
int SortedListForEach(sorted_list_iter_t start, sorted_list_iter_t stop, 
                            int(*operation)(void* data, void* param), void* param);

/* empties the src list, complexity o(n+m) */
void SortedListMerge(srlist_t* dest, srlist_t* src);

/* complexity o(n), if found- return the first that found. else- return the stop*/
sorted_list_iter_t SortedListFind(srlist_t* srlist, sorted_list_iter_t start,
                            sorted_list_iter_t stop, const void* to_find);

/*complexity o(n),  if found- return the first that found. else- return the stop*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t start, sorted_list_iter_t stop,
                            int(*match)(const void* data,const void* param), const void* param);

#endif

