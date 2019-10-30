#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "avl.h"

#define MAX2(a,b) (((a) > (b)) ? (a) : (b))

enum side {LEFT, RIGHT};

typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    avl_node_t *child[2];
    size_t height;
};

struct avl
{
    cmp_func_t cmp_func;
    void *param;
    avl_node_t *root;
};

static void DestroyPostOrder(avl_node_t *node);
static size_t AVLSizeTree(avl_node_t *node);
static avl_node_t *AVLFindNode(avl_t *avl, avl_node_t *node, const void *data);
static avl_node_t *AVLInsertNode(avl_t *avl, avl_node_t *node, avl_node_t *new_node);
static ssize_t AVLHeightNode(avl_node_t *node);
static int AVLForEachInOrder(avl_node_t *node, op_func_t op_func, void *param);
static void *AVLFindIfInOrder(avl_node_t *node, find_if_func_t find_if_func, void *param);
static avl_node_t *AVLCreateNode(void *data);
static avl_node_t *AVLRemoveNode(avl_t *avl, avl_node_t *node, const void *data);
static avl_node_t *AVLDestroyNode(avl_t *avl, avl_node_t *node);
static avl_node_t *AVLFurthermostToSide(avl_node_t *node, int side);
static int AVLCountChildren(avl_node_t *node);

static int AVLBalanceFactor(avl_node_t *node);
static avl_node_t *AVLRotateToSide(avl_node_t *node, int side);
static avl_node_t *AVLRebalance(avl_node_t *node);

avl_t *AVLCreate(cmp_func_t cmp_func, void *param)
{
    avl_t *avl = (avl_t*)malloc(sizeof(avl_t));
    avl->cmp_func = cmp_func;
    avl->param = param;
    avl->root = NULL;

    return (avl);
}

void AVLDestroy(avl_t *avl)
{
    if (!AVLIsEmpty(avl))
    {
        DestroyPostOrder(avl->root);
    }
    
    free(avl);
    avl = NULL;
}

size_t AVLSize(const avl_t *avl)
{
    return AVLSizeTree(avl->root);
}

size_t AVLHeight(const avl_t *avl)
{
    return (avl->root->height);
}

int AVLIsEmpty(const avl_t *avl)
{
    return (NULL == avl->root);
}

int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t *new_node = AVLCreateNode(data);

    if (NULL == new_node)
    {
        return (-1);
    }

    avl->root = AVLInsertNode(avl, avl->root, new_node);

    return (0);
}


void AVLRemove(avl_t *avl, const void *data)
{
    avl->root = AVLRemoveNode(avl, avl->root, data);

    return;
}


void *AVLFind(avl_t *avl, const void *data)
{
    avl_node_t *node = NULL;
    void *data_found = NULL;
    node = AVLFindNode(avl, avl->root, data);
    if (NULL != node)
    {
        data_found = node->data;
    }

    return (data_found);
}

int AVLForEach(avl_t *avl, op_func_t op_func, void *param)
{
    return(AVLForEachInOrder(avl->root, op_func, param));
}

void *AVLFindIf(avl_t *avl, find_if_func_t find_if_func, void *param)
{
    return(AVLFindIfInOrder(avl->root, find_if_func, param));
}

static void DestroyPostOrder(avl_node_t *node)
{
    if (node->child[LEFT])
    {
        DestroyPostOrder(node->child[LEFT]);
        node->child[LEFT] = NULL;
    }

    if (node->child[RIGHT])
    {
        DestroyPostOrder(node->child[RIGHT]);
        node->child[RIGHT] = NULL;
    }

    free(node);
}

static size_t AVLSizeTree(avl_node_t *node)
{
    size_t size_l = 0, size_r = 0;

    if (NULL == node)
    {
        return (0);
    }

    size_l = AVLSizeTree(node->child[LEFT]);
    size_r = AVLSizeTree(node->child[RIGHT]);

    return (size_l + size_r + 1);
}

static avl_node_t *AVLFindNode(avl_t *avl, avl_node_t *node, const void *data)
{
    int cmp_res = 0, side = 0;

    if (NULL == node)
    {
        return (NULL);
    }

    cmp_res = avl->cmp_func(data, node->data, avl->param);

    if (0 == cmp_res)
    {
        return (node);
    }

    side = cmp_res > 0;
    node = node->child[side];
    return (AVLFindNode(avl, node, data));
}

static avl_node_t *AVLInsertNode(avl_t *avl, avl_node_t *node, avl_node_t *new_node)
{
    int side = 0;

    if (NULL == node)
    {
        return (new_node);
    }

    assert(avl->cmp_func(new_node->data, node->data, avl->param) != 0);

    side = avl->cmp_func(new_node->data, node->data, avl->param) > 0;
    node->child[side] = AVLInsertNode(avl, node->child[side], new_node);
    node = AVLRebalance(node);
    node->height = AVLHeightNode(node);

    return (node);
}

