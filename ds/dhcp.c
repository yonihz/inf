#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "dhcp.h"

#define IP4_BIT_RANGE 32

typedef struct dhcp_node dhcp_node_t;

static dhcp_node_t *DHCPCreateNode(void);
static dhcp_node_t *RecAlloc(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height);
static dhcp_node_t *RecFree(dhcp_node_t *node, int *status, unsigned int *host, unsigned int height);
static int IsFullNode(dhcp_node_t *node, unsigned int height);
static void DHCPDestroyNode(dhcp_node_t *node);
static int DHCPCountChildren(dhcp_node_t *node);
static size_t RecSize(dhcp_node_t *node, unsigned int height);
static ip_t GetBroadcastIP(ip_t net_addr, size_t prefix);
static ip_t GetServerIP(ip_t net_addr);
static void PrintIP(ip_t ip);

struct dhcp_node {
    dhcp_node_t *child[2];
    int is_full;
};

struct dhcp {
    dhcp_node_t *root;
    ip_t net_addr;
    size_t prefix;
};

dhcp_t *DHCPCreate(ip_t net_addr, size_t prefix)
{
    ip_t out_ip = 0;
    int status = 0;
    dhcp_t *dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));

    if (NULL == dhcp)
    {
        return (NULL);
    }

    assert(prefix > 2);
    dhcp->net_addr = net_addr;
    dhcp->prefix = prefix;
    dhcp->root = DHCPCreateNode();
    assert(dhcp->root);

    /* BC: xxx.xxx.xxx.255, Server: xxx.xxx.xxx.1, Network: xxx.xxx.xxx.0 */

    printf("Alloc NET IP:\n");
    status |= DHCPAlloc(dhcp, net_addr, &out_ip);
    printf("Alloc BC IP:\n");
    status |= DHCPAlloc(dhcp, GetBroadcastIP(net_addr, prefix), &out_ip);
    printf("Alloc SERVER IP:\n");
    status |= DHCPAlloc(dhcp, GetServerIP(net_addr), &out_ip);

    if (0 != status)
    {
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
    unsigned int host = 0, host_mask = 0, host_bit_range = 0;

    printf("req_ip: ");
    PrintIP(req_ip);

    if (0 != dhcp->root->is_full)
    {
        return (NO_FREE_IPS);
    }

    host_bit_range = IP4_BIT_RANGE - dhcp->prefix;
    host_mask = (1 << host_bit_range) - 1;
    host = req_ip & host_mask;

    if (req_ip > GetBroadcastIP(dhcp->net_addr, dhcp->prefix) ||
        req_ip < dhcp->net_addr)
    {
        return (OUT_OF_RANGE);
    }

    RecAlloc(dhcp->root, &status, &host, host_bit_range);

    *out_ip = dhcp->net_addr + host;

    printf("out_ip: ");
    PrintIP(*out_ip);

    return (status);
}

dhcp_ret_val_t DHCPFree(dhcp_t *dhcp, ip_t ip)
{
    int status = SUCCESS;
    unsigned int host = 0, host_mask = 0, host_bit_range = 0;

    if (ip >= GetBroadcastIP(dhcp->net_addr, dhcp->prefix) ||
        ip <= GetServerIP(dhcp->net_addr))
    {
        return (OUT_OF_RANGE);
    }

    host_bit_range = IP4_BIT_RANGE - dhcp->prefix;
    host_mask = (1 << (host_bit_range - 1)) - 1;
    host = ip & host_mask;
    RecFree(dhcp->root, &status, &host, host_bit_range);

    return (status);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    unsigned int size = 0, host_bit_range = 0;
    
    size = (1 << (IP4_BIT_RANGE - dhcp->prefix));
    host_bit_range = IP4_BIT_RANGE - dhcp->prefix;
    return (size - RecSize(dhcp->root, host_bit_range));
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
        printf("node created\n");
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

    if (NULL != node->child[next_child_side] && 
        0 != node->child[next_child_side]->is_full)
    {
        next_child_side = !next_child_side;
    }

    *host = (~(1 << (height - 1)) & *host) | (next_child_side << (height - 1));
    node->child[next_child_side] = RecAlloc(node->child[next_child_side], status, host, height - 1);
    node->is_full = IsFullNode(node, height);

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
    node->is_full = IsFullNode(node, height);

    if (0 == DHCPCountChildren(node))
    {
        free(node);
        node = NULL;      
    }

    return (node);
}

