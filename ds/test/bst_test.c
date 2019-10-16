#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "bst.h"

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
void TestInsertRemove();
void TestTraverse();

int main()
{
    TestInsertRemove();
    TestTraverse();
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

void TestInsertRemove()
{
    bst_t *bst = NULL;
    int arr1[SIZE_ARR1] = {50, 30, 80, 10, 40, 5, 12, 100, 90, 85, 70, 86};
    bst_itr_t root = NULL;
    bst_itr_t test_itr = NULL;
    size_t i = 0;

    printf("Basic Tests: Insert, Remove, Create, Find, GetData, Destroy\n");
    bst = BSTCreate(IntCmp, NULL);

    for (i = 0; i < SIZE_ARR1; i++)
    {
        VerifyVoidptr(BSTGetData(BSTInsert(bst, (arr1 + i))), (arr1 + i), "INSERT");
    }                    

    root = bst->end.child[0];

    test_itr = root;
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 0), "INSERT - TREE LOCATION");

    test_itr = root->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 1), "INSERT - TREE LOCATION");

    test_itr = root->child[1];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 2), "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 3), "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 4), "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 10), "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 7), "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[0]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 5), "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[0]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 6), "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[1]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), NULL, "INSERT - TREE LOCATION");

    test_itr = root->child[0]->child[1]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), NULL, "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[1]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 8), "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[1]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), NULL, "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[1]->child[0]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 9), "INSERT - TREE LOCATION");

    test_itr = root->child[1]->child[1]->child[0]->child[1];
    VerifyVoidptr(BSTGetData(test_itr), NULL, "INSERT - TREE LOCATION");

    test_itr = BSTFind(bst, (arr1 + 2));
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 2), "FIND");

    BSTRemove(test_itr);

    test_itr = root->child[1];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 9), "REMOVE");

    test_itr = root->child[1]->child[1]->child[0]->child[0];
    VerifyVoidptr(BSTGetData(test_itr), (arr1 + 11), "REMOVE");

    BSTDestroy(bst);
}

void TestTraverse()
{
    bst_t *bst = NULL;
    int arr1[SIZE_ARR1] = {50, 30, 80, 10, 40, 5, 12, 100, 90, 85, 70, 86};
    int arr1_sorted[SIZE_ARR1] = {5, 10, 12, 30, 40, 50, 70, 80, 85, 86, 90, 100};
    int arr1_sorted_foreach[SIZE_ARR1];   
    bst_itr_t test_itr = NULL;
    bst_itr_t itr_begin = NULL;
    bst_itr_t itr_end = NULL;
    int add = 1;
    size_t i = 0;

    for (i = 0; i < SIZE_ARR1; ++i)
    {
        arr1_sorted_foreach[i] = arr1_sorted[i] + add;
    }

    printf("Traverse Tests: Next, Prev, Begin, End, Size, IsEmpty, ForEach\n");
    bst = BSTCreate(IntCmp, NULL);

    VerifyInt(BSTIsEmpty(bst), 1, "ISEMPTY - EMPTY BST");
    VerifySizet(BSTSize(bst), 0, "SIZE - EMPTY BST");
    for (i = 0; i < SIZE_ARR1; i++)
    {
        BSTInsert(bst, (arr1 + i));
        VerifySizet(BSTSize(bst), i + 1, "SIZE - AFTER INSERT");
    }

    VerifySizet(BSTSize(bst), 12, "SIZE - AFTER 12 INSERT");
    VerifyInt(BSTIsEmpty(bst), 0, "ISEMPTY - NON-EMPTY BST");

    test_itr = BSTBegin(bst);
    itr_end = BSTEnd(bst);
    for (i = 0; !BSTIsSame(test_itr, itr_end); i++, test_itr = BSTNext(test_itr))
    {
        VerifyVoidptr(BSTGetData(test_itr), (arr1_sorted + i), "NEXT");
    }

    itr_begin = BSTBegin(bst);
    test_itr = BSTPrev(BSTEnd(bst));
    for (i = 0; !BSTIsSame(test_itr, itr_begin); i++, test_itr = BSTPrev(test_itr))
    {
        VerifyVoidptr(BSTGetData(test_itr), (arr1_sorted + SIZE_ARR1 -1 - i), "PREV");
    }

    test_itr = BSTBegin(bst);
    itr_end = BSTEnd(bst);
    
    BSTForEach(test_itr, itr_end, AddInt, &add);

    for (i = 0; !BSTIsSame(test_itr, itr_end); i++, test_itr = BSTNext(test_itr))
    {
        VerifyVoidptr(BSTGetData(test_itr), (arr1_sorted_foreach + i), "FOR EACH - ADD 1");
    }    

    test_itr = BSTBegin(bst);
    itr_end = BSTEnd(bst);
    for (i = 0; !BSTIsSame(test_itr, itr_end); i++, test_itr = BSTBegin(bst))
    {
        BSTRemove(test_itr);
        VerifySizet(BSTSize(bst), SIZE_ARR1 - i - 1, "SIZE - AFTER REMOVE");
    }

    VerifyInt(BSTIsEmpty(bst), 1, "ISEMPTY - EMPTY BST");
    BSTDestroy(bst);  
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



