#include <stdio.h>
#include "bits_arr.h"

/* macros for set bits LUT (8 bits) */
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define SET_BITS B6(0), B6(1), B6(1), B6(2)

/* macros for reverese bits LUT (8 bits) */

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
#define REVERSE_BITS R6(0), R6(2), R6(1), R6(3)

size_t word_size = sizeof(bitsarr_t) * 8;

bitsarr_t BitsArrFlip(bitsarr_t arr, size_t index)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (arr);
	}

	m <<= index;

	return (arr ^ m);	
}

bitsarr_t BitsArrSetOn(bitsarr_t arr, size_t index)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (arr);
	}

 	m <<= index;

	return (arr | m);
}

bitsarr_t BitsArrSetOff(bitsarr_t arr, size_t index)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (arr);
	}

	m <<= index;

	return (arr & (~m));
}

size_t BitsArrCountOn(bitsarr_t arr)
{
	size_t i = 0;
	size_t m = 1ul;
	size_t count = 0;

	for (i = 0; i < word_size; i++)
	{
		m = 1ul << i;

		if (m & arr)
		{
			count++;
		}
	}

	return (count);
}

size_t BitsArrCountOff(bitsarr_t arr)
{
	size_t i = 0;
	size_t m = 1ul;
	size_t count = 0;

	arr = ~arr;

	for (i = 0; i < word_size; i++)
	{
		m = 1ul << i;

		if (m & arr)
		{
			count++;
		}
	}

	return (count);
}

bitsarr_t BitsArrResetAll(bitsarr_t arr)
{
	return (0ul & arr);
}

bitsarr_t BitsArrSetAll(bitsarr_t arr)
{
	return ((~0ul) | arr);
}	

int BitsArrIsOn(bitsarr_t arr, size_t index)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (-1);
	}
	
	m <<= index;

	if (arr & m)
	{
		return (1);
	}

	return (0);
}

int BitsArrIsOff(bitsarr_t arr, size_t index)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (-1);
	}
	
	m <<= index;

	if (arr & m)
	{
		return (0);
	}

	return (1);
}


bitsarr_t BitsArrRotR(bitsarr_t arr, size_t n)
{
	n = n % word_size;

	return ((arr << (word_size - n)) | (arr >> n));
}

bitsarr_t BitsArrRotL(bitsarr_t arr, size_t n)
{
	n = n % word_size;

	return ((arr >> (word_size - n)) | (arr << n));
}


char *BitsArrToString(bitsarr_t arr, char *dest)
{
	size_t i = 0;

	while (i < word_size)
	{
		*(dest + word_size - 1 - i) = arr % 2 + '0';
		arr /= 2;
		i++;
	}

	return (dest);
}

bitsarr_t BitsArrMirror(bitsarr_t arr)
{
	bitsarr_t mirror = arr;	
	size_t i = 0;

	while (i < (word_size - 1))
	{
		mirror <<= 1;
		arr >>= 1;
		mirror |= arr & 1;
		i++;
	}
	
	return (mirror);
}

bitsarr_t BitsArrSetBit(bitsarr_t arr, size_t index, int state)
{
	size_t m = 1ul;

	if (index > (word_size - 1))
	{
		return (arr);
	}

	m <<= index;

	return (state) ? (arr | m) : (arr & (~m)) ;   
}

bitsarr_t BitsArrMirrorLUT(bitsarr_t arr)
{
	size_t i = 0;
	size_t rev_bits_lut[256] = { REVERSE_BITS };	
	bitsarr_t arr_mirror = 0ul;

	while (i < word_size)
	{
		arr_mirror |= (rev_bits_lut[(arr >> i) & 0xff] << (word_size - 8 - i));
		i += 8;
	}

	return (arr_mirror);
}

size_t BitsArrCountOnLUT(bitsarr_t arr)
{
	size_t i = 0;	
	unsigned int count = 0;
	unsigned int set_bits_lut[256] = { SET_BITS };

	for (i = 0; i < (word_size / 8); i++)
	{
		count += set_bits_lut[(arr >> (i * 8)) & 0xff];
	}

	return (count);
}