static int IsFullNode(dhcp_node_t *node, unsigned int height)
{
    int is_full = 0;
    
    if (height == 1 && node->child[0] && node->child[1])
    {
        is_full = 1;
    }

    else if (height != 1 && node->child[0] && node->child[1])
    {
        if (node->child[0]->is_full && node->child[1]->is_full)
        {
            is_full = 1;
        }
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

static ip_t GetBroadcastIP(ip_t net_addr, size_t prefix)
{
    unsigned int host_mask = 0, host_bit_range = 0;

    host_bit_range = IP4_BIT_RANGE - prefix;
    host_mask = (1 << host_bit_range) - 1;
    
    return (net_addr | host_mask);
}

static ip_t GetServerIP(ip_t net_addr)
{
    return (net_addr + 1);
}

static void PrintIP(ip_t ip)
{
    printf("%u.%u.%u.%u / %u\n",
    ip >> 24,
    (ip << 8) >> 24,
    (ip << 16) >> 24,
    (ip << 24) >> 24,
    ip);
}


/*
static ip_t GetBroadcastIP(ip_t net_addr, size_t prefix)
{
    ip_t ip = {{0, 0, 0, 0}};
    size_t host_bit_range = 0;
    unsigned int net_addr_uint = 0;
    unsigned int host_mask = 0;

    host_bit_range = IP4_BIT_RANGE - prefix;
    net_addr_uint = IPCharToUInt(net_addr);

    host_mask = (1 << host_bit_range) - 1;
    
    return (IPUIntToChar(net_addr_uint | host_mask));
}
*/

/*
static ip_t GetServerIP(ip_t net_addr)
{
    unsigned int server_ip_uint = 0;

    server_ip_uint = IPCharToUInt(net_addr) + 1;

    return (IPUIntToChar(server_ip_uint));
}
*/

/*
static unsigned int IPCharToUInt(ip_t ip)
{
    unsigned int ip_uint = 0;
    ip_uint = 
    (unsigned int)ip.addr[3] << (24 - 1) |
    (unsigned int)ip.addr[2] << (16 - 1) |
    (unsigned int)ip.addr[1] << (8 - 1) |
    (unsigned int)ip.addr[0];  

    return (ip_uint);
}
*/

/*
static ip_t IPUIntToChar(unsigned int ip_uint)
{
    ip_t ip = {0, 0, 0, 0};
    ip.addr[3] = (char)(0xff & (ip_uint >> (24 - 1)));
    ip.addr[2] = (char)(0xff & (ip_uint >> (16 - 1)));
    ip.addr[1] = (char)(0xff & (ip_uint >> (8 - 1)));
    ip.addr[0] = (char)(0xff & ip_uint);

    return (ip);
}
*/

/*
static unsigned int RecAlloc(dhcp_t *dhcp, dhcp_node_t *node, unsigned int host, size_t height)
{
    int next_child_side = 0;

    if (0 == height)
    {
        return (host);
    }

    next_child_side = (host & (1 << (height - 1)) != 0);

    if (NULL == node->child[next_child_side])
    {
        node->child[next_child_side] = DHCPCreateNode();
    }

    if (0 != node->child[next_child_side]->is_full)
    {
        next_child_side = !next_child_side;

        if (NULL == node->child[next_child_side])
        {
            node->child[next_child_side] = DHCPCreateNode();
        }
    }

    host = (next_child_side << (height - 1)) & host;
    host = RecAlloc(dhcp, node->child[next_child_side], host, height - 1);
    node->is_full = IsFullNode(node, height);

    return (host);
}
*/