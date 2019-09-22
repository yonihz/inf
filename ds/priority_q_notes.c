#include <stdlib.h> /* malloc */ 
/*** stddef ***/

#include "sorted_list.h"
#include "priority_q.h"

int is_before_pq (const void* data1, const void* data2, const void* param);

typedef struct
{
	const void* param;
	comp_func_t comp_func;
} is_before_comp_t;

struct pq
{
	srlist_t* list;
	is_before_comp_t is_before_comp;
};


pq_t* PQCreate(comp_func_t comp_priority, const void* param)
{
	pq_t* new_pq = NULL;

	new_pq = malloc(sizeof(pq_t));

	if (NULL == new_pq)
	{
		return (NULL);
	}

	new_pq->is_before_comp.param = param;
	new_pq->is_before_comp.comp_func = comp_priority;
	new_pq->list = SortedListCreate(&is_before_pq, &(new_pq->is_before_comp));
	/*** DONE need to check if create secceeded if not free new_pq ***/
	return (new_pq);
}

void PQDestroy(pq_t* pq)
{
	SortedListDestroy(pq->list);
	free(pq);
	/*** DONE pq = NULL ***/
}


int PQEnqueue(pq_t* pq, void* data)
{
	sorted_list_iter_t iter_enq;
	
	iter_enq = SortedListInsert(pq->list, data);
	
	return (SortedListIsSameIter(iter_enq, SortedListEnd(pq->list))) ? 1 : 0;
}


void* PQDequeue(pq_t* pq)
{
	return (SortedListPopFront(pq->list));
}


void* PQPeek(const pq_t* pq)
{
	return (SortedListGetData(SortedListBegin(pq->list)));
}


int PQIsEmpty(const pq_t* pq)
{
	return (SortedListIsEmpty(pq->list));
}


size_t PQSize(const pq_t* pq)
{
	return (SortedListSize(pq->list));
}


void PQClear(pq_t* pq)
{
	SortedListDestroy(pq->list);
	pq->list = SortedListCreate(&is_before_pq, &(pq->is_before_comp));
	/*** DONE not pretty ;) ***/
}


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
					/*** DONE no need for that ***/

	SortedListRemove(iter_match);
	return (data_match);
}

int is_before_pq (const void* data1, const void* data2, const void* param)
{
	int res = ((is_before_comp_t*)param)->comp_func(data1,data2,
				((is_before_comp_t*)param)->param);
	return (res > 0) ? 1 : 0;
}
