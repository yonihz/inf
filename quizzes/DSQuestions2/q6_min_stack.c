/* compile command:
gd q6_min_stack.c ../../ds/stack.c -I../../ds/include
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define NELEM 5

typedef enum {SUCCESS = 0, FAILURE = 1} status_t;

status_t PushMinStack(void *data, stack_t *data_stack, stack_t *min_stack);
void PopMinStack(stack_t *data_stack, stack_t *min_stack);
void *GetMinMinStack(stack_t *min_stack);

int main()
{
    int arr[NELEM] = {8, 3, 5, 2, 5};
    stack_t *data_stack = NULL;
    stack_t *min_stack = NULL;
    size_t nelem = NELEM;
    size_t size_elem = sizeof(int);

    data_stack = StackCreate(nelem, size_elem);
    min_stack = StackCreate(nelem, size_elem);

    PushMinStack(&arr[0], data_stack, min_stack);
    printf("GetMin: %d\n", *(int*)GetMinMinStack(min_stack));

    PushMinStack(&arr[1], data_stack, min_stack);
    printf("GetMin: %d\n", *(int*)GetMinMinStack(min_stack));

    PushMinStack(&arr[2], data_stack, min_stack);
    printf("GetMin: %d\n", *(int*)GetMinMinStack(min_stack));

    PushMinStack(&arr[3], data_stack, min_stack);
    printf("GetMin: %d\n", *(int*)GetMinMinStack(min_stack));

    PushMinStack(&arr[4], data_stack, min_stack);
    printf("GetMin: %d\n", *(int*)GetMinMinStack(min_stack));

    StackDestroy(data_stack);
    StackDestroy(min_stack);

    return 0;
}

status_t PushMinStack(void *data, stack_t *data_stack, stack_t *min_stack)
{
    void *top_min = NULL;

    assert(data_stack && min_stack);

    if (0 == StackPush(data_stack, data))
    {
        return FAILURE;
    }

    if (StackIsEmpty(min_stack))
    {
        StackPush(min_stack, data);
        return SUCCESS;
    }

    top_min = (void*)StackPeek(min_stack);

    if (*(int*)top_min < *(int*)data)
    {
        StackPush(min_stack, top_min);
    }
    else
    {
        StackPush(min_stack, data);
    }

    return SUCCESS;
}

void PopMinStack(stack_t *data_stack, stack_t *min_stack)
{
    assert(data_stack && min_stack);

    StackPop(data_stack);
    StackPop(min_stack);
}

void *GetMinMinStack(stack_t *min_stack)
{
    assert(min_stack);

    if (StackIsEmpty(min_stack))
    {
        return NULL;
    }

    return (void*)StackPeek(min_stack);
}