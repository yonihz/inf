#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* toupper */

int AtoiAnyBase(const char* str, int base);
char* ItoaAnyBase(int n, int b);

int main()
{
	int n = 31;
	char* str1 = 0;
	char* str2 = "1F";
	int base = 16;

	str1 = ItoaAnyBase(n,base);
	printf("%d in base %d is %s\n",n, base, str1);
	printf("%s in base %d is %d\n", str2, base, AtoiAnyBase(str2, base));

	strcmp(str1, "1F") ?
	printf("ITOA TEST FAILED\n") : printf("ITOA TEST PASSED\n");  
	
	AtoiAnyBase(str2, base) == 31 ?
	printf("ATOI TEST PASSED\n") : printf("ATOI TEST FAILED\n");  
	
	free(str1);

	return (0);
}

int AtoiAnyBase(const char* str, int base)
{
	int i = 0;
	int n = 0;
	int len = 0;
	int c = 0;
	int isNeg = 1;

	if (*str == '-')
	{
		isNeg = -1;
		str++;	
	}

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
		else if (base > 10 && (toupper(c) > 'A' + base - 11))
		{
			printf("Input string does not match base\n");
			exit(1);
		}
		
		if (isalpha(c))
		{
			c = toupper(c) - ('A' - 10);
		}
		else
		{
			c = c - '0';
		}

		n = n * base + c;
	}

	n *= isNeg;

	return (n);	
}

char* ItoaAnyBase(int n, int base)
{
	int n_temp = n;
	int len = 0;
	int i = 0;
	char* str = 0;
	int isNeg = 0;

	if (n < 0)
	{
		isNeg = 1;
		n *= -1;
	}
	
	len += isNeg;
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

	if (isNeg)
	{
		*str = '-';
	}

	return (str);
}
