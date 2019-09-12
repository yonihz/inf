#ifndef _DLIST_H_
#define _DLIST_H_

/* Rev. 1.7*/ 
/* 11.09.19  09:45 */
#include <stddef.h> /*size_t, NULL*/

typedef struct dlist dlist_t;
typedef struct dlist_node_t* dlist_iter_t;


/* in case of match return 0 */
typedef int(*is_match_func)(const void* data, const void* param);
/* return value: 0 = continue , otherwise - stop */
typedef int(*oper_func_t)(void* data, void* param);


/*in case of failure return NULL, complexity of malloc */
dlist_t* DListCreate(void);

/*complexity of free*/
void DListDestroy(dlist_t* dlist);

/* return number of elements, complexity O(n)*/
size_t DListSize(const dlist_t* dlist);

/* complexity O(n)*/
int DListIsEmpty(const dlist_t* dlist);

/*complexity O(1), get data from end is undefined*/
void* DListGetData(dlist_iter_t iter);

/* return the return-value of the last operation. interate over [iter_start, iter_end)
, complexity O(n) */
int DListForEach(dlist_iter_t iter_start, dlist_iter_t iter_end,
                    oper_func_t operation, void* param); 

/*return the first found iter or iter_end if not found,
interate over [iter_start, iter_end) complexity O(n)*/
dlist_iter_t DListFind(dlist_iter_t iter_start, dlist_iter_t iter_end,
                       is_match_func match, void* param);

/* return dest, insert new iters before dest, including iters from
src_start to the one before src_stop, complexity O(1)*/
dlist_iter_t DListSplice(dlist_iter_t dest, dlist_iter_t src_start,
                         dlist_iter_t src_stop);

/*returns the first iter or DListEnd if the list is empty, complexity O(1)*/
dlist_iter_t DListBegin(const dlist_t* dlist);

/*returns the end of the list, complexity O(1)*/
dlist_iter_t DListEnd(const dlist_t* dlist);

/*complexity O(1)*/
dlist_iter_t DListNext(dlist_iter_t iter);

/*complexity O(1)*/
dlist_iter_t DListPrev(dlist_iter_t iter);

/* return: 0 - not same, 1 - same, complexity O(1) */
int DListIsSame(dlist_iter_t iter1, dlist_iter_t iter2);

/*insert before iter, return the inserted iter, complexity of malloc
in case of failure return DListEnd*/
dlist_iter_t DListInsert(dlist_t* dlist, dlist_iter_t iter, void* data);

/* return the iter after removed one or DListEnd in case of last iter,
complexity O(1) */
dlist_iter_t DListRemove(dlist_iter_t iter);

/* return the new first iter, in case of failure returns DListEnd,
complexity O(1) */
dlist_iter_t DListPushFront(dlist_t* dlist, void* data);

/* return the new last element, in case of failure returns DListEnd,
complexity O(1) */
dlist_iter_t DListPushBack(dlist_t* dlist, void* data);

/*return the data of the first iter and removes it, complexity O(1)*/
void* DListPopFront(dlist_t* dlist);

/*return the data of the last iter and removes it, complexity O(1)*/
void* DListPopBack(dlist_t* dlist);

#endif


