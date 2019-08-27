#ifndef _BITSARR_H_
#define _BITSARR_H_

#include <stddef.h>
#include <stdio.h>
#include "bits_arr.h"

typedef size_t bitsarr_t; 

/* return current status. complexity o(1) */
bitsarr_t BitsArrFlip(bitsarr_t arr, size_t index);

/*  complexity o(1)*/
bitsarr_t BitsArrSetOn(bitsarr_t arr, size_t index);

/*  complexity o(1)*/
bitsarr_t BitsArrSetOff(bitsarr_t arr, size_t index);

/*  return count of on. complexity o(n)*/
size_t BitsArrCountOn(bitsarr_t arr);

/*  return count of off. complexity o(n) */
size_t BitsArrCountOff(bitsarr_t arr);

/* complexity o(n) */
bitsarr_t BitsArrResetAll(bitsarr_t arr);

/* complexity o(n) */
bitsarr_t BitsArrSetAll(bitsarr_t arr);

/* return 1 if on, else 0. complexity o(1) */
int BitsArrIsOn(bitsarr_t arr, size_t index);

/* return 1 if off, else 0. complexity o(1) */
int BitsArrIsOff(bitsarr_t arr, size_t index);

/* complexity o(n) */
bitsarr_t BitsArrRotR(bitsarr_t arr, size_t n);

/* complexity o(n) */
bitsarr_t BitsArrRotL(bitsarr_t arr, size_t n);

/* return dest. complexity o(n) */
char *BitsArrToString(bitsarr_t arr, char *dest);

/* complexity o(n) */
bitsarr_t BitsArrMirror(bitsarr_t arr);

/* complexity o(1) */
bitsarr_t BitsArrSetBit(bitsarr_t arr, size_t index, int state);

bitsarr_t BitsArrMirrorLUT(bitsarr_t arr);

size_t BitsArrCountOnLUT(bitsarr_t arr);

#endif
