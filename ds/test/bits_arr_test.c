#include <stdio.h>
#include "../include/bits_arr.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void PrintTestResult(int test_result, int num);
void TestBitsArrSetOn();
void TestBitsArrSetOff();
void TestBitsArrFlip();
void TestBitsArrResetAll();
void TestBitsArrSetAll();
void TestBitsArrIsOn();
void TestBitsArrIsOff();
void TestBitsArrSetBit();

int main()
{
	
	/* SetOn test */
	TestBitsArrSetOn();

	/* SetOff test */
	TestBitsArrSetOff();

	/* Flip test */
	TestBitsArrFlip();

	/* SetAll test */
	TestBitsArrSetAll();

	/* ResetAll test */
	TestBitsArrResetAll();

	/* SetBit test */

	/* isOn test */
	TestBitsArrIsOn();

	/* isOff test */
	TestBitsArrIsOff();
	

	return (0);
}

void PrintTestResult(int test_result, int test_num)
{
	if (test_result)
	{
		printf(GRN);
		printf("# TEST %d PASSED #\n", test_num);
	}
	else
	{
		printf(RED);
		printf("# TEST %d FAILED #\n", test_num);
	}
	
	printf(RESET);
}

void TestBitsArrFlip()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	printf("TestBitsArrFlip Tests\n");

	/* test1 - check that on bit at specific index is now off, compare to expected result */
	test_result = (BitsArrFlip((arr1 | (1ul << index1)), index1) == arr1); 
	PrintTestResult(test_result, 1);

	/* test2 - check that off bit at specific index is now on, compare to expected result */
	test_result = (BitsArrFlip(arr1, index2) == (arr1 | (1ul << index2))); 
	PrintTestResult(test_result, 2);

	/* test3 - check when passing index out of bounds array is returned unchanged, compare to expected result */
	test_result = (BitsArrFlip(arr1, index3) == (arr1)); 
	PrintTestResult(test_result, 3);
}
void TestBitsArrSetOn()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 63ul;
	size_t index3 = 64ul;

	printf("TestBitsArrSetOn Tests\n");

	/* test1 - check that off bit at specific index is now on, compare to expected result */
	test_result = (BitsArrSetOn(arr1, index1) == (arr1 | 1ul << index1)); 
	PrintTestResult(test_result, 1);

	/* test2 - check that on bit at specific index is still on, compare to expected result */
	test_result = (BitsArrSetOn(arr1, index2) == (arr1 | 1ul << index2)); 
	PrintTestResult(test_result, 2);

	/* test3 - check when passing index out of bounds array is returned unchanged, compare to expected result */
	test_result = (BitsArrSetOn(arr1, index3) == (arr1)); 
	PrintTestResult(test_result, 3);
}

void TestBitsArrSetOff()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 10ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	printf("TestBitsArrSetOff Tests\n");

	/* test1 - check that on bit at specific index is now off, compare to expected result */
	test_result = (BitsArrSetOff((arr1 | (1ul << index1)), index1) == (arr1)); 
	PrintTestResult(test_result, 1);

	/* test2 - check that off bit at specific index is still off, compare to expected result */
	test_result = (BitsArrSetOff(arr1, index2) == arr1); 
	PrintTestResult(test_result, 2);

	/* test3 - check when passing index out of bounds array is returned unchanged, compare to expected result */
	test_result = (BitsArrSetOff(arr1, index3) == (arr1)); 
	PrintTestResult(test_result, 3);
}

void TestBitsArrCountOn();

void TestBitsArrCountOff();

void TestBitsArrResetAll()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	printf("TestBitsArrResetAll Tests\n");

	/* test1 - check that on bit at specific index is now off, compare to expected result */
	test_result = (BitsArrResetAll(arr1) == 0ul); 
	PrintTestResult(test_result, 1);
}

void TestBitsArrSetAll()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);

	printf("TestBitsArrSetAll Tests\n");

	/* test1 - check that on bit at specific index is now off, compare to expected result */
	test_result = (BitsArrSetAll(arr1) == (~0ul)); 
	PrintTestResult(test_result, 1);
}

void TestBitsArrIsOn()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 5ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	printf("BitsArrIsOn Tests\n");

	/* test1 - check that on bit at specific index return 1, compare to expected result */
	test_result = (BitsArrIsOn(arr1, index1) == 1);
	PrintTestResult(test_result, 1);

	/* test2 - check that off bit at specific index return 0, compare to expected result */
	test_result = (BitsArrIsOn(arr1, index2) == 0);
	PrintTestResult(test_result, 2);

	/* test3 - check that index out of bounds return -1, compare to expected result */
	test_result = (BitsArrIsOn(arr1, index3) == (-1));
	PrintTestResult(test_result, 3);
}

void TestBitsArrIsOff()
{
	int test_result = 0;
	size_t arr1 = (1ul << 5) | (1ul << 20) | (1ul << 63);
	size_t index1 = 5ul;
	size_t index2 = 62ul;
	size_t index3 = 64ul;

	printf("BitsArrIsOff Tests\n");

	/* test1 - check that off bit at specific index return 1, compare to expected result */
	test_result = (BitsArrIsOff(arr1, index2) == 1);
	PrintTestResult(test_result, 1);

	/* test2 - check that on bit at specific index return 0, compare to expected result */
	test_result = (BitsArrIsOff(arr1, index1) == 0);
	PrintTestResult(test_result, 2);

	/* test3 - check that index out of bounds return -1, compare to expected result */
	test_result = (BitsArrIsOff(arr1, index3) == (-1));
	PrintTestResult(test_result, 3);
}

void TestBitsArrRotR();

void TestBitsArrRotL();

void TestBitsArrToString();

void TestBitsArrMirror();

void TestBitsArrSetBit()
{

}
