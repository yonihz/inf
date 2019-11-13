/*version number 1.2,
    time 18:30*/

#ifndef _DHCP_H_OL74_
#define _DHCP_H_OL74_

#include <stddef.h>/*size_t*/

typedef enum dhcp_ret_val { 
    SUCCESS, 
    DOUBLE_FREE_FAILURE, 
    OUT_OF_RANGE,
    SYSTEM_ERROR
} dhcp_ret_val_t;

typedef struct dhcp dhcp_t;

typedef struct ip {
    char addr[4];
}ip_t;

/*Receive system ip address and subnet mask. Return pointer to DHCP.
    Return NULL on fail*/
dhcp_t *DHCPCreate(ip_t net_addr, size_t prefix);

/*Destroy and free DHCP*/
void DHCPDestroy(dhcp_t *dhcp);

/*Receive pointer to DHCP and requested IP address. Designate address requested
    if available, or closest avialable if not.
    Return success or failure status*/
dhcp_ret_val_t DHCPAlloc(dhcp_t *dhcp, ip_t req_ip, ip_t *out_ip);

/*Receive pointer to DHCP and requested IP address to free. 
    Free address requested if possible.
    Return success or failure status*/
dhcp_ret_val_t DHCPFree(dhcp_t *dhcp, ip_t ip);

/*Receive pointer to DHCP. Return number of available IP addresses in pool*/
size_t DHCPCountFree(dhcp_t *dhcp);

#endif