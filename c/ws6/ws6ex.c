#include <stdio.h>

/* macros for lookup table (8 bits) */
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

/* lookup table - each index has the corresponding number of bits */
unsigned int lut[256] = { COUNT_BITS };

long pow2(unsigned int x, unsigned int y);
int isPow2Loop(unsigned int n);
int isPow2NoLoop(unsigned int n);
unsigned int Add1(unsigned int n);
void PrintIf3Bits(unsigned int n[], size_t size);
int is3Bits(unsigned int n);
unsigned int ByteMirrorLoop(unsigned int n);
unsigned int ByteMirrorNoLoop(unsigned int n);
unsigned char CheckBits2OR6(unsigned char c);
unsigned char CheckBits2AND6(unsigned char c);
unsigned char SwapBits3And5(unsigned char c);
unsigned int ClosestDiv16(unsigned int n);
void Swap(unsigned int* n1, unsigned int* n2);
int CountSetBitsLoop(unsigned int n);
int CountSetBitsLUT(unsigned int n);
void PrintBitsFloat(unsigned int* ptr);

int main()
{
	size_t i = 0;
	unsigned int x = 3;
	unsigned int y = 4;
	unsigned int n = 16;
	unsigned char c = 33;
	unsigned int arr[20];
	size_t size_arr = 0;
	float f = 1.2;
	int* ptr = 0;

	size_arr = sizeof(arr)/sizeof(arr[0]);

	for (i = 0; i < size_arr; i++)
	{
		arr[i] = i;
	}

	/* ex1 test: x * (2 ^ y) */
	printf("%d * (2 ^ %d) = %ld\n", x, y, pow2(x,y));

	/* ex2 test: isPow2 */
	printf("isPow2Loop(%u) = %d\n", n, isPow2Loop(n));
	printf("isPow2NoLoop(%u) = %d\n", n, isPow2NoLoop(n));

	/* ex3 test: add 1 */
	printf("Add1(%u) = %u\n", n, Add1(n));

	/* ex4 test: print if n has 3 bits on */
	PrintIf3Bits(arr,size_arr);

	/* ex5 test: byte mirror */
	printf("ByteMirrorLoop(%d) = %d\n", n, ByteMirrorLoop(n));

	/* ex6 test: check if bits 2 and 6 are on */
	printf("CheckBits2AND6(%d) = %d\n", c, CheckBits2AND6(c));

	/* ex7 test: check if bits 2 or 6 are on */
	printf("CheckBits2OR6(%d) = %d\n", c, CheckBits2OR6(c));

	/* ex8 test: swap bits 3 and 5 */
	printf("SwapBits3And5(%d) = %d\n", c, SwapBits3And5(c));

	/* ex9 test: find closest num dividable by 16 */
	printf("ClosestDiv16(%d) = %d\n", n, ClosestDiv16(n));

	/* ex10 test: find closest num dividable by 16 */
	printf("Before Swap: n1 = %u, n2 = %u\n", x, y);
	Swap(&x, &y);
	printf("After Swap: n1 = %u, n2 = %u\n", x, y);

	/* ex11 test: count set bits loop */
	printf("CountSetBits(%u) = %d\n", n, CountSetBitsLoop(n));

	/* ex12 test: count set bits loop */
	printf("CountSetBitsLUT(%u) = %d\n", n, CountSetBitsLUT(n));

	/* ex13 test: prints bits of float */
	ptr = &f;
	PrintBitsFloat(ptr);

	return (0);
}

/* ex1 function: x * (2 ^ y) */

long pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

/* ex2-1 function: isPow2 - with loop */

int isPow2Loop(unsigned int n)
{
	unsigned int m = 1;

	while (m <= n)
	{
		if (n == m)
		{
			return (1);
		}

		m = m << 1;
	}

	return (0);
}

/* ex2-2 function: isPow2 - no loop */

int isPow2NoLoop(unsigned int n)
{
	if (0 == n)
	{
		return (0);
	}

	else if ( (n & (n - 1)) == 0)
	{
		return (1);
	}

	return (0);	
}

/* ex3 function: add 1 bitwise */

