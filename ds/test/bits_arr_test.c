/****************************************************************
* 																*
* FILE NAME: bits_arr_test.c									*
* 																*
* PURPOSE: Testing bits array functions							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include "bits_arr.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void TestBitsArrSetOn();
void TestBitsArrSetOff();
void TestBitsArrFlip();
void TestBitsArrResetAll();
void TestBitsArrSetAll();
void TestBitsArrIsOn();
void TestBitsArrIsOff();
void TestBitsArrSetBit();
void TestBitsArrCountOn();
void TestBitsArrCountOff();
void TestBitsArrRotR();
void TestBitsArrRotL();
void TestBitsArrToString();
void TestBitsArrMirror();
void TestBitsArrMirrorLUT();
void TestBitsArrCountOnLUT();

int main()
{
	TestBitsArrSetOn();
	TestBitsArrSetOff();
	TestBitsArrFlip();
	TestBitsArrSetAll();
	TestBitsArrResetAll();
	TestBitsArrSetBit();
	TestBitsArrIsOn();
	TestBitsArrIsOff();
	TestBitsArrCountOn();
	TestBitsArrCountOff();
	TestBitsArrCountOnLUT();
	TestBitsArrMirror();
	TestBitsArrMirrorLUT();
	TestBitsArrRotL();
	TestBitsArrRotR();
	TestBitsArrToString();
	
	return (0);
}

void VerifySizet(bitsarr_t test, bitsarr_t expected, char pass[], char fail[])
{
	(test == expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyInt(int test, int expected, char pass[], char fail[])
{
	(test == expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyChar(char test[], char expected[], char pass[], char fail[])
{
	(!strcmp(test, expected)) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void TestBitsArrFlip()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	/* test1 - on bit at specific index is now off */
	/* test2 - off bit at specific index is now on */
	/* test3 - passing index out of bounds */

	printf("TestBitsArrFlip Tests\n");
	VerifySizet(BitsArrFlip((arr1 | (1ul << index1)), index1),
	arr1,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifySizet(BitsArrFlip(arr1, index2),
	(arr1 | (1ul << index2)),
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifySizet(BitsArrFlip(arr1, index3),
	arr1,
	"TEST 3 PASSED", "TEST 3 FAILED");
}
void TestBitsArrSetOn()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 63ul;
	size_t index3 = 64ul;

	/* test1 - off bit at specific index is now on */
	/* test2 - on bit at specific index is still on */
	/* test3 - passing index out of bounds */

	printf("TestBitsArrSetOn Tests\n");
	VerifySizet(BitsArrSetOn(arr1, index1),
	(arr1 | 1ul << index1),
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifySizet(BitsArrSetOn(arr1, index2),
	(arr1 | 1ul << index2),
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifySizet(BitsArrSetOn(arr1, index3),
	arr1,
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrSetOff()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	/* test1 - on bit at specific index is now off */
	/* test2 - off bit at specific index is still off */
	/* test3 - passing index out of bounds */

	printf("TestBitsArrSetOff Tests\n");
	VerifySizet(BitsArrSetOff((arr1 | (1ul << index1)), index1),
	arr1,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifySizet(BitsArrSetOff(arr1, index2),
	arr1,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifySizet(BitsArrSetOff(arr1, index3),
	arr1,
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrCountOn()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	/* test1 - specific array */
	/* test2 - all on array */
	/* test3 - all off array */

	printf("TestBitsArrCountOn Tests\n");
	VerifyInt(BitsArrCountOn(arr1),
	3,
	"TEST 1 PASSED", "TEST 1 FAILED");
	
	VerifyInt(BitsArrCountOn(~0lu),
	64,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyInt(BitsArrCountOn(0lu),
	0,
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrCountOff()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	/* test1 - specific array */
	/* test2 - all on array */
	/* test3 - all off array */

	printf("TestBitsArrCountOff Tests\n");
	VerifyInt(BitsArrCountOff(arr1),
	(64-3),
	"TEST 1 PASSED", "TEST 1 FAILED");
	
	VerifyInt(BitsArrCountOff(~0lu),
	0,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyInt(BitsArrCountOff(0lu),
	64,
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrResetAll()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	/* test1 - specific array */

	printf("TestBitsArrResetAll Tests\n");
	VerifySizet(BitsArrResetAll(arr1),
	0ul,
	"TEST 1 PASSED", "TEST 1 FAILED");
}

void TestBitsArrSetAll()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	/* test1 - specific array */

	printf("TestBitsArrSetAll Tests\n");
	VerifySizet(BitsArrSetAll(arr1),
	(~0ul),
	"TEST 1 PASSED", "TEST 1 FAILED");
}

void TestBitsArrIsOn()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 5ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	/* test1 - on bit at specific index return 1 */
	/* test2 - off bit at specific index return 0 */
	/* test3 - index out of bounds return -1 */

	printf("BitsArrIsOn Tests\n");
	VerifyInt(BitsArrIsOn(arr1, index1),
	1,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifyInt(BitsArrIsOn(arr1, index2),
	0ul,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyInt(BitsArrIsOn(arr1, index3),
	(-1),
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrIsOff()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 5ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	/* test1 - off bit at specific index return 1 */
	/* test2 - on bit at specific index return 0 */
	/* test3 - index out of bounds return -1 */

	printf("BitsArrIsOff Tests\n");
	VerifyInt(BitsArrIsOff(arr1, index2),
	1ul,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifyInt(BitsArrIsOff(arr1, index1),
	0ul,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyInt(BitsArrIsOff(arr1, index3),
	(-1),
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrRotR()
{
	size_t arr1 = (1ul << 1) | (1ul << 20) | (1ul << 62);
	size_t arr2 = (1ul << (1 - 5 + 64)) | (1ul << (20 - 5)) | (1ul << (62 - 5));
 
	/* test1 - specific array, rotate by specific number */
	/* test2 - specific array, rotate by specific number plus 64*n */

	printf("TestBitsArrRotR Tests\n");
	VerifySizet(BitsArrRotR(arr1, 5),
	arr2,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifySizet(BitsArrRotR(arr1,(5 + 64 * 5)),
	arr2,
	"TEST 2 PASSED", "TEST 2 FAILED");
}

void TestBitsArrRotL()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 62);
	size_t arr2 = (1ul << (5 + 5)) | (1ul << (20 + 5)) | (1ul << (62 + 5 - 64));

	/* test1 - specific array, rotate by specific number */
	/* test2 - specific array, rotate by specific number plus 64*n */

	printf("TestBitsArrRotL Tests\n");
	VerifySizet(BitsArrRotL(arr1, 5),
	arr2,
	"TEST 1 PASSED", "TEST 1 FAILED");
	
	VerifySizet(BitsArrRotL(arr1, (5 + 64 * 5)),
	arr2,
	"TEST 2 PASSED", "TEST 2 FAILED");
}

void TestBitsArrToString()
{
	size_t arr1 = (1ul << 0) | (1ul << 20) | (1ul << 61);
	size_t arr2 = ~0lu;
	size_t arr3 = 0lu;
	static char arr1_char[64];
	static char arr2_char[64];
	static char arr3_char[64];
	static char arr1t_char[]=
	"0010000000000000000000000000000000000000000100000000000000000001";
	static char arr2t_char[]=
	"1111111111111111111111111111111111111111111111111111111111111111";
	static char arr3t_char[]=
	"0000000000000000000000000000000000000000000000000000000000000000";

	/* test1 - specific array */
	/* test2 - all on array */
	/* test1 - all off array */

	printf("TestBitsArrToString Tests\n");
	VerifyChar(BitsArrToString(arr1, arr1_char),
	arr1t_char,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifyChar(BitsArrToString(arr2, arr2_char),
	arr2t_char,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyChar(BitsArrToString(arr3, arr3_char),
	arr3t_char,
	"TEST 3 PASSED", "TEST 3 FAILED");
}

void TestBitsArrMirror()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t arr2 = (1ul << (63-5)) | (1ul << (63-20)) | (1ul << (63-63));

	/* test1 - specific array */

	printf("TestBitsArrMirror Tests\n");
	VerifySizet(BitsArrMirror(arr1),
	arr2,
	"TEST 1 PASSED", "TEST 1 FAILED");
}

void TestBitsArrSetBit()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 63ul;

	/* test1 - off bit that was set on at specific index is now on */
	/* test2 - on bit that was set on at specific index is still on */
	/* test3 - on bit that was set off at specific index is now off */
	/* test4 - off bit that was set off at specific index is still off */

	printf("TestBitsArrSetBit Tests\n");
	VerifySizet(BitsArrSetBit(arr1, index1, 1),
	(arr1 | (1ul << index1)),
	"TEST 1 PASSED", "TEST 1 FAILED");
	
	VerifySizet(BitsArrSetBit(arr1,index2, 1),
	arr1,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifySizet(BitsArrSetBit((arr1 | (1ul << index1)), index1, 0),
	arr1,
	"TEST 3 PASSED", "TEST 3 FAILED");

	VerifySizet(BitsArrSetBit(arr1, index1, 0),
	arr1,
	"TEST 4 PASSED", "TEST 4 FAILED");
}

void TestBitsArrMirrorLUT()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t arr2 = (1ul << (63-5)) | (1ul << (63-20)) | (1ul << (63-63));

	/* test1 - specific array */

	printf("TestBitsArrMirrorLUT Tests\n");
	VerifySizet(BitsArrMirrorLUT(arr1),
	arr2,
	"TEST 1 PASSED", "TEST 1 FAILED");
}

void TestBitsArrCountOnLUT()
{
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	/* test1 - specific array */
	/* test2 - all on array */
	/* test3 - all off array */

	printf("TestBitsArrCountOnLUT Tests\n");
	VerifyInt(BitsArrCountOnLUT(arr1),
	3,
	"TEST 1 PASSED", "TEST 1 FAILED");

	VerifyInt(BitsArrCountOnLUT(~0lu),
	64,
	"TEST 2 PASSED", "TEST 2 FAILED");

	VerifyInt(BitsArrCountOnLUT(0lu),
	0,
	"TEST 3 PASSED", "TEST 3 FAILED");
}
