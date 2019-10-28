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

static int AVLInsertNode(avl_t *avl, avl_node_t *node, void *data);

static size_t AVLHeightUpdate(avl_node_t *node);

static int AVLForEachInOrder(avl_node_t *node, op_func_t op_func, void *param);

static void *AVLFindIfInOrder(avl_node_t *node, find_if_func_t find_if_func, void *param);

static avl_node_t *AVLCreateNode(void *data);

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
    DestroyPostOrder(avl->root);
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
    return (AVLInsertNode(avl, avl->root, data));
}


void AVLRemove(avl_t *avl, const void *data)
{
    avl_node_t *next = NULL, *parent = NULL;
    avl_node_t *node_remove = NULL;
    int nchildren = 0, side = 0;

    assert(avl->root);

    node_remove = AVLFindNode(avl, avl->root, data);

    if (node_remove == avl->root)
    {
        free(avl->root);
        avl->root = NULL;
    }

    switch (AVLCountChildren(node_remove))
    {
        case 0:
        {
            parent = AVLFindParent(avl, avl->root, data);
            side = (parent->child[RIGHT] == node_remove);
            parent->child[side] = NULL;
            free(node_remove);
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
            next = AVLLeftmost(node_remove->child[RIGHT]);
            node_remove->data = next->data;
            AVLRemove(avl, next->data);
            break;
        }
    }
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
        node = node->child[LEFT];
        DestroyPostOrder(node);
        node->child[LEFT] = NULL; /* needed? */
    }

    if (node->child[RIGHT])
    {
        node = node->child[RIGHT];
        DestroyPostOrder(node);
        node->child[RIGHT] = NULL; /* needed? */
    }

    free(node);
}

static size_t AVLSizeTree(avl_node_t *node)
{
    size_t size_left = 0, size_right = 0;

    if (NULL == node)
    {
        return (0);
    }

    size_left = AVLSizeTree(node->child[LEFT]);
    size_right = AVLSizeTree(node->child[RIGHT]);

    return (size_left + size_right + 1);
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

static avl_node_t *AVLFindParent(avl_t *avl, avl_node_t *node, const void *data)
{
    int cmp_res = 0, cmp_res_child = 0, side = 0;

    if (NULL == node)
    {
        return (NULL);
    }

    cmp_res = avl->cmp_func(data, node->data, avl->param);

    /* if node found is the input node return NULL */
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

        return status;
    }

    status = AVLInsertNode(avl, node->child[side], data);
    node->height = AVLHeightUpdate(node);

    return (status);
}

static size_t AVLHeightUpdate(avl_node_t *node)
{
    ssize_t height_left = 0, height_right = 0;
    height_left = (node->child[LEFT] != NULL) ? (ssize_t)(node->child[LEFT]->height) : (-1) ;
    height_right = (node->child[RIGHT] != NULL) ? (ssize_t)(node->child[RIGHT]->height) : (-1) ;

    return (1 + MAX2(height_left, height_right));
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