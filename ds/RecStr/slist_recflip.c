#include 

slist_node_t* RecSListFlip(slist_node_t* head);

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