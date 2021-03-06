/****************************************************************
* 																*
* FILE NAME: heap_test.c										*
* 																*
* PURPOSE: Testing heap functions								*
* 																*
* DATE: 08.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "heap.h"

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

int IntCmp(const void* data1, const void* data2);

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

void TestBasic()
{
	int arr[10] = {30, 10, 20, 3, 8, 40, 50, 90, 44, 16};
	heap_t *heap = NULL;

	heap = HeapCreate(IntCmp);

	VerifySizet(HeapSize(heap), 0, "HEAP SIZE IS 0 AFTER CREATE");
	VerifyInt(HeapIsEmpty(heap), 1, "HEAP ISEMPTY IS 1 AFTER CREATE");

	VerifyInt(HeapPush(heap, (arr + 0)), 0, "HEAP PUSH RETURN SUCCESS");
	VerifyInt(HeapIsEmpty(heap), 0, "HEAP ISEMPTY IS 0 AFTER 1 PUSH");
	VerifySizet(HeapSize(heap), 1, "HEAP SIZE IS 1 AFTER 1 PUSH");
	HeapPush(heap, (arr + 1));
	/* Heap: 30 */
	VerifySizet(HeapSize(heap), 2, "HEAP SIZE IS 2 AFTER 2 PUSH");
	VerifyVoidptr(HeapPeek(heap), (arr + 0), "PEEK AFTER PUSH");
	HeapPush(heap, (arr + 2));
	HeapPush(heap, (arr + 3));
	HeapPush(heap, (arr + 4));
	/* Heap: 30 - 10 - 20 - 3 - 8 */
	HeapPop(heap);
	/* Heap: 10 - 20 - 3 - 8 */
	VerifySizet(HeapSize(heap), 4, "HEAP SIZE IS 2 AFTER 1 POP");
	VerifyVoidptr(HeapPeek(heap), (arr + 2), "PEEK AFTER POP");
	HeapPush(heap, (arr + 5));
	/* Heap: 10 - 20 - 3 - 8 - 40 */
	VerifyVoidptr(HeapPeek(heap), (arr + 5), "PEEK AFTER PUSH NEW MAX");
	HeapPush(heap, (arr + 6));
	HeapPush(heap, (arr + 7));
	HeapPush(heap, (arr + 8));
	HeapPush(heap, (arr + 9));
	/* Heap: 10 - 20 - 3 - 8 - 40 - 50 - 90 - 44 - 16 */
	HeapRemove(heap, (arr + 6), IntCmp);
	/* Heap: 10 - 20 - 3 - 8 - 40 - 90 - 44 - 16 */
	HeapPop(heap);
	/* Heap: 10 - 20 - 3 - 8 - 40 - 44 - 16 */
	VerifySizet(HeapSize(heap), 7, "HEAP SIZE IS 7 AFTER 1 REMOVE");
	VerifyVoidptr(HeapPeek(heap), (arr + 8), "PEEK AFTER REMOVE AND POP");

	HeapDestroy(heap);
}

int IntCmp(const void* data1, const void* data2)
{
    return (*(int*)data1 - *(int*)data2);
}