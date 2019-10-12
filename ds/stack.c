/****************************************************************
* 																*
* FILE NAME: stack.c											*
* 																*
* PURPOSE: Stack functions source file							*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */
#include <assert.h>

#include "stack.h"

#ifndef NDEBUG
#define ACTIVE 0xDEADBEEF
#endif

struct stack
{
	void* head;
    void* current;
    void* end;
    size_t size_of_element;

#ifndef NDEBUG
    size_t status;
#endif
};

stack_t *StackCreate(size_t num_of_elements, size_t size_of_element)
{
	size_t total_size = size_of_element * num_of_elements;
	stack_t* new_stack = NULL;
	void* new = NULL;

	assert(0 != total_size);

	new = malloc(sizeof(stack_t) + total_size);

	assert(NULL != new);

	new_stack = new;
	new_stack->head = (char*)new_stack + sizeof(stack_t);
    new_stack->size_of_element = size_of_element;
    new_stack->current = new_stack->head;
    new_stack->end = (char*)new_stack->head + total_size;

#ifndef NDEBUG
    new_stack->status = ACTIVE;
#endif

    return (new);
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack && ACTIVE == stack->status);

#ifndef NDEBUG
    stack->status = 0lu;
#endif

    free(stack);
}

int StackPush(stack_t *stack, const void *element)
{
	assert(NULL != stack && ACTIVE == stack->status);

    if (stack->current == stack->end)
    {
        return (0);
    }
    
    memcpy(stack->current, element, stack->size_of_element);
    stack->current = (char*)stack->current + stack->size_of_element;
    return (1);  
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack && ACTIVE == stack->status);

    if (stack->current == stack->head)
    {
        return;
    }
    
    stack->current = (char*)stack->current - stack->size_of_element;
}

const void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack && ACTIVE == stack->status);
    
    if (stack->current == stack->head)
    {
        return (NULL);
    }

    return ((char*)stack->current - stack->size_of_element);
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack && ACTIVE == stack->status);
    
    return
    ( ((char*)stack->current - (char*)stack->head) / stack->size_of_element); 
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack && ACTIVE == stack->status);

    return (stack->current == stack->head);
}
