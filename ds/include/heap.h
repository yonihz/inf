#ifndef _HEAP_H_OL74_
#define _HEAP_H_OL74_

/* Rev. 0.0 */ 
/* 05.11.19  16:15 */
#include <stddef.h> /* size_t */

typedef struct heap heap_t;

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
typedef int(*cmp_func_t)(const void *data1, const void *data2);
/* 
*	match_func:
*		user func to determine if data1 == data2.
*
*	return:
*		returns: 0 -    data1 == data2
                non 0 - data1 != data2
*/
typedef int(*match_func_t)(const void *data1, const void *data2);

/* 
*	HeapCreate:
*		creates an empty Heap.
* 	arguments: 
*		cmp_func = function that will be used to determine the order of elements
*	return:
*		pointer to the created Heap
*	complexity:
*		time O(1), space O(1)
*	special notes:
*		this function is using malloc.  
*/
heap_t *HeapCreate(cmp_func_t cmp_func);

/* 
*	HeapDestroy:
*		destroy an Heap.
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*	complexity:
*		time O(n), space O(1)  
*/
void HeapDestroy(heap_t *heap);

/* 
*	HeapSize:
*		return the num of elements in the Heap
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*	return:
*		the number of elements in heap
*	complexity:
*		time O(1), space O(1)  
*/
size_t HeapSize(const heap_t *heap);

/* 
*	HeapIsEmpty:
*		return if the heap is empty
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*	return:
*		1 if empty
*		0 if not
*	complexity:
*		time O(1), space O(1)  
*/
int HeapIsEmpty(const heap_t *heap);

/* 
*	HeapPush:
*		push the data to the heap.
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*       data = pointer to push to the heap
*	return:
*		0 if success
*	complexity:
*		time O(log(n)), space O(1)  
*/
int HeapPush(heap_t *heap, void *data);

/* 
*	HeapPop:
*		pop the high data from the heap.
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*	return:
*		0 if success
*	complexity:
*		time O(log(n)), space O(1)  
*/
void HeapPop(heap_t *heap);

/* 
*	HeapPeek:
*		peek to the high data from the heap.
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*	return:
*		void* to the data
*	complexity:
*		time O(1), space O(1)  
*/
void *HeapPeek(const heap_t *heap);

/* 
*	HeapRemove:
*		remove the match data from the heap.
* 	arguments: 
*		heap = a pointer given by HeapCreate func
*       match_func = function that will be used to determine if data to remove found
*	return:
*		void* to the data
*	complexity:
*		time O(n), space O(1)  
*/
void *HeapRemove(heap_t *heap, const void *data, match_func_t match_func);


#endif /* _AVL_H_OL74_ */
