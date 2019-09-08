#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* toupper */

unsigned int AtoiAnyBase(const char* str, unsigned int base);
char* ItoaAnyBase(unsigned int n, unsigned int b);

int main()
{
	unsigned int n = 31;
	char* str1 = 0;
	char* str2 = "11111";
	unsigned int base = 2;

	str1 = ItoaAnyBase(n,base);
	printf("%d in base %d is %s\n",n, base, str1);
	printf("%s in base %d is %d\n", str2, base, AtoiAnyBase(str2, base));

	strcmp(str1, "11111") ?
	printf("ITOA TEST FAILED\n") : printf("ITOA TEST PASSED\n");  
	
	AtoiAnyBase(str2, base) == 31 ?
	printf("ATOI TEST PASSED\n") : printf("ATOI TEST FAILED\n");  
	
	free(str1);

	return (0);
}

unsigned int AtoiAnyBase(const char* str, unsigned int base)
{
	unsigned int i = 0;
	unsigned int n = 0;
	unsigned int len = 0;
	unsigned int c = 0;
	
	len = strlen(str);

	for (i = 0; i < len; i++)
	{
		c = *(str + i);

		if (!isdigit(c) && !isalpha(c))
		{		
			printf("Input string must contain alphabetic or numeric chars\n");
			exit(1);
		}
		if (base <= 10 && (!isdigit(c) || (c > '0' + base - 1)))
		{
			printf("Input string does not match base\n");
			exit(1);
		}
		if (base > 10 && ((unsigned int)toupper(c) > 'A' + base - 11))
		{
			printf("Input string does not match base\n");
			exit(1);
		}
		else if (isalpha(c))
		{
			c = toupper(c) - ('A' - 10);
		}
		else
		{
			c = c - '0';
		}

		n = n * base + c;
	}

	return (n);	
}

char* ItoaAnyBase(unsigned int n, unsigned int base)
{
	int n_temp = n;
	int len = 0;
	int i = 0;
	char* str = 0;
	
	while (n_temp)
	{
		n_temp /= base;
		len++;
	}
	
	str = malloc(len + 1);
	
	*(str + len) = '\0';

	for (i = 0; i < len; i++)
	{
		n_temp = n % base;
		*(str + len - 1 - i) = n_temp <= 9 ? n_temp + '0' : n_temp + 'A' - 10; 
		n /= base;
	}

	return (str);
}
