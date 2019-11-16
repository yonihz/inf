#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "dhcp.h"

#define UNUSED(x) (void)(x)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);
static void PrintIP(ip_t ip);

/* API test functions */

void TestBasic();

int main()
{
    TestBasic();
    return (0);
}

void VerifyInt(int test, int expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyVoidptr(void* test, void* expected, char test_name[])
{
	if (NULL == expected)
	{
		(test == NULL) ?
		(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
		(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
		printf(RESET);
		return;
	}

	(*(int*)test == *(int*)expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyChar(char test[], char expected[], char test_name[])
{
	(!strcmp(test, expected)) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[])
{
	(!strncmp(test, expected, n)) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
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

void TestBasic()
{
	ip_t net_addr = 0;
	ip_t req_ip1 = 0;
	size_t prefix = 24;
	dhcp_t *dhcp = NULL;
	ip_t out_ip1 = 0;
	ip_t expected_out_ip1 = 0;
	int status = 0;
	size_t host_range_test = 0, host_range_expected = 0;

	printf("Basic tests:\n");

	/* net_addr = 10.0.2.0, subnet mask = 255.255.255.0 */
	net_addr |= ((10 << 24) | (0 << 16) | (2 << 8) | 0);
	printf("Create with network address: ");
	PrintIP(net_addr);
	dhcp = DHCPCreate(net_addr, prefix);
	VerifySizet(DHCPCountFree(dhcp), 256 - 3, "COUNT_FREE AFTER CREATE");
	host_range_expected = DHCPCountFree(dhcp);

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 31);
	expected_out_ip1 = 167772703;

	printf("Alloc with required IP: ");
	PrintIP(req_ip1);
	VerifyInt(DHCPAlloc(dhcp, req_ip1, &out_ip1), 0, "ALLOC - RETURN VALUE");
	VerifySizet(out_ip1, expected_out_ip1, "ALLOC - OUT_IP");
	VerifySizet(DHCPCountFree(dhcp), 256 - 4, "COUNT_FREE AFTER 1 ALLOC");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 254);
	expected_out_ip1 = 167772926;

	VerifyInt(DHCPAlloc(dhcp, req_ip1, &out_ip1), 0, "ALLOC - RETURN VALUE");
	VerifySizet(out_ip1, expected_out_ip1, "ALLOC - OUT_IP");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER 1 ALLOC");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (3 << 8) | 255);

	VerifyInt(DHCPAlloc(dhcp, req_ip1, &out_ip1), OUT_OF_RANGE, "ALLOC - RETURN VALUE OUT OF RANGE");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER FAILED ALLOC");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 255);

	VerifyInt(DHCPFree(dhcp, req_ip1), OUT_OF_RANGE, "FREE - RETURN VALUE OUT OF RANGE");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER FAILED FREE");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 1);

	VerifyInt(DHCPFree(dhcp, req_ip1), OUT_OF_RANGE, "FREE - RETURN VALUE OUT OF RANGE");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER FAILED FREE");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 31);
	expected_out_ip1 = 167772702;

	VerifyInt(DHCPAlloc(dhcp, req_ip1, &out_ip1), 0, "ALLOC OF USED IP - RETURN VALUE");
	VerifySizet(out_ip1, expected_out_ip1, "ALLOC OF USED IP - OUT_IP");
	VerifySizet(DHCPCountFree(dhcp), 256 - 6, "COUNT_FREE AFTER 1 ALLOC OF USED IP");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 31);

	VerifyInt(DHCPFree(dhcp, req_ip1), 0, "FREE - RETURN VALUE");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER 1 FREE");

	VerifyInt(DHCPFree(dhcp, req_ip1), DOUBLE_FREE_FAILURE, "DOUBLE FREE - RETURN VALUE");
	VerifySizet(DHCPCountFree(dhcp), 256 - 5, "COUNT_FREE AFTER FREE FAILED");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 31);
	expected_out_ip1 = 167772703;

	VerifyInt(DHCPAlloc(dhcp, req_ip1, &out_ip1), 0, "ALLOC OF SAME IP THAT WAS FREED - RETURN VALUE");
	VerifySizet(out_ip1, expected_out_ip1, "ALLOC OF SAME IP THAT WAS FREED - OUT_IP");
	VerifySizet(DHCPCountFree(dhcp), 256 - 6, "COUNT_FREE AFTER 1 ALLOC");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 31);
	DHCPFree(dhcp, req_ip1);
	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 30);
	DHCPFree(dhcp, req_ip1);
	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 254);
	DHCPFree(dhcp, req_ip1);
	VerifySizet(DHCPCountFree(dhcp), 256 - 3, "COUNT_FREE EMPTY");

	req_ip1 = 0 | ((10 << 24) | (0 << 16) | (2 << 8) | 2);
	while (0 == status)
	{
		status = DHCPAlloc(dhcp, req_ip1, &out_ip1);
		if (0 == status)
		{
			++host_range_test;
		}
	}

	VerifySizet(host_range_test, host_range_expected, "COUNT ALLOCS UNTIL NO MORE AVAILABLE");
	VerifyInt(status, NO_FREE_IPS, "ALLOC RETURN VALUE - NO FREE IPS");

	DHCPDestroy(dhcp);
}