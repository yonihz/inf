#ifndef _PQ_H_
#define _PQ_H_

/* Rev. 1.0*/ 
/* 15.09.19  17:00 */
#include <stddef.h> /*size_t, NULL*/

#include "heap.h"

typedef struct pq pq_t;

/* return 1 in if data1 is before data2, else 0 */
typedef int(*comp_func_t)(const void* data1, const void* data2);

/* in case of failure return NULL, complexity o(1) */
pq_t* PQCreate(comp_func_t comp_priority, const void* param);

/* complexity o(n) */
void PQDestroy(pq_t* pq);

/* return: 0- success, 1- fail. complexity o(n) */
int PQEnqueue(pq_t* pq, void* data);

/* complexity o(1) */
void* PQDequeue(pq_t* pq);

/* complexity o(1) */
void* PQPeek(const pq_t* pq);

/* return: 1- empty. complexity o(1) */
int PQIsEmpty(const pq_t* pq);

/* complexity o(1) */
size_t PQSize(const pq_t* pq);

/* complexity o(n) */
void PQClear(pq_t* pq);

/* complexity o(n) */
void* PQErase(pq_t* pq, match_func_t match_func, const void* data);

#endif

