#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

/* Rev. 1.0*/ 
/* 03.09.19  10:50 */
#include <stddef.h>

typedef struct slist_node slist_node_t;

struct slist_node
{
    void* data;
    slist_node_t* next;
};
/*when found return 0*/
typedef int(*is_match_func)(const void* data, void* param);
/* only 0 = continue , otherwise - stop*/
typedef int(*operation_func)(void* data, void* param);

/* complexity of malloc,when nested the inner most points to NULL */
slist_node_t *SListCreateNode(void *data, slist_node_t *next);

/* complexity of o(1), return new_node */
slist_node_t* SListInsertAfter(slist_node_t *target, slist_node_t *new_node);

/* complexity of o(1),return target */
slist_node_t* SListInsert(slist_node_t *target, slist_node_t *new_node);

/* complexity of o(1), return the node after the erased one */
slist_node_t* SListRemoveAfter(slist_node_t *target);

/* complexity of o(1), return the node after the erased one
can not remove the last node in the list */
slist_node_t* SListRemove(slist_node_t *target);

/* complexity of o(n) ,if loop return 0*/
size_t SListCount(const slist_node_t *head);

/* complexity of o(n) */
void SListFreeAll(slist_node_t *head);

/* complexity of o(n) if loop return NULL*/
slist_node_t *SListFind(slist_node_t *head, is_match_func match, void *param);

/* complexity of o(n),if loop return NULL */
void SListForEach(slist_node_t* head, operation_func operation, void* param);

/* complexity of o(n),if loop return NULL*/
slist_node_t* SListFlip(slist_node_t* head);

/* complexity of o(n) */
int SListHasLoop(const slist_node_t* head);

/* complexity of o(n),return the mutual node. if loop return NULL */
slist_node_t* SListFindIntersection(slist_node_t* head1, slist_node_t* head2);

#endif