static ssize_t AVLHeightNode(avl_node_t *node)
{
    ssize_t height_l = 0, height_r = 0;
    avl_node_t *child_l = NULL, *child_r = NULL;

    if (NULL == node)
    {
        return (-1);
    }

    child_l = node->child[LEFT];
    child_r = node->child[RIGHT];

    height_l = (child_l != NULL) ? (ssize_t)(child_l->height) : (-1) ;
    height_r = (child_r != NULL) ? (ssize_t)(child_r->height) : (-1) ;

    return(1 + MAX2(height_l, height_r));
}

static int AVLForEachInOrder(avl_node_t *node, op_func_t op_func, void *param)
{
    int status = 0;

    if (node->child[LEFT] && (0 == status))
    {
        status = AVLForEachInOrder(node->child[LEFT], op_func, param);
    }

    if (0 == status)
    {
        status = op_func(node->data, param);  
    }

    if (node->child[RIGHT] && (0 == status))
    {
        status = AVLForEachInOrder(node->child[RIGHT], op_func, param);
    }

    return (status);
}

static void *AVLFindIfInOrder(avl_node_t *node, find_if_func_t find_if_func, void *param)
{
    void *node_found = NULL;

    if (node->child[LEFT] && (NULL == node_found))
    {
        node_found = AVLFindIfInOrder(node->child[LEFT], find_if_func, param);
    }

    if (NULL == node_found)
    {
        if (1 == find_if_func(node->data, param))
        {
            node_found = node;
        }  
    }

    if (node->child[RIGHT] && (NULL == node_found))
    {
        node_found = AVLFindIfInOrder(node->child[RIGHT], find_if_func, param);
    }

    return (node_found);
}

static avl_node_t *AVLCreateNode(void *data)
{
    avl_node_t *node = NULL;

    node = (avl_node_t*)malloc(sizeof(avl_node_t));
    
    if (NULL == node)
    {
        return (NULL);
    }

    node->data = data;
    node->height = 0;
    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;

    return (node);
}

static avl_node_t *AVLRemoveNode(avl_t *avl, avl_node_t *node, const void *data)
{
    int cmp_res = 0, side = 0;

    cmp_res = avl->cmp_func(data, node->data, avl->param);

    if (0 == cmp_res)
    {
        return (AVLDestroyNode(avl, node));
    }

    side = cmp_res > 0;
    node->child[side] = AVLRemoveNode(avl, node->child[side], data);
    node = AVLRebalance(node);
    node->height = AVLHeightNode(node);

    return (node);
}

static avl_node_t *AVLDestroyNode(avl_t *avl, avl_node_t *node)
{
    int side = 0;
    avl_node_t *next = NULL;
    void *data_swap = NULL;

    switch (AVLCountChildren(node))
    {
        case 0:
        {
            free(node);
            node = NULL;
            break;
        }
        case 1:
        {
            side = (NULL != node->child[RIGHT]);
            free(node);
            node = node->child[side];
            break;
        }
        case 2:
        {
            next = AVLFurthermostToSide(node->child[RIGHT], LEFT);
            data_swap = next->data;
            AVLRemoveNode(avl, node->child[RIGHT], next->data);
            /* AVLRemoveNode(avl, node, next->data); */
            node->data = data_swap;
            break;
        }
    }

    return (node);
}

static avl_node_t *AVLFurthermostToSide(avl_node_t *node, int side)
{
    if (NULL == node->child[side])
    {
        return (node);
    }

    return (AVLFurthermostToSide(node->child[side], side));
}

static int AVLCountChildren(avl_node_t *node)
{
    return ((NULL != node->child[LEFT]) + (NULL != node->child[RIGHT]));
}

static int AVLBalanceFactor(avl_node_t *node)
{
    ssize_t height_l = 0, height_r = 0;
    avl_node_t *child_l = NULL, *child_r = NULL;

    child_l = node->child[LEFT];
    child_r = node->child[RIGHT];

    height_l = (child_l != NULL) ? (ssize_t)(child_l->height) : (-1) ;
    height_r = (child_r != NULL) ? (ssize_t)(child_r->height) : (-1) ;

    return (height_l - height_r);    
}

static avl_node_t *AVLRotateToSide(avl_node_t *node, int side)
{
    avl_node_t *new_root = NULL;

    new_root = node->child[!side];
    node->child[!side] = new_root->child[side];
    new_root->child[side] = node;
    
    return new_root;
}

