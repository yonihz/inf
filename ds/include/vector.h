#ifndef _VECTOR_H_
#define _VECTOR_H_

/* Rev. 0.0 */ 
/* 29.8.19  14:30 */

#include <stddef.h>

typedef struct vector vector_t;

/* complexity of malloc function */
vector_t *VectorCreate(size_t size_of_element, size_t num_of_elements);


/* complexity of free function */
void VectorDestroy(vector_t* vector);


/* complexity of O(1) */
size_t VectorSize(const vector_t* vector);


/* complexity of O(1) */
size_t VectorCapacity(const vector_t* vector);


/* complexity of O(log n)
   return : success = 0, failure = 1 */
int VectorPushBack(vector_t* vector, const void *element);


/* complexity of O(log n) */
void VectorPopBack(vector_t* vector);


/* complexity of O(1) */
void *VectorGetItemAddress(const vector_t* vector, size_t index);


/* complexity of realloc function
   return : success = 0, failure = 1 */
int VectorReserve(vector_t* vector, size_t num_of_elements);

#endif


