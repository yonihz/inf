/****************************************************************
* 																*
* FILE NAME: dhcp.c						    					*
* 																*
* PURPOSE: DHCP functions source file		    				*
*                                                               *
* DATE: 14.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h>

#include "dhcp.h"

#define IP4_SIZE 32

typedef struct dhcp_node dhcp_node_t;

/* Recursive tree traversal functions */
static dhcp_node_t *RecAlloc(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height);
static dhcp_node_t *RecFree(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height);
static size_t RecSize(dhcp_node_t *node, unsigned int height);
static void DHCPDestroyNode(dhcp_node_t *node);

/* Default addresses create functions */
static ip_t GetBroadcastIP(ip_t net_addr, size_t prefix);
static ip_t GetServerIP(ip_t net_addr);

/* Other service functions */
static dhcp_node_t *DHCPCreateNode(void);
static int IsFullSubtree(dhcp_node_t *node);
static int DHCPCountChildren(dhcp_node_t *node);

struct dhcp_node {
    dhcp_node_t *child[2];
    int is_full;
};

struct dhcp {
    dhcp_node_t *root;
    ip_t net_addr;
    size_t host_size;
};

dhcp_t *DHCPCreate(ip_t net_addr, size_t prefix)
{
    ip_t out_ip = 0;
    int status = SUCCESS;
    dhcp_t *dhcp = NULL;
    unsigned int host_mask = 0;

    dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->net_addr = net_addr;
    dhcp->host_size = IP4_SIZE - prefix;
    host_mask = (1 << dhcp->host_size) - 1;

    if (prefix > IP4_SIZE - 2 ||
        prefix < 1 ||
        (net_addr & host_mask) != 0)
    {
        free(dhcp);
        dhcp = NULL;
        return (NULL);
    }

    dhcp->root = DHCPCreateNode();
    assert(dhcp->root);

    /*  Default addresses for prefix = 24:
        Broadcast: xxx.xxx.xxx.255
        Server: xxx.xxx.xxx.1
        Network: xxx.xxx.xxx.0
    */

    status = !((status == SUCCESS) && (SUCCESS == DHCPAlloc(dhcp, net_addr, &out_ip)));
    status = !((status == SUCCESS) && (SUCCESS == DHCPAlloc(dhcp, GetBroadcastIP(net_addr, dhcp->host_size), &out_ip)));
    status = !((status == SUCCESS) && (SUCCESS == DHCPAlloc(dhcp, GetServerIP(net_addr), &out_ip)));

    if (SUCCESS != status)
    {
        DHCPDestroy(dhcp);
        return (NULL);
    }

    return (dhcp);
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    DHCPDestroyNode(dhcp->root);
    dhcp->root = NULL;

    free(dhcp);
    dhcp = NULL;
}

dhcp_ret_val_t DHCPAlloc(dhcp_t *dhcp, ip_t req_ip, ip_t *out_ip)
{
    int status = SUCCESS;
    unsigned int host = 0, host_mask = 0;

    if (0 != dhcp->root->is_full)
    {
        return (NO_FREE_IPS);
    }

    host_mask = (1 << dhcp->host_size) - 1;
    host = req_ip & host_mask;

    if (req_ip > GetBroadcastIP(dhcp->net_addr, dhcp->host_size) ||
        req_ip < dhcp->net_addr)
    {
        return (OUT_OF_RANGE);
    }

    RecAlloc(dhcp->root, &status, &host, dhcp->host_size);

    *out_ip = dhcp->net_addr + host;

    return (status);
}

