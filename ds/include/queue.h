#ifndef _QUEUE_H_
#define _QUEUE_H_

/* Rev. 1.0*/ 
/* 04.09.19  11:30 */
#include <stddef.h>

typedef struct queue queue_t;

/* complexity of malloc */
queue_t* QCreate();

/* complexity o(n) */
void QDestroy(queue_t* queue);

/* complexity o(1) */
void QDequeue(queue_t* queue);

/* return 0=success, 1=failur no check if data=null 
complexity of malloc */
int QEnqueue(queue_t* queue, void *data);

/* if empty return null, return pointer to node->data
complexity o(1) */
void *QPeek(const queue_t* queue);

/* complexity o(n) */
size_t QSize(const queue_t* queue);

/* 1= empty. 0=full
complexity o(1) */
int QIsEmpty(const queue_t* queue);

/* complexity o(1),src became empty queue */
void QAppend(queue_t* dest, queue_t* src);

#endif


