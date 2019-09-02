#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

/* Rev. 0.5*/ 
/* 02.09.19  14:30 */
#include <stddef.h>

typedef struct SList_node SList_node_t;

struct SList_node
{
    void* data;
    SList_node_t* next;
};

typedef int(*is_match_func)(void* data, void* param);
/* only 0 = continue , otherwise - stop*/
typedef int(*operation_func)(void* data, void* param);

/* complexity of malloc */
SList_node_t *SListCreateNode(void *data, SList_node_t *next);

/* complexity of o(1), return new_node */
SList_node_t* SListInsertAfter(SList_node_t *target, SList_node_t *new_node);

/* complexity of o(1),return target */
SList_node_t* SListInsert(const SList_node_t *target, SList_node_t *new_node);

/* complexity of o(1), return the node after the erased one */
SList_node_t* SListRemoveAfter(SList_node_t *target);

/* complexity of o(1), return the node after the erased one */
SList_node_t* SListRemove(const SList_node_t *target);

/* complexity of o(n) */
size_t SListCount(const SList_node_t *head);

/* complexity of o(n) */
void SListFreeAll(SList_node_t *head);

/* complexity of o(n) */
SList_node_t *SListFind(SList_node_t *head, is_match_func *match, void *param);

/* complexity of o(n) */
void SListForEach(SList_node_t* head, operation_func* operation, void* param);

/* complexity of o(n) */
SList_node_t* SListFlip(SList_node_t* head);

/* complexity of o(n) */
int SListHasLoop(const SList_node_t* head);

/* complexity of o(n) */
SList_node_t* SListFindIntersection(SList_node_t* head1, SList_node_t* head2);

#endif


