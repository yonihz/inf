#include "dhcp.h"

#define IP4_BIT_RANGE

typedef struct dhcp_node {
dhcp_node_t *child[2];
int is_full;
} dhcp_node_t;

typedef struct dhcp {
    dhcp_node_t *root;
    ip_t net_addr;
    size_t prefix;
} dhcp_t;

dhcp_t *DHCPCreate(ip_t net_addr, size_t prefix)
{
    dhcp_t *dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
    ip_t out_ip = {{0, 0, 0, 0}};

    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->root = DHCPCreateNode();
    dhcp->net_addr = net_addr;
    dhcp->prefix = prefix;

    /* BC: xxx.xxx.xxx.255, Server: xxx.xxx.xxx.1, Network: xxx.xxx.xxx.0 */

    DHCPAlloc(dhcp, net_addr, &out_ip);
    DHCPAlloc(dhcp, GetBroadcastIP(net_addr, prefix), &out_ip);
    DHCPAlloc(dhcp, GetServerIP(net_addr), &out_ip);

    return (dhcp);
}


void DHCPDestroy(dhcp_t *dhcp)
{

}


dhcp_ret_val_t DHCPAlloc(dhcp_t *dhcp, ip_t req_ip, ip_t *out_ip)
{
    unsigned int host = 0, host_mask = 0;
    size_t height = 0, host_bit_range = 0;

    if (0 != dhcp->root->is_full)
    {
        return (OUT_OF_RANGE); /* TODO: change enum */
    }

    host_bit_range = IP4_BIT_RANGE - dhcp->prefix;
    host_mask = (1 << host_bit_range) - 1;
    host = IPCharToUInt(req_ip) & host_mask;
    height = IP4_BIT_RANGE - dhcp->prefix;
    host = RecAlloc(dhcp, host, height, dhcp->root);
}

dhcp_ret_val_t DHCPFree(dhcp_t *dhcp, ip_t ip)
{

}

size_t DHCPCountFree(dhcp_t *dhcp)
{

}

static ip_t GetBroadcastIP(ip_t net_addr, size_t prefix)
{
    ip_t ip = {{0, 0, 0, 0}};
    size_t host_bit_range = 0;
    unsigned int net_addr_uint = 0;
    unsigned int host_mask = 0;

    host_bit_range = IP4_BIT_RANGE - prefix;
    net_addr_uint = IPCharToUInt(net_addr);

    host_mask = (1 << host_bit_range) - 1;
    
    return(IPUIntToChar(net_addr_uint | host_mask));
}

static ip_t GetServerIP(ip_t net_addr)
{
    unsigned int server_ip_uint = 0;

    server_ip_uint = IPCharToUInt(net_addr) + 1;

    return (IPUIntToChar(server_ip_uint));
}

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

static ip_t IPUIntToChar(unsigned int ip_uint)
{
    ip_t ip = {0, 0, 0, 0};
    ip.addr[3] = (char)(0xff & (ip_uint >> (24 - 1)));
    ip.addr[2] = (char)(0xff & (ip_uint >> (16 - 1)));
    ip.addr[1] = (char)(0xff & (ip_uint >> (8 - 1)));
    ip.addr[0] = (char)(0xff & ip_uint);

    return (ip);
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

static unsigned int RecAlloc(dhcp_t *dhcp, unsigned int host, size_t height, dhcp_node_t *node)
{
    int next_child_side = 0;

    if (0 == height)
    {
        return (host);
    }

    next_child_side = (host & (1 << height) != 0);

    if (NULL == node->child[next_child_side])
    {
        node->child[next_child_side] = DHCPCreateNode();
    }

    if (0 != node->child[next_child_side]->is_full)
    {
        next_child_side = !next_child_side;
    }

    host = (next_child_side << (height - 1)) & host;

    host = RecAlloc(dhcp, host, height - 1, node->child[next_child_side]);

    node->is_full = IsFullNode(node, height);

    return (host);
}

static int IsFullNode(dhcp_node_t *node, size_t height)
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