unsigned int Add1(unsigned int n)
{
	unsigned int m = 1;

	while (0 != (n & m))
	{
		n = n ^ m;
		m <<= 1;
	}

	n = n ^ m;

	return (n);	
}

/* ex4 functions: print if 3 bits on */

void PrintIf3Bits(unsigned int n[], size_t size)
{
	size_t i = 0;

	printf("PrintIf3Bits: ");

	for (i = 0; i < size; i++)
	{
		if (is3Bits(n[i]))
		{
			printf("%u ", n[i]);
		}	
	}

	printf("\n");
}

int is3Bits(unsigned int n)
{
	unsigned int m = 1;
	size_t i = 0;

	while (m <= n)
	{
		if (n & m)
		{
			i++;
		}

		m = m << 1;
	}
	
	if (i == 3)
	{
		return (1);
	}

	return (0);
}

/* ex5-1 function: byte mirror (with loop) */

unsigned int ByteMirrorLoop(unsigned int n)
{
	unsigned int m1 = 1, m2 = 1 << 7;
	unsigned int n_m1 = 0, n_m2 = 0;
	unsigned int i = 0;
	unsigned int mirror = 0;
	unsigned int size = 8;

	for (i = 0; i < (size / 2); i++)
	{
		n_m1 = m1 & n;
		n_m1 <<= ((size - 1) - 2 * i);
		mirror |= n_m1;
		m1 <<= 1;

		n_m2 = m2 & n;
		n_m2 >>= (2 * i + 1);
		mirror |= n_m2;
		m2 >>= 1;
	}

	return (mirror);
}

/* ex5-2 function: byte mirror (no loop) */

unsigned int ByteMirrorNoLoop(unsigned int n)
{
	return (0);
}

/* ex6 function: check if bits 2 and 6 are on */

unsigned char CheckBits2AND6(unsigned char c)
{
	unsigned int m1 = 1 << 1;
	unsigned int m2 = 1 << 5;
	int result;

	result = (c & m1) && (c & m2);

	return (result);
}

/* ex7 function: check if bits 2 or 6 are on */

unsigned char CheckBits2OR6(unsigned char c)
{
	unsigned int m1 = 1 << 1;
	unsigned int m2 = 1 << 5;
	int result;

	result = (c & m1) || (c & m2);

	return (result);
}

/* ex8 function: swap between bit 3 and bit 5 */

unsigned char SwapBits3And5(unsigned char c)
{
	unsigned char m1 = 1 << 2;
	unsigned char m2 = 1 << 4;
	unsigned char c_m1 = 0;
	unsigned char c_m2 = 0;

	c_m1 = c & m1;
	c_m1 <<= 2;

	c_m2 = c & m2;
	c_m2 >>= 2;
	
	c = ((c | m1) ^ m1) & ((c | m2) ^ m2);

	c = c | (c_m1 | c_m2); 

	return (c);
}

/* ex9 function: find closest num dividable by 16 */

unsigned int ClosestDiv16(unsigned int n)
{
	unsigned int m = 1;

	while (m < (1 << 4))
	{
		if (n & m)
		{		
			n = n ^ m;
		}

		m <<= 1;
	}

	return (n);	
}

/* ex10 function: swap two vars without a 3rd var */

void Swap(unsigned int* n1, unsigned int* n2)
{
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;	
}

/* ex11 function: count number of set bits (loop) */

int CountSetBitsLoop(unsigned int n)
{
	unsigned int m = 1;
	unsigned int i = 0;

	while (m <= n)
	{
		if (n & m)
		{
			i++;
		}

		m = m << 1;
	}

	return (i);
}

/* ex12 function: count number of set bits (LUT) */

int CountSetBitsLUT(unsigned int n)
{
	int count = 0; 

	count = lut[n & 0xff] +
			lut[n >> 8 & 0xff] +
			lut[n >> 16 & 0xff] +
			lut[n >> 24];

	return (count);
}

/* ex13 function: print bits of float */

void PrintBitsFloat(unsigned int* ptr)
{
	int bit = 0;
	unsigned int m = 1;
	
	while (m <= *ptr)
	{
		bit = 0;

		if (m & *ptr)
		{
			bit = 1;
		}
		
		printf("%d \n", bit);
	}
}