static avl_node_t *AVLRebalance(avl_node_t *node)
{
    int hside1 = 0, hside2 = 0;

    if ((-1 < AVLBalanceFactor(node)) && (1 > AVLBalanceFactor(node)))
    {
        return node;
    }

    hside1 = AVLBalanceFactor(node) < 0;
    hside2 = AVLBalanceFactor(node->child[hside1]);
    hside2 = (hside2 == 0) ? (hside1) : (hside2 < 0);

    if (hside1 == hside2) /* LL or RR */
    {
        return (AVLRotateToSide(node, !hside1));
    }
    else /* LR or RL */
    {
        node->child[hside1] = AVLRotateToSide(node->child[hside1], hside1);
        return (AVLRotateToSide(node, hside2));
    }
}

/* Insert without rebalance */
/*
static int AVLInsertNode(avl_t *avl, avl_node_t *node, void *data)
{
    int status = 0, side = 0;

    if (NULL == avl->root)
    {
        avl->root = AVLCreateNode(data);

        if (avl->root == NULL)
        {
            status = (-1);
        }

        return status;
    }

    assert(avl->cmp_func(data, node->data, avl->param) != 0);

    side = avl->cmp_func(data, node->data, avl->param) > 0;

    if (NULL == node->child[side])
    {
        node->child[side] = AVLCreateNode(data);

        if (node->child[side] == NULL)
        {
            status = (-1);
        }
        node->height = AVLHeightNode(node);

        return status;
    }

    status = AVLInsertNode(avl, node->child[side], data);
    node->height = AVLHeightNode(node);

    return (status);
}
*/

/* Rotate using swap method */
/*
static void AVLRotateLeft(avl_node_t *node)
{
    avl_node_t *hchild = NULL, *temp = NULL;

    hchild = node->child[RIGHT];
    AVLSwapData(node, hchild);
    node->child[RIGHT] = hchild->child[RIGHT];
    temp = hchild->child[LEFT];
    hchild->child[LEFT] = node->child[LEFT];
    hchild->child[RIGHT] = temp;
    node->child[LEFT] = hchild;
}
*/

/*
static avl_node_t *AVLFindParent(avl_t *avl, avl_node_t *node, const void *data)
{
    int cmp_res = 0, cmp_res_child = 0, side = 0;

    if (NULL == node)
    {
        return (NULL);
    }

    cmp_res = avl->cmp_func(data, node->data, avl->param);

    if (0 == cmp_res)
    {
        return (NULL);
    }

    side = cmp_res > 0;
    cmp_res_child = avl->cmp_func(data, node->child[side]->data, avl->param);
    
    if (0 == cmp_res_child)
    {
        return (node);
    }

    node = node->child[side];
    return (AVLFindParent(avl, node, data));
}
*/

/* Insert node without rebalancing */
/*
static int AVLInsertNode(avl_t *avl, avl_node_t *node, void *data)
{
    int status = 0, side = 0;

    if (NULL == avl->root)
    {
        avl->root = AVLCreateNode(data);

        if (avl->root == NULL)
        {
            status = (-1);
        }

        return status;
    }

    assert(avl->cmp_func(data, node->data, avl->param) != 0);

    side = avl->cmp_func(data, node->data, avl->param) > 0;

    if (NULL == node->child[side])
    {
        node->child[side] = AVLCreateNode(data);

        if (node->child[side] == NULL)
        {
            status = (-1);
        }
        node->height = AVLHeightNode(node);

        return status;
    }

    status = AVLInsertNode(avl, node->child[side], data);
    AVLBalanceIfNeeded(node);
    node->height = AVLHeightNode(node);

    return (status);
}
*/

/* Remove without rebalancing */
/*
static void AVLRemoveNode(avl_t *avl, avl_node_t *node, const void *data)
{
    avl_node_t *next = NULL, *parent = NULL, *node_remove = NULL;
    void *data_swap;
    int side = 0;

    UNUSED(node);

    node_remove = AVLFindNode(avl, avl->root, data);

    switch (AVLCountChildren(node_remove))
    {
        case 0:
        {
            if (node_remove == avl->root)
            {
                avl->root = NULL;
                free(node_remove);
            }
            else
            {
                parent = AVLFindParent(avl, avl->root, data);
                side = ((NULL != parent->child[RIGHT]) && (parent->child[RIGHT] == node_remove));
                parent->child[side] = NULL;
                free(node_remove);
            }
            break;
        }
        case 1:
        {
            side = (NULL != node_remove->child[RIGHT]);
            parent = node_remove;
            node_remove = parent->child[side];
            parent->data = node_remove->data;
            parent->child[LEFT] = node_remove->child[LEFT];
            parent->child[RIGHT] = node_remove->child[RIGHT];
            free(node_remove);
            break;
        }
        case 2:
        {
            next = AVLFurthermostToSide(node_remove->child[RIGHT], LEFT);
            data_swap = next->data;
            AVLRemoveNode(avl, node_remove->child[RIGHT], next->data);
            node_remove->data = data_swap;
            break;
        }
    }
    return;
}
*/
