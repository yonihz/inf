#ifndef _DLIST_H_
#define _DLIST_H_

/* Rev. 1.0*/ 
/* 09.09.19  16:40 */
#include <stddef.h> /*size_t, NULL*/

typedef struct dlist dlist_t;
typedef struct dlist_node_t* dlist_iter_t;



/* in case of match return 0 */
typedef int(*is_match_func)(const void* data, void* param);
/* param: 0 = continue , otherwise - stop */
typedef int(*oper_func_t)(void* data, void* param);


/*complexity of malloc */
dlist_t* DListCreate(void);

/*complexity of free*/
void DListDestroy(dlist_t* dlist);

/* return number of elements, complexity O(n)*/
size_t DListSize(const dlist_t* dlist);

/* complexity O(n)*/
int DListIsEmpty(const dlist_t* dlist);

/*complexity O(1)*/
void* DListGetData(dlist_iter_t iter);

/* return the value passed by the operation, complexity O(n) */
int DListForEach(dlist_iter_t iter_start, dlist_iter_t iter_end,
                    oper_func_t operation, void* param); 

/*return the first found element, complexity O(n)*/
dlist_iter_t DListFind(dlist_iter_t iter_start, dlist_iter_t iter_end,
                       is_match_func match, void* param);
/* return dest, complexity O(1)*/
dlist_iter_t DListSplice(dlist_iter_t dest, dlist_iter_t src_start,
                         dlist_iter_t src_stop);
/*complexity O(1)*/
dlist_iter_t DListBegin(const dlist_t* dlist);

/*complexity O(1)*/
dlist_iter_t DListEnd(const dlist_t* dlist);

/*return NULL in case of the last element, complexity O(1)*/
dlist_iter_t DListNext(dlist_iter_t iter);

/*return NULL in case of the first element, complexity O(1)*/
dlist_iter_t DListPrev(dlist_iter_t iter);

/* return: 0 - not same, 1 - same, complexity O(1) */
int DListIsSame(dlist_iter_t iter1, dlist_iter_t iter2);

/*return the inserted element, complexity O(1)*/
dlist_iter_t DListInsert(dlist_t* dlist, dlist_iter_t iter, void* data);

/* return the next element, or null if last, complexity O(1) */
dlist_iter_t DListRemove(dlist_iter_t iter);

/* return the first element, complexity O(1) */
dlist_iter_t DListPushFront(dlist_t* dlist, void* data);

/* return the end element, complexity O(1) */
dlist_iter_t DListPushBack(dlist_t* dlist, void* data);

/* complexity O(1)*/
void* DListPopFront(dlist_t* dlist);

/* complexity O(1)*/
void* DListPopBack(dlist_t* dlist);

#endif


