#include <stdlib.h>

#include "bst.h"

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
    return (bst);
}

void BSTDestroy(bst_t *bst)
{
    int parent_pos = 0; /* position relative to parent: 1 is right, 0 is left */
    bst_itr_t parent = NULL;
    bst_itr_t itr = BSTBegin(bst);

    while (!BSTIsSame(itr,BSTEnd(bst)))
    {
        while (itr->child[0])
        {
            itr = itr->child[0];
        }
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
}

/*bst_itr_t BSTFind(bst_t *bst, const void *data)*/

bst_itr_t BSTInsert(bst_t *bst, void *data)
{
    bst_itr_t new = (bst_itr_t)malloc(sizeof(bst_node_t));
    bst_itr_t itr;
    int cmp_res = 0;
    itr = (const bst_itr_t)&(bst->end);

    while (itr->child[cmp_res])
    {
        itr = itr->child[cmp_res];
        if (0 == cmp_res)
        {
            return BSTEnd(bst);
        }
        cmp_res = ((bst->cmp_func(data, itr->data, NULL)) > 0);
    }
    itr->child[cmp_res] = new;
    return new;
}

/*void BSTRemove(bst_itr_t itr)*/

/*int BSTForEach(bst_itr_t itr_start, bst_itr_t itr_end, op_func_t op_func, void *param)*/

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
    return (itr->data);
}

bst_itr_t BSTNext(bst_itr_t itr)
{
    if (itr->child[1])
    {
        itr = itr->child[1];
        while (itr->child[0])
        {
            itr = itr->child[0];
        }
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
        itr = itr->child[1];
        while (itr->child[1])
        {
            itr = itr->child[1];
        }
    }
    else
    {
        while (BSTIsSame(itr, itr->parent->child[0]))
        {
            itr = itr->parent;
        }
        itr = itr->parent;
    }
    return (itr);
}

bst_itr_t BSTBegin(const bst_t *bst)
{
    bst_itr_t itr = (const bst_itr_t)&(bst->end);
    
    while (itr->child[0])
    {
        itr = itr->child[0];
    }
    return (itr);
}

bst_itr_t BSTEnd(const bst_t *bst)
{
    return ((const bst_itr_t)&(bst->end));
}

int BSTIsSame(bst_itr_t itr1, bst_itr_t itr2)
{
    return (itr1 == itr2);
}