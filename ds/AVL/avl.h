#ifndef _AVL_H_OL74_
#define _AVL_H_OL74_

/* Rev. 1.1 */ 
/* 28.10.19  10:26 */
#include <stddef.h> /* size_t */

typedef struct avl avl_t;

/* 
*	cmp_func:
*		user func to determine the order of the elements within the AVL
* 	arguments:
* 		data1 = an element from AVL
*		data2 = an element from AVL
*		param = a param that will be used in the cmp_func
*	return:
*		returns an integer less than, equal to, or greater than zero if data1
*		is found, respectively, to be before, match, or after data2
*/
typedef int(*cmp_func_t)(const void *data1, const void *data2, void *param);

/* 
*	op_func:
*		user func to make operation of AVL elements
* 	arguments: 
*		data = an element from AVL
*		param = a param that will be used in the op_func
*	return:
*		0 if successful 
*		otherwise if not
*	special notes:
*		AVL behaviour is undefined if data changed in a way that affect
*		the cmp_func of that AVL 
*/
typedef int(*op_func_t)(void *data, void *param);

/* 
*	find_if_func:
*		user func to search element within AVL by other methods than cm_func
* 	arguments: 
*		data = an element from AVL
*		param = a param that will be used in the is_same_func
*	return:
*		1 if same 
*		0 if not
*/
typedef int (*find_if_func_t)(const void *data, void *param);

/* 
*	AVLCreate:
*		creates an empty AVL.
* 	arguments: 
*		cmp_func = function that will be used to determine the order of elements
*		param = a param that will be used in the cmp_func
*	return:
*		pointer to the created AVL
*	complexity:
*		time O(1), space O(1)
*	special notes:
*		this function is using malloc.  
*/
avl_t *AVLCreate(cmp_func_t cmp_func, void *param);

/* 
*	AVLDestroy:
*		destroy an AVL.
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*	complexity:
*		time O(n), space O(1)  
*/
void AVLDestroy(avl_t *avl);

/* 
*	AVLSize:
*		return the num of elements in the AVL
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*	return:
*		the number of elements in AVL
*	complexity:
*		time O(n), space O(1)  
*/
size_t AVLSize(const avl_t *avl);

/* 
*	AVLHeight:
*		return the maximum height of the AVL
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*	return:
*		the maximum height of the AVL
*	complexity:
*		time O(1), space O(1)  
*	special notes:
*		undefined for empty AVL 
*/
size_t AVLHeight(const avl_t *avl);

/* 
*	AVLIsEmpty:
*		return if the AVL is empty
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*	return:
*		1 if empty
*		0 if not
*	complexity:
*		time O(1), space O(1)  
*/
int AVLIsEmpty(const avl_t *avl);

/* 
*	AVLInsert:
*		adds an elemnt to the AVL
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*		data = the element to be added
*	return:
*		0 if success
*		anything else if not
*	complexity:
*		time O(log n), space O(1) 
*	special notes:
*		this function is using malloc. 
*/
int AVLInsert(avl_t *avl, void *data);

/* 
*	AVLRemove:
*		removes an elemnt to the AVL
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*		data = the element to be removed
*	complexity:
*		time O(log n), space O(1) 
*/
void AVLRemove(avl_t *avl, const void *data);

/* 
*	AVLFind:
*		find the element within the AVL (relies on the cmp_func)
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*		data = the element to be searched
*	return:
*		NULL if not found
*		ptr to the element if found
*	complexity:
*		time O(log n), space O(1) 
*	special notes:
*		AVL behaviour is undefined if data changed in a way that affect
*		the cmp_func of that AVL 
*/
void *AVLFind(avl_t *avl, const void *data);

/* 
*	AVLForEach:
*		find the element within the AVL
*		this func travers the entire AVL in order
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*		op_func = operation to be made on each element
*		param = element to be used by the opr_func
*	return:
*		the return value of the last op_func
*		0 - if success
*		1 - if failure occured
*	complexity:
*		time O(n), space O(1) 
*/
int AVLForEach(avl_t *avl, op_func_t op_func, void *param);

/* 
*	AVLFindIf:
*		find the element within the AVL
*		this func travers the entire AVL
* 	arguments: 
*		avl = a pointer given by AVLCreate func
*		find_if_func = a func that the element will be seached by
*		param = element to be used by the match_func
*	return:
*		NULL if not found
*		ptr to the element if found.
*		first found, order undefined
*	complexity:
*		time O(n), space O(1) 
*	special notes:
*		AVL behaviour is undefined if data changed in a way that affect
*		the cmp_func of that AVL 
*/
void *AVLFindIf(avl_t *avl, find_if_func_t find_if_func, void *data);

#endif /* _AVL_H_OL74_ */
