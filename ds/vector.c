/****************************************************************
* 																*
* FILE NAME: vector.c											*
* 																*
* PURPOSE: Vector functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"

#ifndef NDEBUG
#define ACTIVE 0xDEADBEEF
#define ALLOCATED 0xBADDCAFE
#endif

struct vector
{
	void* head;
    void* current;
    void* end;
    size_t size_of_element;

#ifndef NDEBUG
    size_t status;
#endif
};

vector_t *VectorCreate(size_t size_of_element, size_t num_of_elements)
{
	vector_t* new_vector = NULL;

	assert(0 != size_of_element);

	new_vector = malloc(sizeof(vector_t));

	assert(NULL != new_vector);

    new_vector->size_of_element = size_of_element;
	new_vector->head = NULL;
	new_vector->current = NULL;
	new_vector->end = NULL;

#ifndef NDEBUG
    new_vector->status = ACTIVE;
#endif

	VectorReserve(new_vector, num_of_elements);

    return (new_vector);
}

int VectorReserve(vector_t* vector, size_t num_of_elements)
{
	void* temp_head = NULL;
	size_t current_size = 0;
	size_t total_size = vector->size_of_element * num_of_elements;

	if (0 == total_size)
	{
		return (0);
	}

	assert(NULL != vector &&
	(ACTIVE == vector->status || ALLOCATED == vector->status));

	if (NULL != vector->head)
	{
		current_size = VectorSize(vector) * vector->size_of_element;
	}

	temp_head = realloc(vector->head, total_size);

	if (NULL == temp_head)
	{
		return (1);
	}

#ifndef NDEBUG
    vector->status = ALLOCATED;
#endif
		
	vector->head = temp_head;
	vector->current = (char*)vector->head + current_size;
    vector->end = (char*)vector->head + total_size;
	return (0);
}

void VectorDestroy(vector_t* vector)
{
	assert(NULL != vector &&
	(ACTIVE == vector->status || ALLOCATED == vector->status));

#ifndef NDEBUG
    vector->status = 0x00000000;
#endif
	
	free(vector->head);
	free(vector);
}

size_t VectorSize(const vector_t* vector)
{
	assert(NULL != vector &&
	(ACTIVE == vector->status || ALLOCATED == vector->status));
	
	return
	(((char*)vector->current - (char*)vector->head)/vector->size_of_element);
}

size_t VectorCapacity(const vector_t* vector)
{
	assert(NULL != vector &&
	(ACTIVE == vector->status || ALLOCATED == vector->status));
	
	return
	(((char*)vector->end - (char*)vector->head)/vector->size_of_element);
}

int VectorPushBack(vector_t* vector, const void *element)
{
	int status = 0;

	assert(NULL != vector && ALLOCATED == vector->status);

	if (vector->current == vector->end)
	{
		status = VectorReserve(vector, (VectorCapacity(vector) * 2));
	}

	assert(0 == status);
	
	memcpy(vector->current, element, vector->size_of_element);

	vector->current = (char*)vector->current + vector->size_of_element;
	return (status);
}

void VectorPopBack(vector_t* vector)
{
	assert(NULL != vector && ALLOCATED == vector->status);

	if (vector->current == vector->head)
    {
        return;
    }

	vector->current = (char*)vector->current - vector->size_of_element;

	if ((VectorSize(vector) <= (VectorCapacity(vector) / 4)) &&
		VectorSize(vector) != 0)
	{
		VectorReserve(vector, (VectorCapacity(vector) / 2));
	}
}


void *VectorGetItemAddress(const vector_t* vector, size_t index)
{
	assert(NULL != vector && ALLOCATED == vector->status);

	if ( (vector->current == vector->head) ||
		((index + 1) > VectorSize(vector)) )
    {
        return (NULL);
    }

    return ((char*)vector->head + index * vector->size_of_element);
}



