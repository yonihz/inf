#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int AtoiAnyBase(char* str, int b);
char* ItoaAnyBase(int n, int b);

int main()
{
	int n = 31;
	char* str1 = 0;
	char* str2 = "11111";
	int base = 2;

	str1 = ItoaAnyBase(n,base);
	printf("%d in base %d is %s\n",n, base, str1);
	printf("%s in base %d is %d\n", str2, base, AtoiAnyBase(str2, base));

	return (0);
}

int AtoiAnyBase(char* str, int b)
{
	int i = 0;
	int n = 0;
	int len = 0;
	int c = 0;
	
	len = strlen(str);

	while (i < len)
	{
		c = *(str + i);

		if (!isdigit(c) && !isalpha(c))
		{		
			printf("Input string must contain alphabetic or numeric chars\n");
			exit(1);
		}
		else if (isalpha(c))
		{
			c = toupper(c) - 55;
		}
		else
		{
			c = c - '0';
		}

		n = n * b + c;
		i++;
	}

	return (n);	
}

char* ItoaAnyBase(int n,int b)
{
	int n_temp = n;
	int len = 0;
	int i = 0;
	char* str = 0;
	
	while (n_temp)
	{
		n_temp /= b;
		len++;
	}
	
	str = malloc(len + 1);
	
	*(str + len) = '\0';

	while (i < len)
	{
		n_temp = n % b;
		*(str + len - 1 - i) = n_temp <= 9 ? n_temp + '0' : n_temp + 55; 
		n /= b;
		i++;
	}

	return (str);
}
