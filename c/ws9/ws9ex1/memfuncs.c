#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "memfuncs.h"

void *Memset(void *s, int c, size_t n)
{
	char* org = (char*)s;
	char* char_ptr = 0;
	size_t* word_ptr = 0;
	size_t offset_tail = 0;
	size_t offset_head = 0;
	size_t word_c = 0;
	size_t i = 0;
	size_t word_size = sizeof(size_t);
	size_t chunks = 0;

	offset_tail = (word_size - ((size_t)(s) % word_size)) % word_size;
	chunks = (n - offset_tail) / word_size;
	offset_head = n - offset_tail - chunks * word_size;

	printf("chunks: %lu, tail: %lu, head: %lu\n", chunks, offset_tail, offset_head); 

	for (i = 0; i < word_size; i++)
	{
		word_c += (0xff & (size_t)c) << (i * 8);
	}

	char_ptr = (char*)s;

	for (i = 0; i < (offset_tail + 1) && n > 0; i++)
	{
		printf("tail\n");
		*char_ptr = c;
		char_ptr = char_ptr + i;
		n--;
	}
	
	word_ptr = (size_t*)char_ptr;

	for (i = 0; i < chunks && n > 0; i++)
	{
		printf("chunk\n");
		*word_ptr = word_c;
		word_ptr = word_ptr + i;
		n = n - word_size;
	}

	char_ptr = (char*)word_ptr;

	for (i = 0; i < offset_head && n > 0; i++)
	{
		printf("head\n");
		*char_ptr = c;
		char_ptr = char_ptr + i;
		n--;
	}

	return org;
}

/*
void *Memcpy(void *dest, const void *src, size_t n)
{

}

void *Memmove(void *dest, const void *src, size_t n)
{

}
*/
