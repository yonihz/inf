/****************************************************************
* 																*
* FILE NAME: cbuff_test.c										*
* 																*
* PURPOSE: Testing cbuff functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 08.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h> /* strlen */
#include <time.h> /* time */
#include <stdlib.h> /* srand */

#include "cbuff.h"
#include "verify_funcs.h"

struct c_buff
{
	char* arr;
	size_t cap;
	size_t size;
	size_t read_idx;
};

/* API test functions */

void TestBasics();
void TestWriteReadCirc();
void CreateStr(char* str);
void CleanStr(char* str);
void TestStress();

int main()
{
	srand(time(NULL));

	TestBasics();
	TestWriteReadCirc();
	TestStress();
    
	return (0);
}

/* Test functions for API */

void TestBasics()
{
	char arr_src[8] = "ABCDEFG";
	char arr_dest[8];
	cbuff_t* cbuff1 = NULL;

	printf("Basic Tests\n");

	cbuff1 = CBuffCreate(sizeof(arr_src) - 1);

	VerifySizet(CBuffCapacity(cbuff1), 7,
	"TEST1  - CAPACITY AFTER CREATE");

	VerifySizet(CBuffFreeSpace(cbuff1), 7,
	"TEST2  - FREESPACE AFTER CREATE");
	
	VerifyInt(CBuffIsEmpty(cbuff1), 1,
	"TEST3  - ISEMPTY RETURNS 1 AFTER CREATE");

	VerifySizet(CBuffWrite(cbuff1, arr_src, 5), 5,
	"TEST4  - WRITE RETURN VALUE");

	VerifySizet(CBuffFreeSpace(cbuff1), 2,
	"TEST5  - FREESPACE AFTER WRITE");
	
	VerifyInt(CBuffIsEmpty(cbuff1), 0,
	"TEST6  - ISEMPTY RETURNS 0 AFTER WRITE");

	VerifySizet(CBuffRead(cbuff1, arr_dest, 5), 5,
	"TEST7  - READ RETURN VALUE");

	VerifySizet(CBuffFreeSpace(cbuff1), 7,
	"TEST8  - FREESPACE AFTER READ ALL");
	
	VerifyInt(CBuffIsEmpty(cbuff1), 1,
	"TEST9  - ISEMPTY RETURNS 1 AFTER READ ALL");

	VerifySizet(CBuffWrite(cbuff1, arr_src, 9), 7,
	"TEST10 - WRITE RETURN VALUE WHEN N>SIZE");

	VerifySizet(CBuffRead(cbuff1, arr_dest, 20), 7,
	"TEST11 - READ RETURN VALUE WHEN N>SIZE");

	CBuffDestroy(cbuff1);
}

void TestWriteReadCirc()
{
	char arr_src[8] = "ABCDEFG";
	char arr_dest[6] = "00000";
	char arr_src2[6] = "ABCDE";
	cbuff_t* cbuff1 = NULL;

	printf("Write/Read circular Tests\n");

	cbuff1 = CBuffCreate(sizeof(arr_src) - 1);

	CBuffWrite(cbuff1, arr_src, 5);
	CBuffRead(cbuff1, arr_dest, 5);

	VerifySizet(cbuff1->read_idx, 5,
	"TEST1 - READ_IDX INCREASES AFTER WRITE AND READ");

	CBuffWrite(cbuff1, arr_src, 5);

	VerifyStrncmp(cbuff1->arr, "CDEDEAB",strlen("CDEDEAB"),
	"TEST2 - CHECK ARR AFTER WRITE");

	CBuffRead(cbuff1, arr_dest, 5);

	VerifyChar(arr_src2, arr_dest,
	"TEST3 - CHECK READ AFTER WRITE");

	CBuffDestroy(cbuff1);
}

void TestStress()
{
	char arr_src[8] = {0,0,0,0,0,0,0,0};
	char arr_dest[8] = {0,0,0,0,0,0,0,0};
	size_t i = 0;
	cbuff_t* cbuff1 = NULL;

	printf("Write/Read stress Tests\n");

	cbuff1 = CBuffCreate(sizeof(arr_src) - 1);

	for (i = 0; i < 30; i++)
	{
		CreateStr(arr_src);
		CleanStr(arr_dest);
		CBuffWrite(cbuff1, arr_src, strlen(arr_src));
		CBuffRead(cbuff1, arr_dest, strlen(arr_src));
		VerifyChar(arr_dest, arr_src,
		"STRESS TEST - WRITE / READ");
		CleanStr(arr_src);
		CleanStr(arr_dest);
	}

	CBuffDestroy(cbuff1);
}

void CreateStr(char* str)
{
	size_t len = 8;
	size_t i = 0;

	len = rand() % len;	
	for (i = 0; i < len; i++)
	{
		*(str+i) = 65 + rand() % 25;
	}
	*(str+i) = '\0';
}

void CleanStr(char* str)
{
	size_t len = strlen(str);
	size_t i = 0;
	
	for (i = 0; i <= len; i++)
	{
		*(str+i) = '\0';
	}
}
