#include <stdio.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

int Flip(int n);
unsigned char MirrorByte(unsigned char n);
unsigned char Mirror(unsigned char n);
unsigned int FlipBit(unsigned int val, int n);
unsigned int CountSetBitsByte(unsigned int n);
unsigned int CountSetBits(unsigned int n);
unsigned char RotateLeft(unsigned char byte, int nbits);
unsigned int Multi8(unsigned int n);
void SwapNoTemp1(int* a, int* b);
void SwapNoTemp2(int* a, int* b);
void SwapPtr(int** a, int** b);
size_t Strlen(const char *s);
int Strcmp(const char *s1, const char *s2);
char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
char *Strcat(char *dest, const char *src);

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyStr(char test[], char expected[], char test_name[]);
void VerifyChar(unsigned char test, unsigned char expected, char test_name[]);


int main()
{
	int a = 5;
	int b = 7;
	int *ap = &a;
	int *bp = &b;

	unsigned char num3 = (1 << 0) | (1 << 2);
	unsigned char num3_mirror = (1 << 7) | (1 << 5);
	unsigned int num4 = (1 << 0) | (1 << 2);
	unsigned int num4_flip3 = (1 << 0);
	unsigned char num5 = (1 << 0) | (1 << 2);
	unsigned char num6 = (1 << 1) | (1 << 7);
	unsigned char num6_rot2 = (1 << 3) | (1 << 1);	

	char str11[50] = "One";
	char str12[50] = "One";
	char str21[50] = "Two";
	char str22[50] = "Two";
	char str31[50] = "Three";
	char str32[50] = "Three";
	
	VerifyInt(Flip(12345), 54321, "FLIP TEST");
	VerifyInt(Flip(-12345), -54321, "FLIP TEST");
	VerifyChar(MirrorByte(num3), num3_mirror, "MIRROR BYTE TEST");
	VerifyChar(Mirror(num3), num3_mirror, "MIRROR BYTE LUT TEST");
	VerifyChar(FlipBit(num4, 3), num4_flip3, "FLIP BIT TEST");
	VerifyInt(CountSetBitsByte(num5), 2, "COUNT SET BITS TEST");
	VerifyInt(CountSetBits(num5), 2, "COUNT SET BITS LUT TEST");
	VerifyChar(RotateLeft(num6, 2), num6_rot2, "ROTATE LEFT TEST");
	VerifyInt(Multi8(2), 16, "MULTIPLY BY 8 TEST");

	SwapPtr(&ap, &bp);
	VerifyInt(*ap, 7, "SWAP PTR TEST1");
	VerifyInt(*bp, 5, "SWAP PTR TEST2");

	VerifySizet(Strlen(str11),strlen(str11), "STRLEN TEST");
	VerifyInt(Strcmp(str11,str12), strcmp(str11,str12), "STRCMP TEST 1");
	VerifyInt(Strcmp(str11,str31), strcmp(str11,str31), "STRCMP TEST 1");
	VerifyStr(Strcpy(str11,str31), strcpy(str12,str32), "STRCPY TEST");
	VerifyStr(Strncpy(str31,str21,2), strncpy(str32,str22,2), "STRNCPY TEST");
	VerifyStr(Strcat(str31,str21), strcat(str32,str22), "STRCAT TEST");

	return (0);
}

void VerifyInt(int test, int expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyStr(char test[], char expected[], char test_name[])
{
	(!strcmp(test, expected)) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyChar(unsigned char test, unsigned char expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

int Flip(int n)
{
	int res = 0;
	while (n)
	{
		res = res * 10 + n % 10;
		n /= 10;
	}

	return (res);
}

unsigned char MirrorByte(unsigned char n)
{
	unsigned char m = n;	
	unsigned char size = 8;
	unsigned char i = 0;

	while (i < (size - 1))
	{
		m <<= 1;
		n >>= 1;
		m |= n & 1;
		i++;
	}

	return (m);
}

unsigned char Mirror(unsigned char n)
{
	static int isMirrorLUT = 0;
	static unsigned char MirrorBits_LUT[256];
	unsigned char i = 0;

	if (!isMirrorLUT)
	{
		for (i = 0; i < 255; i++)
		{
			MirrorBits_LUT[(size_t)i] = MirrorByte(i);
		}

		isMirrorLUT = 1;
	}

	return (MirrorBits_LUT[n]);
}

unsigned int FlipBit(unsigned int val, int n)
{
	return(val && (1 << n));
}

unsigned int CountSetBitsByte(unsigned int n)
{
	unsigned int m = 1, i = 0;

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

unsigned int CountSetBits(unsigned int n)
{
	static int isCountLUT = 0;
	static unsigned char CountBits_LUT[256];
	unsigned char i = 0;

	if (!isCountLUT)
	{
		for (i = 0;i < 255; i++)
		{
			CountBits_LUT[(size_t)i] = CountSetBitsByte(i);
		}

		isCountLUT = 1;
	}

	return (CountBits_LUT[n]);
}

unsigned char RotateLeft(unsigned char byte, int nbits)
{
	nbits = nbits % 8;
	return (byte << nbits | byte >> (8 - nbits));
}

void SwapPtr(int** a, int** b)
{
	int* temp = *a;
	*a = *b;
	*b = temp;
}

size_t Strlen(const char *s)
{
	size_t count = 0;
	
	while (*s)
	{
		count++;
		s++;
	}
	
	return count;
}

int Strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

char *Strcpy(char *dest, const char *src)
{
	char* org = dest;

	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}

	*dest = '\0';

	return (org);	
}

char *Strncpy(char *dest, const char *src, size_t n)
{
	char* org = dest;

	while (n)
	{
		*dest = *src;
		src++;
		dest++;
		n--;
	}

	return (org);	
}

char *Strcat(char *dest, const char *src)
{
	size_t len = Strlen(dest);
	char* org = dest;
	dest = dest + len;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	return org;
}

unsigned int Multi8(unsigned int n)
{
	return (n << 3);
}

void SwapNoTemp1(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void SwapNoTemp2(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
