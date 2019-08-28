#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define ACTIVE 0xDEADBEEF

int isValidStack(const stack_t *stack);

struct stack
{
    void* head;
    void* current;
    void* end;
    size_t size_of_element;
    size_t status;
};

stack_t *StackCreate(size_t num_of_elements, size_t size_of_element)
{
	size_t max_size = 1e6;
	size_t total_size = size_of_element * num_of_elements;

    stack_t* new = malloc(sizeof(stack_t));
    new->head = malloc(size_of_element * num_of_elements);

    if (0 == total_size || max_size < total_size)
    {
        return (NULL);
    } 

    if (NULL == new || NULL == new->head)
    {
        return (NULL);
    } 

    new->size_of_element = size_of_element;
    new->status = ACTIVE;
    new->current = new->head;
    new->end = (char*)new->head + total_size;
    
    return (new);
}

void StackDestroy(stack_t *stack)
{
    if (0 == isValidStack(stack))
    {
        return;
    }

    stack->status = 0lu;
    free(stack->head);
    free(stack);
}

int StackPush(stack_t *stack, const void *element)
{
    if (0 == isValidStack(stack))
    {
        return (-1);
    }

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
    if (0 == isValidStack(stack))
    {
        return;
    }

    if (stack->current == stack->head)
    {
        return;
    }
    
    stack->current = (char*)stack->current - stack->size_of_element;
}

const void *StackPeek(const stack_t *stack)
{
    if (0 == isValidStack(stack))
    {
        return (NULL);
    }
    
    if (stack->current == stack->head)
    {
        return (NULL);
    }

    return ((char*)stack->current - stack->size_of_element);
}

size_t StackSize(const stack_t *stack)
{
    if (0 == isValidStack(stack))
    {
        return (0ul);
    }
    
    return
    ( ((char*)stack->current - (char*)stack->head) / stack->size_of_element); 
}

int StackIsEmpty(const stack_t *stack)
{
    if (0 == isValidStack(stack))
    {
        return (0);
    }

    return (stack->current == stack->head);
}

int isValidStack(const stack_t *stack)
{
    if (NULL == stack)
    {
        return (0);
    }

    if (ACTIVE != stack->status)
    {
        return (0);
    }

    return (1); 
}

