#include <stdio.h> /* printf */

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

	printf("\noffset_tail: %lu | chunks: %lu | offset_head: %lu\n\n",
	offset_tail, chunks, offset_head);

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
	size_t head_src = 0;
	size_t chunks = 0;
	size_t buffer = 0;
	size_t i = 0;

	/* calc tails of src and dest, number of word size chunks, head of src */
	tail_src = (word_size - ((size_t)(src) % word_size)) % word_size;
	tail_dest = (word_size - ((size_t)(dest) % word_size)) % word_size;
	chunks = (n - tail_dest) / word_size;
	head_src = n - tail_dest - chunks * word_size;

	printf("\ntail_src: %lu | tail_dest: %lu | chunks: %lu | head_src: %lu\n\n",
	tail_src, tail_dest, chunks, head_src);
	
	/* copy first to dest tail byte by byte */
	for (i = 0; i < tail_dest && n > 0; i++)
	{
		*(char_ptr_dest + i) = *(char_ptr_src + i);
		n--;
	}

	/* start of src ptr for chunks depends on which tail is larger */
	if (tail_src >= tail_dest)
	{
		buff1_ptr_src = (size_t*)(char_ptr_src - (word_size - tail_src));
		buff2_ptr_src = (size_t*)(char_ptr_src + tail_src);
	}
	else
	{
		buff1_ptr_src = (size_t*)(char_ptr_src + tail_src);
		buff2_ptr_src = (size_t*)(char_ptr_src + tail_src + word_size);
	}

	/* copy word size chunks */
	word_ptr_dest = (size_t*)(char_ptr_dest + tail_dest);

	for (i = 0; i < chunks && n > 0; i++)
	{
		if (tail_src >= tail_dest)
		{
			buffer =
			(*(buff1_ptr_src + i) >> (word_size - (tail_src - tail_dest))*8) | 
			(*(buff2_ptr_src + i) << (tail_src - tail_dest)*8);
		}
		else
		{
			buffer =
			(*(buff1_ptr_src + i) >> (tail_dest - tail_src)*8) | 
			(*(buff2_ptr_src + i) << (word_size - (tail_dest-tail_src))*8);
		}

		*(word_ptr_dest + i) = buffer;
		n -= word_size;
	}

	/* last copy - byte by byte from head src to dest */
	char_ptr_src = (char*)(char_ptr_src + tail_dest + chunks * word_size);
	char_ptr_dest = (char*)(word_ptr_dest + i);

	for (i = 0; i < head_src && n > 0; i++)
	{
		*(char_ptr_dest+i) = *(char_ptr_src+i);
		n--;
	}

	return (dest);
}


void *Memmove(void *dest, const void *src, size_t n)
{
	size_t word_size = sizeof(size_t);
	char* char_ptr_src = (char*)src;
	char* char_ptr_dest = (char*)dest;
	size_t* word_ptr_src = (size_t*)src;
	size_t* word_ptr_dest = (size_t*)dest;

	size_t head_src = 0;
	size_t chunks = 0;
	size_t i = 0;

	head_src = (size_t)(char_ptr_src + n) % word_size;
	chunks = (n - head_src) / word_size;

	printf("\nchunks: %lu | head_src: %lu\n\n", chunks, head_src);

	/* if src>dest: copy from start of src in chunks then head byte by byte */
	/* if dest>src: copy from end of src head byte by byte then in chunks */
	if (src > dest)
	{
		/* printf("src > dest\n"); */
		for (i = 0; i < chunks && n > 0; i++)
		{
			/* printf("chunk\n"); */
			*(word_ptr_dest + i) = *(word_ptr_src + i);
			n -= word_size;
		}

		char_ptr_src = (char*)(word_ptr_src + i);
		char_ptr_dest = (char*)(word_ptr_dest + i);

		for (i = 0; i <= head_src && n > 0; i++)
		{
			/* printf("head\n"); */
			*(char_ptr_dest+i) = *(char_ptr_src+i);
			n--;
		}
	}
	else if (dest > src)
	{
		/* printf("dest > src\n"); */
		char_ptr_src = char_ptr_src + n;
		char_ptr_dest = char_ptr_dest + n;

		for (i = 0; i < head_src && n > 0; i++)
		{
			/* printf("head\n"); */
			*(char_ptr_dest - i - 1) = *(char_ptr_src - i - 1);
			n--;
		}

		word_ptr_src = (size_t*)(char_ptr_src - head_src);
		word_ptr_dest = (size_t*)(char_ptr_dest - head_src);

		for (i = 0; i < head_src && n > 0; i++)
		{
			/* printf("chunk\n"); */
			*(word_ptr_dest - i - 1) = *(word_ptr_src - i - 1);
			n -= word_size;
		}
	}

	return (dest);
}

