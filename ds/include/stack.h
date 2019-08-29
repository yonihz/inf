/****************************************************************
* 																*
* FILE NAME: stack.h											*
* 																*
* PURPOSE: Stack functions header file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#ifndef _STACK_H_
#define _STACK_H_

/* Rev. 1.1 */ 
/* 28.8.19  12:30 */

#include <stddef.h>

typedef struct stack stack_t;

/* complexity of malloc function */
stack_t *StackCreate(size_t num_of_elements, size_t size_of_element);

/* complexity of free function */
void StackDestroy(stack_t *stack);

/* complexity of O(n) */
int StackPush(stack_t *stack, const void *element);

/* complexity of O(1) */
void StackPop(stack_t *stack);

/* complexity of O(1) */
const void *StackPeek(const stack_t *stack);

/* complexity of O(1) */
size_t StackSize(const stack_t *stack);

/* complexity of O(1) */
int StackIsEmpty(const stack_t *stack);

#endif


