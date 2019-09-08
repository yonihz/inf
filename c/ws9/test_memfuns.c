#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "memfuncs.h"

#define ARR_SIZE 40

int TestMemset(char *s1, char* s2, size_t n, char c, int offset);
int TestMemcpy(char dest1[], char src1[], char dest2[], char src2[], size_t n, int offset_dest, int offset_src);
int TestMemmove(char dest1[], char src1[], char dest2[], char src2[], size_t n, int offset_dest, int offset_src);

int main()
{
	char arr1[ARR_SIZE];
	char arr2[ARR_SIZE];
	char arr1m[ARR_SIZE];
	char arr2m[ARR_SIZE];

	/* bus error detection (disable all prints before running) */
	/*
 	__asm__("pushf\norl $0x40000,(%rsp)\npopf");
	*/

	/* test - memset */
	
	TestMemset(arr1, arr1m, 20, 1, 0);
	TestMemset(arr1, arr1m, 6, 1, 0);
	TestMemset(arr1, arr1m, 20, 1, 5);
	TestMemset(arr1, arr1m, 6, 1, 5);

	/* test - memcpy */
	
	TestMemcpy(arr2, arr1, arr2m, arr1m, 20, 4, 2);
	TestMemcpy(arr2, arr1, arr2m, arr1m, 20, 2, 4);
	TestMemcpy(arr2, arr1, arr2m, arr1m, 20, 4, 0);
	TestMemcpy(arr2, arr1, arr2m, arr1m, 20, 0, 4);
	

	/* test - memmove */
	
	TestMemmove(arr1, arr1, arr1m, arr1m, 20, 8, 16);
	TestMemmove(arr1, arr1, arr1m, arr1m, 20, 16, 8);
	TestMemmove(arr1, arr1, arr1m, arr1m, 20, 8, 0);
	TestMemmove(arr1, arr1, arr1m, arr1m, 20, 16, 0);
	
	return (0);
}

int TestMemset(char *s1, char* s2, size_t n, char c, int offset)
{
	size_t i = 0;
	size_t status = 0;

	printf("\n\nMemset test - %lu bytes\n", n);

	for (i = 0; i < ARR_SIZE; i++) { s1[i] = 0; s2[i] = 0; }
	
	Memset(s1+offset, c, n * sizeof(char));
	memset(s2+offset, c, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", s1[i]); } printf("\n");
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", s2[i]); } printf("\n");

	status = strcmp(s1, s2);
	status ? printf("Test fail\n") : printf("Test pass\n") ;
	return status;
}

int TestMemcpy(char dest1[], char src1[], char dest2[], char src2[], size_t n, int offset_dest, int offset_src)
{
	size_t i = 0;
	int status = 0;

	for (i = 0; i < ARR_SIZE; i++) { src1[i] = i; dest1[i] = 0; src2[i] = i; dest2[i] = 0; }

	printf("\n\nMemcpy test - %lu bytes\n", n);

	Memcpy(dest1+offset_dest, src1+offset_src, n * sizeof(char));
	memcpy(dest2+offset_dest, src2+offset_src, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", src1[i]); } printf("\n");
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", dest1[i]); } printf("\n\n");
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", src2[i]); } printf("\n");
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", dest2[i]); } printf("\n\n");
	
	status = strcmp(dest1, dest2);
	status ? printf("Test fail\n") : printf("Test pass\n") ;
	return status;
}

int TestMemmove(char dest1[], char src1[], char dest2[], char src2[], size_t n, int offset_dest, int offset_src)
{
	size_t i = 0;
	int status = 0;

	for (i = 0; i < ARR_SIZE; i++) { src1[i] = i; dest1[i] = i; src2[i] = i; dest2[i] = i; }

	printf("\n\nMemmove test - %lu bytes\n", n);

	Memmove(dest1+offset_dest,src1+offset_src, n * sizeof(char));
	memmove(dest2+offset_dest,src2+offset_src, n * sizeof(char));
	
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", dest1[i]); } printf("\n\n");
	for (i = 0; i < ARR_SIZE; i++) { printf("%2d ", dest2[i]); } printf("\n\n");

	status = strcmp(dest1, dest2);
	status ? printf("Test fail\n") : printf("Test pass\n") ;
	return status;
}
