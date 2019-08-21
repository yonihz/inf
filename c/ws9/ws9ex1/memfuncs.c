#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "memfuncs.h"

void *Memset(void *s, int c, size_t n)
{
	char* char_ptr = (char*)s;
	size_t* word_ptr = (size_t*)s;
	size_t offset_tail = 0;
	size_t offset_head = 0;
	size_t word_c = 0;
	size_t i = 0;
	size_t word_size = sizeof(size_t);
	size_t chunks = 0;

	offset_tail = (word_size - ((size_t)(s) % word_size)) % word_size;
	chunks = (n - offset_tail) / word_size;
	offset_head = n - offset_tail - chunks * word_size;

	/* duplicate c to word size length */
	for (i = 0; i < word_size; i++)
	{
		word_c += (0xff & (size_t)c) << (i * word_size);
	}

	/* insert tail bits before alignment boundary */
	for (i = 0; i < offset_tail && n > 0; i++)
	{
		*(char_ptr + i) = c;
		n--;
	}

	/* insert word sized chunks */
	word_ptr = (size_t*)(char_ptr+i);

	for (i = 0; i < chunks && n > 0; i++)
	{
		*(word_ptr+i) = word_c;
		n -= word_size;
	}

	/* insert head bits left after last alignment boundary */
	char_ptr = (char*)(word_ptr+i);

	for (i = 0; i < offset_head && n > 0; i++)
	{
		*(char_ptr+i) = c;
		n--;
	}

	return (s);
}

/*
void *Memcpy(void *dest, const void *src, size_t n)
{

}

void *Memmove(void *dest, const void *src, size_t n)
{

}
*/
