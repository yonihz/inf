#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

#define SIZE 10

slist_node_t *PivotSort(slist_node_t *head, int pivot);
void PrintSList(slist_node_t *head);

int main()
{
	int arr[SIZE] = {1, 7, 2, 9, 18, 13, 3, 5, 10, 19};
	size_t i = 0;
    int pivot = 11;
	slist_node_t* head = NULL;

	for (i = 0; i < SIZE; i++)
	{
		head = SListCreateNode(&arr[i], head);
	}

    printf("List before pivot sort:\n");
    PrintSList(head);

    printf("List after pivot sort (pivot = %d):\n", pivot);
    head = PivotSort(head, pivot);
    PrintSList(head);

    return 0;
}

slist_node_t *PivotSort(slist_node_t *head, int pivot)
{
    slist_node_t *left_head = NULL, *left_last = NULL;
    slist_node_t *right_head = NULL, *right_last = NULL;
    slist_node_t *new_head = NULL;
    int data = 0;

    if (head == NULL)
    {
        return NULL;
    }

    while (NULL != head)
    {
        data = *(int*)(head->data);
        
        if (data < pivot)
        {
            if (left_head == NULL)
            {
                left_head = head;
                left_last = head;
            }
            else
            {
                left_last->next = head;
                left_last = head;
            }
        }
        else
        {
            if (right_head == NULL)
            {
                right_head = head;
                right_last = head;
            }
            else
            {
                right_last->next = head;
                right_last = head;
            }           
        }

        head = head->next;
    }

    if (right_head != NULL)
    {
        right_last->next = NULL;
    }

    if (left_head == NULL)
    {
        new_head = right_head;
    }

    else
    {
        new_head = left_head;
        left_last->next = right_head;
    }

    return new_head;
}

void PrintSList(slist_node_t *head)
{
    while (head)
    {
        printf("%d ", *(int*)(head->data));
        head = head->next;
    }

    printf("\n");
}