#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

/* Rev. 0.0 */ 
/* 01.09.19  18:30 */
#include <stddef.h>

typedef struct node node_t;

struct node
{
    void* data;
    node_t* next;
};

typedef int(*cmp_func)(void* data, void* node_value);
typedef void(*operation_func)(node_t* node);

/* complexity of malloc */
node_t *SLLCreateNode(const void *data);

/* complexity of o(1) */
void SLLInsertAfter(node_t *target, node_t *new_node);

/* complexity of o(1) */
void SLLInsert(const node_t *target, node_t *new_node);

/* complexity of o(1) */
void SLLRemoveAfter(node_t *target);

/* complexity of o(1) */
void SLLRemove(const node_t *target);

/* complexity of o(n) */
size_t SLLCount(const node_t* head);

/* complexity of o(n) */
void SLLFreeAll(node_t* head);

/* complexity of o(n) */
node_t *SLLFind(const node_t* head, cmp_func* cmp, const void* data);

/* complexity of o(n) */
void SLLForEach(node_t* head, operation_func* operation);

/* complexity of o(n) */
node_t* SLLFlip(node_t* head);

/* complexity of o(n) */
int SLLHasLoop(const node_t* head);

/* complexity of o(n) */
node_t* SLLFindIntersection(const node_t* head1, const node_t* head2);

#endif


