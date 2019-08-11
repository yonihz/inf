#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for Strlen() */

char* AddLargeNums(char* result, const char* num1, const char* num2);
void SwapPtr(char** ptr1, char** ptr2);
void SwapNum(int* num1, int* num2);
int Ascii2Num(int a);
int Num2Ascii(int n);

int main()
{
	/* test */
	char* result = 0;

	result = malloc(5);
	printf("%s\n\n",AddLargeNums(result, "111","222"));
	free(result);
	
	result = malloc(6);
	printf("%s\n\n",AddLargeNums(result, "11","2222"));
	free(result);

	result = malloc(6);
	printf("%s\n\n",AddLargeNums(result, "2222","11"));
	free(result);

	result = malloc(5);
	printf("%s\n\n",AddLargeNums(result, "999","1"));
	free(result);

	result = malloc(6);
	printf("%s\n\n",AddLargeNums(result, "9999","1111"));
	free(result);

	return (0);
}

char* AddLargeNums(char* result, const char* num1, const char* num2)
{
		
	int len1 = Strlen(num1);
	int len2 = Strlen(num2);
	char* num1_org = 0;
	char* num2_org = 0;
	int add;

	printf("%s + %s\n",num1, num2); /* print for tests */

	if (len2 > len1) /* set num1 as the larger num using value and pointer swap */
	{
		SwapPtr((char **)&num1, (char **)&num2);
		SwapNum(&len1, &len2);
	}

	num1_org = (char *)num1;
	num2_org = (char *)num2;

	*(result+len1+1) = '\0';

	num1 += len1 - 1; /* start of addition from the string end - where the smallet digit is */
	num2 += len2 - 1;
	result += len1;

	*result = '0'; /* init string for later addition */

	while ((num2 - num2_org) >= 0)
	{
		add = Ascii2Num(*num1) + Ascii2Num(*num2) + Ascii2Num(*result); /* add two digits + 1 (if last add was 10 or more) */ 
	
		*(result-1) = (add > 9) ? Num2Ascii(1) : Num2Ascii(0);

		add %= 10;
			
		*result = Num2Ascii(add);

		num1--;
		num2--;
		result--;	
	}
	
	while ((num1 - num1_org) >= 0) /* if one string ended continue with the second one */
	{
		add = Ascii2Num(*num1) + Ascii2Num(*result);

		*(result-1) = (add > 9) ? Num2Ascii(1) : Num2Ascii(0);

		add %= 10;
			
		*result = Num2Ascii(add);

		num1--;
		result--;
	}
	
	if (*result == '0') /* if largest digit is 0 return string string after it */
	{
		result += 1;
	}
	return (result);
}

void SwapPtr(char** ptr1, char** ptr2)
{
	char* ptr_t = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = ptr_t; 
}

void SwapNum(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp; 
}

int Ascii2Num(int a)
{
	return (a - '0');
}

int Num2Ascii(int n)
{
	return (n + '0');
}

