#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "bst.h"

static bst_itr_t BSTRightmost(bst_itr_t itr);
static bst_itr_t BSTLeftmost(bst_itr_t itr);

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

bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{
    bst_t *bst = (bst_t*)malloc(sizeof(bst_t));
    
    if (NULL == bst)
    {
        return (NULL);
    }

    bst->cmp_func = cmp_func;
    bst->param = param;
    bst->end.child[0] = NULL;
    bst->end.child[1] = NULL;
    bst->end.parent = NULL;
    return (bst);
}

void BSTDestroy(bst_t *bst)
{
    int parent_pos = 0; /* position relative to parent: 1 is right, 0 is left */
    bst_itr_t parent = NULL;
    bst_itr_t itr = BSTBegin(bst);

    /* traverse post-order (left right root) */
    while (!BSTIsSame(itr,BSTEnd(bst)))
    {
        itr = BSTLeftmost(itr);
        if (itr->child[1])
        {
            itr = itr->child[1];
            continue;
        }
        else
        {
            parent = itr->parent;
            parent_pos = (parent->child[1] == itr);
            parent->child[parent_pos] = NULL;
            free(itr);
            itr = parent;
        }   
    }
    free(bst);
}

bst_itr_t BSTFind(bst_t *bst, const void *data)
{
    bst_itr_t itr = NULL;
    int cmp_res = 0;
    itr = bst->end.child[0];
    cmp_res = bst->cmp_func(data, itr->data, bst->param);
    while (cmp_res)
    {
        itr = itr->child[cmp_res > 0];
        if (NULL == itr)
        {
            return BSTEnd(bst);
        }
        cmp_res = bst->cmp_func(data, itr->data, bst->param);
    }
    return (itr);
}

bst_itr_t BSTInsert(bst_t *bst, void *data)
{
    bst_itr_t new = (bst_itr_t)malloc(sizeof(bst_node_t));
    bst_itr_t itr;
    int cmp_res = 0;

    if (NULL == new)
    {
        return (NULL);
    }
    
    /* find parent to insert child */
    itr = (bst_itr_t)&(bst->end);
    while (itr->child[cmp_res])
    {
        itr = itr->child[cmp_res];
        cmp_res = (bst->cmp_func(data, itr->data, bst->param));
        assert(0 != cmp_res);
        cmp_res = cmp_res > 0;
    }

    itr->child[cmp_res] = new;
    new->data = data;
    new->parent = itr;
    new->child[0] = NULL;
    new->child[1] = NULL;
    return new;
}

void BSTRemove(bst_itr_t itr)
{
    int parent_pos = 0; /* position relative to parent: 1 is right, 0 is left */
    bst_itr_t child = NULL;
    parent_pos = (itr->parent->child[1] == itr);
    
    /* case 1: itr has no children */ 
    if (itr->child[0] == NULL && itr->child[1] == NULL)
    {
        itr->parent->child[parent_pos] = NULL;
        free(itr);
        return;
    }

    /* case 2: itr has only one child */ 
    if ((itr->child[0] != NULL) ^ (itr->child[1] != NULL))
    {
        child = itr->child[1] ? itr->child[1] : itr->child[0];
        itr->parent->child[parent_pos] = child;
        child->parent = itr->parent;
        free(itr);
        return;
    }

    /* case 3: itr has two children */ 
    child = BSTNext(itr);
    itr->data = child->data;    
    if (BSTIsSame(child, itr->child[1]))
    {
        itr->child[1] = child->child[1];                
    }
    else
    {
        child->parent->child[0] = child->child[1];
    }
    if (child->child[1])
    {
        child->child[1]->parent = child->parent;
    }
    free(child);
}

int BSTForEach(bst_itr_t itr_start, bst_itr_t itr_end, op_func_t op_func, void *param)
{
    int status = 0;
    while ((0 == status) && !BSTIsSame(itr_start, itr_end))
    {
        status = op_func(itr_start->data, param);
        itr_start = BSTNext(itr_start);
    }
    return status;
}

size_t BSTSize(const bst_t *bst)
{
    size_t size = 0;
    bst_itr_t itr = BSTBegin(bst);
    
    while (!BSTIsSame(itr,BSTEnd(bst)))
    {
        itr = BSTNext(itr);
        ++size;
    }
    return (size);
}

int BSTIsEmpty(const bst_t *bst)
{
    return (NULL == bst->end.child[0]);
}

void *BSTGetData(bst_itr_t itr)
{
    if (itr == NULL)
    {
        return (NULL);
    }
    return (itr->data);
}

bst_itr_t BSTNext(bst_itr_t itr)
{
    assert(itr->parent);

    if (itr->child[1])
    {
        itr = itr->child[1];
        itr = BSTLeftmost(itr);
    }
    else
    {
        while (BSTIsSame(itr, itr->parent->child[1]))
        {
            itr = itr->parent;
        }
        itr = itr->parent;
    }
    return (itr);
}

bst_itr_t BSTPrev(bst_itr_t itr)
{
    if (itr->child[0])
    {
        itr = itr->child[0];
        itr = BSTRightmost(itr);
    }
    else
    {
        while (BSTIsSame(itr, itr->parent->child[0]))
        {
            itr = itr->parent;
            assert(itr->parent);
        }
        itr = itr->parent;
    }
    return (itr);
}

bst_itr_t BSTBegin(const bst_t *bst)
{
    bst_itr_t itr = (bst_itr_t)&(bst->end);
    itr = BSTLeftmost(itr);
    return (itr);
}

bst_itr_t BSTEnd(const bst_t *bst)
{
    return ((bst_itr_t)&(bst->end));
}

int BSTIsSame(bst_itr_t itr1, bst_itr_t itr2)
{
    return (itr1 == itr2);
}

static bst_itr_t BSTRightmost(bst_itr_t itr)
{
    while (itr->child[1])
    {
        itr = itr->child[1];
    }
    return (itr);   
}

static bst_itr_t BSTLeftmost(bst_itr_t itr)
{
    while (itr->child[0])
    {
        itr = itr->child[0];
    }
    return (itr);   
}