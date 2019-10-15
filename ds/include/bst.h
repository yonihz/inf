#ifndef _BST_H_
#define _BST_H_

/* Rev. 1.0 */ 
/* 15.10.19  11:00 */
#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_itr_t;

/* returns an integer less than, equal to, or greater than zero if data1 is
found, respectively, to be before, match, or after data2 */
typedef int(*cmp_func_t)(const void *data1, const void *data2, void *param);

/* returns 0 if operation successful, otherwise returns non-zero */
typedef int(*op_func_t)(void *data, void *param);

/* O(1) */
/* returns NULL on error */
bst_t *BSTCreate(cmp_func_t cmp_func, void *param);

/* O(n) */
void BSTDestroy(bst_t *bst);

/* O(log(n)) / O(n) */
/* return itr of match, otherwise returns BSTEnd(bst) if no match found */
bst_itr_t BSTFind(bst_t *bst, const void *data);

/* O(log(n)) / O(n) */
/* returns itr of inserted data, otherwise returns BSTEnd(bst) on error */
bst_itr_t BSTInsert(bst_t *bst, void *data);

/* O(log(n)) / O(n) */
void BSTRemove(bst_itr_t itr);

/* O(n) */
/* op_func range: [itr_start, itr_end) */
/* returns last op_func return value */
int BSTForEach(bst_itr_t itr_start, bst_itr_t itr_end, op_func_t op_func, void *param);

/* O(n) */
size_t BSTSize(const bst_t *bst);

/* O(1) */
int BSTIsEmpty(const bst_t *bst);

/* O(1) */
void *BSTGetData(bst_itr_t itr);

/* O(log(n)) / O(n) */
bst_itr_t BSTNext(bst_itr_t itr);

/* O(log(n)) / O(n) */
bst_itr_t BSTPrev(bst_itr_t itr);

/* O(log(n)) / O(n) */
bst_itr_t BSTBegin(const bst_t *bst);

/* O(1) */
bst_itr_t BSTEnd(const bst_t *bst);

/* O(1) */
int BSTIsSame(bst_itr_t itr1, bst_itr_t itr2);

#endif /* _BST_H_ */
