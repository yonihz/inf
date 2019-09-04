/****************************************************************
* 																*
* FILE NAME: queue.c											*
* 																*
* PURPOSE: Queue functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 04.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "queue.h"
#include "slist.h"


queue_t* QCreate();


void QDestroy(queue_t* queue);


void QDequeue(queue_t* queue);

/* return 0=success, 1=failur no check if data=null */
int QEnqueue(queue_t* queue, void *data);

/* if empty return null, return pointer to node->data */
void *QPeek(const queue_t* queue);


size_t QSize(const queue_t* queue);

/* 1= empty. 0=full */
int QIsEmpty(const queue_t* queue);


void QAppend(queue_t* dest, queue_t* src);






