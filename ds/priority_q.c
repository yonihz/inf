#include <stdlib.h> /* malloc */

#include "sorted_list.h"
#include "priority_q.h"

	
struct pq
{
	srlist_t* list;
	const void* param;
	comp_func_t comp_func;
};

/* in case of failure return NULL, complexity o(1) */
pq_t* PQCreate(comp_func_t comp_priority, const void* param)
{
	pq_t* new_pq = NULL;
	
	new_pq = malloc(sizeof(pq_t));

	if (NULL == new_pq)
	{
		return (NULL);
	}

	new_pq->list = SortedListCreate(comp_priority, param);
	new_pq->param = param;
	new_pq->comp_func = comp_priority;

	return (new_pq);
}

/* complexity o(n) */
void PQDestroy(pq_t* pq)
{
	SortedListDestroy(pq->list);
	free(pq);	
}

/* return: 0- success, 1- fail. complexity o(n) */
int PQEnqueue(pq_t* pq, void* data)
{
	sorted_list_iter_t iter_enq;
	
	iter_enq = SortedListInsert(pq->list, data);
	
	return (SortedListIsSameIter(iter_enq, SortedListEnd(pq->list))) ? 1 : 0;
}

/* complexity o(1) */
void* PQDequeue(pq_t* pq)
{
	return (SortedListPopFront(pq->list));
}

/* complexity o(1) */
void* PQPeek(const pq_t* pq)
{
	return (SortedListGetData(SortedListBegin(pq->list)));
}

/* return: 1- empty. complexity o(1) */
int PQIsEmpty(const pq_t* pq)
{
	return (SortedListIsEmpty(pq->list));
}

/* complexity o(1) */
size_t PQSize(const pq_t* pq)
{
	return (SortedListSize(pq->list));
}

/* complexity o(n) */
void PQClear(pq_t* pq)
{
	SortedListDestroy(pq->list);
	pq->list = SortedListCreate(pq->comp_func, pq->param);
}

/* complexity o(n) */
void* PQErase(pq_t* pq, match_func_t match_func, const void* data)
{
	sorted_list_iter_t iter_match;
	void* data_match = NULL;
	
	iter_match = SortedListFindIf(SortedListBegin(pq->list),
				SortedListEnd(pq->list),
				match_func,
				data);

	data_match = SortedListIsSameIter(iter_match,SortedListEnd(pq->list)) ?
					NULL : SortedListGetData(iter_match);

	SortedListRemove(iter_match);
	return (data_match);
}

