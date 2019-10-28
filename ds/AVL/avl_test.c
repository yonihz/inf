#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "avl.h"

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

#define UNUSED(x) (void)(x)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

#define SIZE_ARR1 12

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

int IntCmp(const void* data1, const void* data2, void* param);
int AddInt(void* data, void* param);
int PrintInt(void* data, void* param);
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
    avl_t *avl = NULL;
    int arr1[SIZE_ARR1] = {50, 30, 80, 10, 40, 5, 12, 100, 90, 85, 70, 86};
    int arr1_sorted[SIZE_ARR1] = {5, 10, 12, 30, 40, 50, 70, 80, 85, 86, 90, 100};
    size_t i = 0;

    printf("Basic Tests:\n");
    avl = AVLCreate(IntCmp, NULL);

    VerifyInt(AVLIsEmpty(avl), 1, "ISEMPTY - EMPTY AVL");
    VerifySizet(AVLSize(avl), 0, "SIZE - EMPTY AVL");

    for (i = 0; i < SIZE_ARR1; i++)
    {
        VerifyInt(AVLInsert(avl, (arr1 + i)), 0, "INSERT - RETURNS 0");
        VerifySizet(AVLSize(avl), i + 1, "SIZE - AFTER INSERT");
    }

    VerifySizet(AVLSize(avl), 12, "SIZE - AFTER 12 INSERT");
    VerifyInt(AVLIsEmpty(avl), 0, "ISEMPTY - NON-EMPTY BST");

    AVLForEach(avl, PrintInt, NULL);

    AVLDestroy(avl);  
}
int IntCmp(const void* data1, const void* data2, void* param)
{
    UNUSED(param);
    return (*(int*)data1 - *(int*)data2);
}

int AddInt(void* data, void* param)
{
    *(int*)data += *(int*)param;
    return (0);
}

int PrintInt(void* data, void* param)
{
    UNUSED(param);
    printf("ForEach print function: %d\n", *(int*)data);
    return (0);
}