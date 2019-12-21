#include <stdlib.h>
#include <assert.h>

#include "bst.h"

enum side {LEFT, RIGHT};

typedef struct bst_node bst_node_t;

struct bst_node
{
    void* data;
    bst_node_t *child[2];
    bst_node_t *parent;
};

struct bst
{
    cmp_func_t cmp_func;
    bst_node_t end;
    void* param; 
};

bst_itr_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *new = NULL, *parent = NULL;
    int cmp_res = 0, side = 0;

    parent = (bst_node_t*)&(bst->end);
    while (parent->child[side])
    {
        parent = parent->child[side];
        cmp_res = (bst->cmp_func(data, parent->data, bst->param));
        if (0 == cmp_res)
        {
            return BSTEnd(bst);
        }
        side = cmp_res > 0;
    }

    new = CreateNode(data);

    if (NULL == new)
    {
        return BSTEnd(bst);
    }

    parent->child[side] = new;
    new->parent = parent;

    return (NodeToItr(new));
}

bst_itr_t BSTInsert2(bst_t *bst, void *data)
{
    bst_node_t *new = NULL;

    new = CreateNode(data);

    if (NULL == new)
    {
        return BSTEnd(bst);
    }

    bst->end.child[LEFT] = RecBSTInsert(bst, bst->end.child[LEFT], new);

    return (NodeToItr(new));
}

bst_node_t *RecBSTInsert(bst_t *bst, bst_node_t *node, bst_node_t *new)
{
    int cmp_res = 0, side = 0;

    if (node == NULL)
    {
        return new;
    }

    cmp_res = (bst->cmp_func(new->data, node->data, bst->param));
    side = cmp_res > 0;

    node->child[side] = RecBSTInsert(bst, node->child[side], new);

    return node;
}