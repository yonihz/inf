/****************************************************************
* 																*
* FILE NAME: bst.c						    					*
* 																*
* PURPOSE: BST functions source file		    				*
*                                                               *
* DATE: 20.10.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc, free */
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

static int ParentSide(bst_node_t *node);
static int NChildren(bst_node_t *node);
static bst_node_t *FurthermostToSide(bst_node_t *node, int side);
static bst_node_t *CreateNode(void *data);
static bst_node_t *ItrToNode(bst_itr_t itr);
static bst_itr_t NodeToItr(bst_node_t *node);

bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{
    bst_t *bst = (bst_t*)malloc(sizeof(bst_t));
    
    if (NULL == bst)
    {
        return (NULL);
    }

    bst->cmp_func = cmp_func;
    bst->param = param;
    bst->end.child[LEFT] = NULL;
    bst->end.child[RIGHT] = NULL;
    bst->end.parent = NULL;

    return (bst);
}

void BSTDestroy(bst_t *bst)
{
    bst_node_t *parent = NULL, *node = NULL;

    node = ItrToNode(BSTBegin(bst));

    /* traverse post-order (left right root) */
    while (!BSTIsSame(NodeToItr(node), BSTEnd(bst)))
    {
        node = FurthermostToSide(node, LEFT);
        if (node->child[RIGHT])
        {
            node = node->child[RIGHT];
            continue;
        }
        else
        {
            parent = node->parent;
            parent->child[ParentSide(node)] = NULL;
            free(node);
            node = parent;
        }   
    }
    free(bst);
}

bst_itr_t BSTFind(bst_t *bst, const void *data)
{
    bst_node_t *node = NULL;
    int cmp_res = 0, side = 0;

    if (BSTIsEmpty(bst))
    {
        return BSTEnd(bst);
    }

    node = bst->end.child[LEFT];
    cmp_res = bst->cmp_func(data, node->data, bst->param);
    while (0 != cmp_res)
    {
        side = cmp_res > 0;
        node = node->child[side];
        if (NULL == node)
        {
            return BSTEnd(bst);
        }
        cmp_res = bst->cmp_func(data, node->data, bst->param);
    }

    return (node);
}

bst_itr_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *new = NULL, *parent = NULL;
    int cmp_res = 0, side = 0;

    /* find parent to insert new child */
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

void BSTRemove(bst_itr_t itr)
{
    bst_node_t *child = NULL, *node = NULL, *next = NULL;
    int nchildren = 0, side = 0;

    node = ItrToNode(itr);
    nchildren = NChildren(node);
    switch (nchildren)
    {
        case 0:
        {
            node->parent->child[ParentSide(node)] = NULL;
            break;
        }
        case 1:
        {
            side = (NULL != node->child[RIGHT]);
            child = (node->child[side]);
            node->parent->child[ParentSide(node)] = child;
            child->parent = node->parent;
            break;
        }
        case 2:
        {
            next = ItrToNode(BSTNext(NodeToItr(node)));
            node->data = next->data;    
            if (BSTIsSame(NodeToItr(next), NodeToItr(node->child[RIGHT])))
            {
                node->child[RIGHT] = next->child[RIGHT];                
            }
            else
            {
                next->parent->child[LEFT] = next->child[RIGHT];
            }
            if (next->child[RIGHT])
            {
                next->child[RIGHT]->parent = next->parent;
            }
            node = next;
            break;
        }
    }

    free(node);

    return;
}

int BSTForEach(bst_itr_t itr_start, bst_itr_t itr_end, op_func_t op_func, void *param)
{
    int status = 0;
    bst_node_t *node_start = NULL, *node_end = NULL;

    node_start = ItrToNode(itr_start);
    node_end = ItrToNode(itr_end);    
    while ((0 == status) && !BSTIsSame(NodeToItr(node_start), NodeToItr(node_end)))
    {
        status = op_func(node_start->data, param);
        node_start = ItrToNode(BSTNext(NodeToItr(node_start)));
    }

    return status;
}

size_t BSTSize(const bst_t *bst)
{
    size_t size = 0;
    bst_node_t *node = NULL;

    node = ItrToNode(BSTBegin(bst));
    while (!BSTIsSame(ItrToNode(node),BSTEnd(bst)))
    {
        node = ItrToNode(BSTNext(NodeToItr(node)));
        ++size;
    }

    return (size);
}

int BSTIsEmpty(const bst_t *bst)
{
    return (NULL == bst->end.child[LEFT]);
}

void *BSTGetData(bst_itr_t itr)
{
    bst_node_t *node;

    node = ItrToNode(itr);

    return (node->data);
}

bst_itr_t BSTNext(bst_itr_t itr)
{
    bst_node_t *node = NULL;

    node = ItrToNode(itr);
    assert(node->parent);

    if (node->child[RIGHT])
    {
        node = node->child[RIGHT];
        node = FurthermostToSide(node, LEFT);
    }
    else
    {
        while (ParentSide(node) == RIGHT)
        {
            node = node->parent;
        }
        node = node->parent;
    }

    return (NodeToItr(node));
}

bst_itr_t BSTPrev(bst_itr_t itr)
{
    bst_node_t *node = NULL;

    node = ItrToNode(itr);
    if (node->child[LEFT])
    {
        node = node->child[LEFT];
        node = FurthermostToSide(node, RIGHT);
    }
    else
    {
        while (ParentSide(node) == LEFT)
        {
            node = node->parent;
            assert(itr->parent);
        }
        node = node->parent;
    }

    return (NodeToItr(node));
}

bst_itr_t BSTBegin(const bst_t *bst)
{
    bst_node_t *node = (bst_node_t*)&(bst->end);

    node = FurthermostToSide(node, LEFT);

    return (NodeToItr(node));
}

bst_itr_t BSTEnd(const bst_t *bst)
{
    return (NodeToItr((bst_node_t*)&(bst->end)));
}

int BSTIsSame(bst_itr_t itr1, bst_itr_t itr2)
{
    return (itr1 == itr2);
}

static int NChildren(bst_node_t *node)
{
    return ((NULL != node->child[LEFT]) + (NULL != node->child[RIGHT]));   
}

static int ParentSide(bst_node_t *node)
{
    return (node->parent->child[RIGHT] == node);
}

static bst_node_t *FurthermostToSide(bst_node_t *node, int side)
{
    while (node->child[side])
    {
        node = node->child[side];
    }

    return (node);
}

static bst_node_t *ItrToNode(bst_itr_t itr)
{
    return itr;
}

static bst_itr_t NodeToItr(bst_node_t *node)
{
    return node;
}

static bst_node_t *CreateNode(void *data)
{
    bst_node_t *new = NULL;

    new = (bst_node_t*)malloc(sizeof(bst_node_t));

    if (NULL == new)
    {
        return (NULL);
    }

    new->data = data;
    new->child[LEFT] = NULL;
    new->child[RIGHT] = NULL;

    return new; 
}