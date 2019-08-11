#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for Strlen() */

char* AddLargeNums(char* result, const char* num1, const char* num2);
void SwapPtr(int** ptr1, int** ptr2);

int main()
{
	/* test */
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
		
	size_t len1 = Strlen(num1);
	size_t len2 = Strlen(num1);
	char* num1_org = (char *)num1;
	char* num2_org = (char *)num2;
	int add;

	printf("%s + %s\n",num1, num2); /* print for tests */

	if (len2 > len1)
	{
		SwapPtr(&num1, &num2);
	}
	
	*(result+len1+1) = '\0';

	num1 = num1 + len1 - 1; /* start of addition from the string end - where the smallet digit is */
	num2 = num2 + len2 - 1;
	result = result + len1 - 1;

	*result = '0'; /* init string for later addition */

	while ((num2 - num2_org) >= 0)
	{
		add = (int)(num1 + num2 + result) - 3*'0'; /* add two digits + 1 (if last add was 10 or more) */ 
	
		*(result-1) = (add > 9) ? 1 + '0' : 0 + '0';

		add %= 10;
			
		*result = add + '0';

		num1--;
		num2--;
		result--;	
	}
	
	while ((num1 - num1_org) >= 0) /* if one string ended continue with the second one */
	{
		add = (int)(num1 + result) - 2*'0';

		*(result-1) = (add > 9) ? 1 + '0' : 0 + '0';

		add %= 10;
			
		*result = add + '0';

		num1--;
		result--;
	}
	
	if (*result == '0') /* if largest digit is 0 return string string after it */
	{
		return (result+1);
	}
	return (result);
}

void SwapPtr(int** ptr1, int** ptr2)
{
	int* ptr_t = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = ptr_t; 
}

