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


void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t word_size = sizeof(size_t);
	char* char_ptr_src = (char*)src;
	char* char_ptr_dest = (char*)dest;
	size_t* buff1_ptr_src = 0;
	size_t* buff2_ptr_src = 0;
	size_t* word_ptr_dest = (size_t*)dest;
	size_t tail_src = 0;
	size_t tail_dest = 0;
	size_t tail_diff = 0;
	size_t head_src = 0;
	size_t chunks = 0;
	size_t buffer = 0;
	size_t i = 0;

	tail_src = (word_size - ((size_t)(src) % word_size)) % word_size;
	tail_dest = (word_size - ((size_t)(dest) % word_size)) % word_size;
	tail_diff = tail_dest <= tail_src ? tail_src - tail_dest : tail_dest;
	chunks = (n - tail_diff) / word_size;
	head_src = n - tail_diff - chunks * word_size;

	printf("n = %lu\n", n);
	printf("tail_src: %lu tail_dest: %lu tail_diff: %lu chunks: %lu head_src: %lu\n",tail_src,tail_dest,tail_diff,chunks,head_src);
	
	for (i = 0; i < tail_dest && n > 0; i++)
	{
		printf("tail\n");
		*(char_ptr_dest + i) = *(char_ptr_src + i);
		n--;
	}

	buff1_ptr_src = (size_t*)(char_ptr_src - (word_size - tail_src));
	buff2_ptr_src = (size_t*)(char_ptr_src + tail_src);
	word_ptr_dest = (size_t*)(char_ptr_dest + tail_dest);

	for (i = 0; i < chunks && n > 0; i++)
	{
		printf("chuck\n");
		buffer = (*(buff1_ptr_src + i) << (word_size - tail_diff)*8) | 
				 (*(buff2_ptr_src + i) >> (tail_diff)*8);
		*(word_ptr_dest + i) = buffer;
		n -= word_size;
	}

	char_ptr_src = (char*)(buff1_ptr_src + i) + (word_size - tail_diff);
	char_ptr_dest = (char*)(word_ptr_dest + i);

	for (i = 0; i < head_src && n > 0; i++)
	{
		printf("head\n");
		*(char_ptr_dest+i) = *(char_ptr_src+i);
		n--;
	}

	return (dest);
}

/*
void *Memmove(void *dest, const void *src, size_t n)
{

}
*/
