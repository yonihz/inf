#include <stdlib.h> /* malloc */
#include <assert.h>

#include "heap.h"
#include "priority_q_heap.h"

#define UNUSED(x) (void)(x)

struct pq
{
	heap_t* heap;
	comp_func_t comp_func;
};

/* in case of failure return NULL, complexity o(1) */
pq_t* PQCreate(comp_func_t comp_priority, const void* param)
{
	pq_t* new_pq = NULL;

	UNUSED(param);

	new_pq = malloc(sizeof(pq_t));

	if (NULL == new_pq)
	{
		return (NULL);
	}

	new_pq->comp_func = comp_priority;
	new_pq->heap = HeapCreate(comp_priority);

	if (NULL == new_pq->heap)
	{
		free(new_pq);
		return (NULL);
	}

	return (new_pq);
}

/* complexity o(n) */
void PQDestroy(pq_t* pq)
{
	assert(pq);

	HeapDestroy(pq->heap);
	free(pq);
	pq = NULL;
}

/* return: 0- success, 1- fail. complexity o(n) */
int PQEnqueue(pq_t* pq, void* data)
{
	assert(pq);
	
	return (HeapPush(pq->heap, data));
}

/* complexity o(1) */
void* PQDequeue(pq_t* pq)
{
	void *data = NULL;

	assert(pq);

	data = HeapPeek(pq->heap);
	HeapPop(pq->heap);

	return (data);
}

/* complexity o(1) */
void* PQPeek(const pq_t* pq)
{
	assert(pq);

	return (HeapPeek(pq->heap));
}

/* return: 1- empty. complexity o(1) */
int PQIsEmpty(const pq_t* pq)
{
	assert(pq);

	return (HeapIsEmpty(pq->heap));
}

/* complexity o(1) */
size_t PQSize(const pq_t* pq)
{
	assert(pq);

	return (HeapSize(pq->heap));
}

/* complexity o(n) */
void PQClear(pq_t* pq)
{
	assert(pq);

	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

/* complexity o(n) */
void* PQErase(pq_t* pq, match_func_t match_func, const void* data)
{
	void* data_match = NULL;
	
	assert(pq);

	data_match = HeapRemove(pq->heap, data, match_func);

	return (data_match);
}
