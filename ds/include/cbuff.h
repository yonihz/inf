#ifndef _CBUFF_H_
#define _CBUFF_H_

/* Rev. 1.0*/ 
/* 08.09.19  14:00 */
#include <sys/types.h>

typedef struct c_buff cbuff_t;

/* if cbuff equals null return -1*/
/* size in bytes, complexity of malloc */

cbuff_t* CBuffCreate(size_t capacity);

/* complexity of free */
void CBuffDestroy(cbuff_t* cbuff);

/* complexity o(1) */
size_t CBuffCapacity(const cbuff_t* cbuff);

/* complexity o(n)- n is the number of bytes, in case of error return -1 */
ssize_t CBuffRead(cbuff_t* cbuff, void *dest, size_t nbytes);

/* complexity o(n)- n is the number of bytes, in case of error return -1 */
ssize_t CBuffWrite(cbuff_t* cbuff, const void *src, size_t nbytes);

/* true = 1, false = 0  complexity o(1) */
int CBuffIsEmpty(const cbuff_t* cbuff);

/* complexity o(1) */
size_t CBuffFreeSpace(const cbuff_t* cbuff);


#endif


