#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for string functions implementation */
#include <string.h> /* for standard string functions */


int main()
{
	char str1[]="AbcbA";

	printf("isPalindrome %s %d\n",str1,isPalindrome(str1));

	return (0);
}
	

int isPalindrome(const char *str)
{
	int i = 0;
	size_t len = Strlen(str);

	while (i < len/2)
	{
		if (*(str + i) != *(str + len - i - 1))
		{
			return (0);
		}

		i++;	
	}
	
	return (1);
}
