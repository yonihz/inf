/****************************************************************
* 																*
* FILE NAME: rec_str.c							    	    	*
* 																*
* PURPOSE: Recursion functions source file        			    *
*                                                               *
* DATE: 01.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stddef.h> /* size_t, NULL */

#include "rec_str.h"
#include "slist.h"
#include "stack.h"

static int BubbleSortStack(stack_t *stack);
static int RecStrncmp(const char *str1, const char *str2, size_t n);

size_t RecStrlen(const char *str)
{
    assert(NULL != str);

    if ('\0' == *str)
    {
        return (0);
    }

    return (1 + RecStrlen(str+1));
}

int RecStrcmp(const char *str1, const char *str2)
{
    assert(NULL != str1 && NULL != str2);

    if ((*str1 != *str2) || (*str1 == '\0'))
    {
        return (*str1 - *str2);
    }

    return RecStrcmp(str1 + 1, str2 + 1);
}

static int RecStrncmp(const char *str1, const char *str2, size_t n)
{
    assert(NULL != str1 && NULL != str2);

    if ((*str1 != *str2) || (n == 1))
    {
        return (*str1 - *str2);
    }

    return RecStrncmp(str1 + 1, str2 + 1, n - 1);
}

char *RecStrcpy(char *dest, const char *src)
{
    assert(NULL != src && NULL != dest);

    *dest = *src;

    if ('\0' == *src)
    {
        return (dest);
    }

    return (RecStrcpy(dest + 1, src + 1) - 1);
}

char *RecStrcat(char *dest, const char *src)
{
    assert(NULL != src && NULL != dest);

    RecStrcpy((dest + RecStrlen(dest)), src);

    return (dest);
}

char *RecStrstr(const char *haystack, const char *needle)
{
    assert(NULL != haystack && NULL != needle);

    if (*haystack == '\0')
    {
        return NULL;
    }

    if (*haystack == *needle)
    {
        size_t len_needle = RecStrlen(needle);
        size_t len_haystack = RecStrlen(haystack);

        if (len_needle <= len_haystack && RecStrncmp(needle, haystack, len_needle) == 0)
        {
            return (char*)haystack;
        }
    }

    return RecStrstr(haystack + 1, needle);    
}

unsigned int ItrFib(unsigned int n)
{
    unsigned int prev_prev = 0, prev = 1, curr = 1;
    unsigned int i = 0;

    curr = n;
    for (i = 1; i < n; i++)
    {
        curr = prev + prev_prev;
        prev_prev = prev;
        prev = curr;
    }

    return curr;
}

unsigned int RecFib(unsigned int n)
{
    if (n <= 1)
    {
        return n;
    }

    return (RecFib(n-1) + RecFib(n-2));
}

slist_node_t* RecSListFlip(slist_node_t* head)
{
    slist_node_t *fhead = NULL;
    if (head == NULL || head-> next == NULL)
    {
        return head;
    }

    fhead = RecSListFlip(head->next);

    head->next->next = head;
    head->next = NULL;

    return fhead;
}

void SortUnsortedStack(stack_t *stack)
{
    if (BubbleSortStack(stack) == 0)
    {
        return;
    }

    SortUnsortedStack(stack);
}

static int BubbleSortStack(stack_t *stack)
{
    int n = 0;
    int elem1 = 0, elem2 = 0; 

    elem1 = *(int*)StackPeek(stack);
    StackPop(stack);

    if (StackIsEmpty(stack))
    {
        StackPush(stack, &elem1);

        return 0;
    }

    n = BubbleSortStack(stack);

    elem2 = *(int*)StackPeek(stack);

    if (elem1 < elem2)
    {
        StackPop(stack);
        StackPush(stack, &elem1);
        StackPush(stack, &elem2);
        n = 1;
    }
    else
    {
        StackPush(stack, &elem1);  
    }
    
    return n;
}