dhcp_ret_val_t DHCPFree(dhcp_t *dhcp, ip_t ip)
{
    int status = SUCCESS;
    unsigned int host = 0, host_mask = 0;

    if (ip >= GetBroadcastIP(dhcp->net_addr, dhcp->host_size) ||
        ip <= GetServerIP(dhcp->net_addr))
    {
        return (OUT_OF_RANGE);
    }

    host_mask = (1 << dhcp->host_size) - 1;
    host = ip & host_mask;
    RecFree(dhcp->root, &status, &host, dhcp->host_size);

    return (status);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    unsigned int size = 0;
    
    size = (1 << dhcp->host_size);
    return (size - RecSize(dhcp->root, dhcp->host_size));
}

static dhcp_node_t *DHCPCreateNode(void)
{
    dhcp_node_t *node = NULL;

    node = (dhcp_node_t*)malloc(sizeof(dhcp_node_t));

    if (NULL == node)
    {
        return (NULL);
    }

    node->child[0] = NULL;
    node->child[1] = NULL;
    node->is_full = 0;

    return (node);
}

static dhcp_node_t *RecAlloc(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height)
{
    int next_child_side = 0;

    if (NULL == node)
    {
        node = DHCPCreateNode();
        if (NULL == node)
        {
            *status = SYSTEM_ERROR;
            return (NULL);
        }
    }

    if (0 == height)
    {
        node->is_full = 1;
        *status = SUCCESS;
        return (node);
    }

    /* Side of next child is determined by the bit corresponding to current height */
    next_child_side = ((*host & (1lu << (height - 1))) != 0);

    /* If next child is full then change to child on the other side */
    if (NULL != node->child[next_child_side] && 
        0 != node->child[next_child_side]->is_full)
    {
        next_child_side = !next_child_side;
    }

    /* Change the output host according to the full nodes found in the tree */
    *host = (~(1 << (height - 1)) & *host) | (next_child_side << (height - 1));
    node->child[next_child_side] = RecAlloc(node->child[next_child_side], status, host, height - 1);
    node->is_full = IsFullSubtree(node);

    if (0 == DHCPCountChildren(node))
    {
        free(node);
        node = NULL;      
    }

    return (node);
}

static dhcp_node_t *RecFree(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height)
{
    int next_child_side = 0;

    if (0 == height)
    {
        free(node);
        node = NULL;
        *status = SUCCESS;

        return (NULL);
    }

    /* Side of next child is determined by the bit corresponding to current height */
    next_child_side = (*host & (1lu << (height - 1))) != 0;

    if (NULL == node->child[next_child_side])
    {
        *status = DOUBLE_FREE_FAILURE;
        return (node);
    }

    node->child[next_child_side] = RecFree(node->child[next_child_side], status, host, height - 1);
    node->is_full = IsFullSubtree(node);

    if (0 == DHCPCountChildren(node))
    {
        free(node);
        node = NULL;      
    }

    return (node);
}

static int IsFullSubtree(dhcp_node_t *node)
{
    int is_full = 0;

    if (node->child[0] && node->child[1] &&
        node->child[0]->is_full && node->child[1]->is_full)
    {
            is_full = 1;
    }

    return (is_full);
}

static void DHCPDestroyNode(dhcp_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    DHCPDestroyNode(node->child[0]);
    DHCPDestroyNode(node->child[1]);
    free(node);
    node = NULL;
}

static int DHCPCountChildren(dhcp_node_t *node)
{
    return ((NULL != node->child[0]) + (NULL != node->child[1]));
}

static size_t RecSize(dhcp_node_t *node, unsigned int height)
{
    size_t size_0 = 0, size_1 = 0;

    if (NULL == node)
    {
        return (0);
    }

    if (0 == height)
    {
        return (1);
    }

    size_0 = RecSize(node->child[0], height - 1);
    size_1 = RecSize(node->child[1], height - 1);

    return (size_0 + size_1);
}

static ip_t GetBroadcastIP(ip_t net_addr, size_t host_size)
{
    unsigned int host_mask = 0;

    host_mask = (1 << host_size) - 1;
    
    return (net_addr | host_mask);
}

static ip_t GetServerIP(ip_t net_addr)
{
    return (net_addr + 1);
}