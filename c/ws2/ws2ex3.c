#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for string functions implementation */
#include <string.h> /* for standard string functions */

void SevenBoom(int from, int to);

int main()
{
	int a = 1; /* from */
	int b = 117; /* to */
	
	printf("SevenBoom %d %d\n",a,b);

	SevenBoom(a,b);

	return (0);
}
	

void SevenBoom(int from, int to) /* using string functions */
{
	int i = from;
	int n = to;
	int len;
	char *str;
	
	while (n != 0)
	{
		n /= 10;
		len++;
	}	
	
	str=malloc(len+1); /* malloc for a string later used by sprintf, size of the number of digits of "to" var */

	while (i <= to)
	{
		if (i % 7 == 0) /* if mod 7 is zero - BOOM */
		{
			printf("BOOM ");
		}
		else if (sprintf(str,"%d",i), Strchr(str,'7') != NULL) /* create a string from the int, and check if it contains 7 with Strchr */
		{
			printf("BOOM ");
		}
		else
		{
			printf("%d ",i);
		}
		
		i++;
	}
	printf("\n");
}
