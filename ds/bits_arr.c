#include <stdio.h>
#include "include/bits_arr.h"

bitsarr_t BitsArrFlip(bitsarr_t arr, size_t index)
{
	size_t m = 1 << index;

	if (index > 63)
	{
		return (arr);
	}

	return (arr ^ m);	
}

bitsarr_t BitsArrSetOn(bitsarr_t arr, size_t index)
{
	size_t m = 1 << index;

	if (index > 63)
	{
		return (arr);
	}

	return (arr | m);
}

bitsarr_t BitsArrSetOff(bitsarr_t arr, size_t index)
{
	size_t m = 1 << index;

	if (index > 63)
	{
		return (arr);
	}

	return (arr & (~m));
}

size_t BitsArrCountOn(bitsarr_t arr);


size_t BitsArrCountOff(bitsarr_t arr);


bitsarr_t BitsArrResetAll(bitsarr_t arr);


bitsarr_t BitsArrSetAll(bitsarr_t arr);


int BitsArrIsOn(bitsarr_t arr, size_t index);


int BitsArrIsOff(bitsarr_t arr, size_t index);


bitsarr_t BitsArrRotR(bitsarr_t arr, size_t n);


bitsarr_t BitsArrRotL(bitsarr_t arr, size_t n);


char *BitsArrToString(bitsarr_t arr, char *dest);


bitsarr_t BitsArrMirror(bitsarr_t arr);


bitsarr_t BitsArrSetBit(bitsarr_t arr, size_t index, int state)
{
	size_t m = 1 << index;

	if (index > 63)
	{
		return (arr);
	}

	return (state) ? (arr | m) : (arr & (~m)) ;   
}

