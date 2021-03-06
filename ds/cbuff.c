/****************************************************************
* 																*
* FILE NAME: cbuff.c											*
* 																*
* PURPOSE: Circular Buffer functions source file				*
*                                                               *
* DATE: 08.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "cbuff.h"

#define MIN2(a,b) (((a) > (b)) ? (b) : (a))

struct c_buff
{
	char* arr;
	size_t cap;
	size_t size;
	size_t read_idx;
};

/* if cbuff equals null return -1*/
/* size in bytes, complexity of malloc */

cbuff_t* CBuffCreate(size_t capacity)
{
	void* new = malloc(sizeof(cbuff_t) + capacity * sizeof(char));
	cbuff_t* new_cbuff = new;
	assert(new);

	if (!new)
	{
		return NULL;
	}

	new_cbuff->arr = (char*)new + sizeof(cbuff_t);
	new_cbuff->cap = capacity;
	new_cbuff->size = 0;
	new_cbuff->read_idx = 0;

	return (new_cbuff);
}

/* complexity of free */
void CBuffDestroy(cbuff_t* cbuff)
{
	free(cbuff);
	cbuff = NULL;
}

/* complexity o(1) */
size_t CBuffCapacity(const cbuff_t* cbuff)
{
	return (cbuff->cap);
}

/* complexity o(n)- n is the number of bytes, in case of error return -1 */
ssize_t CBuffRead(cbuff_t* cbuff, void *dest, size_t nbytes)
{
	size_t nfirst = 0;	
	
	if (!dest)
	{
		return (-1);
	}

	if (CBuffIsEmpty(cbuff))
	{
		return (0);
	}

	nbytes = MIN2(nbytes,cbuff->size);

	nfirst = cbuff->read_idx + nbytes > cbuff->cap ?
	cbuff->cap - cbuff->read_idx : 0;
	
	memcpy(dest,
	cbuff->arr + cbuff->read_idx,
	nfirst);

	dest = (char*)dest + nfirst;

	memcpy(dest,
	cbuff->arr + (cbuff->read_idx + nfirst)%(cbuff->cap),
	nbytes - nfirst);
	
	cbuff->read_idx = (cbuff->read_idx + nbytes)%(cbuff->cap);	
	cbuff->size -= nbytes;

	return (nbytes);
}

/* complexity o(n)- n is the number of bytes, in case of error return -1 */
ssize_t CBuffWrite(cbuff_t* cbuff, const void *src, size_t nbytes)
{
	size_t nfirst = 0;	

	if (!src)
	{
		return (-1);
	}

	if (!CBuffFreeSpace(cbuff))
	{
		return (0);
	}

	nbytes = MIN2(nbytes,CBuffFreeSpace(cbuff));
	
	nfirst = cbuff->read_idx + cbuff->size + nbytes > cbuff->cap ?
	cbuff->cap - cbuff->size - cbuff->read_idx : 0;
	
	memcpy(cbuff->arr + cbuff->read_idx + cbuff->size,
	src,
	nfirst);

	src = (char*)src + nfirst;

	memcpy(cbuff->arr + (cbuff->read_idx + cbuff->size + nfirst)%(cbuff->cap),
	src,
	nbytes - nfirst);

	cbuff->size += nbytes;

	return (nbytes);
}

/* true = 1, false = 0  complexity o(1) */
int CBuffIsEmpty(const cbuff_t* cbuff)
{
	return (cbuff->size == 0);
}

/* complexity o(1) */
size_t CBuffFreeSpace(const cbuff_t* cbuff)
{
	return (cbuff->cap - cbuff->size);
}
