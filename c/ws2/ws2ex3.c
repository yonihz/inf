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
	

void SevenBoom(int from, int to)
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
	
	str=malloc(len+1);

	while (i <= to)
	{
		if (i % 7 == 0)
		{
			printf("BOOM ");
		}
		else if (sprintf(str,"%d",i), Strchr(str,'7') != NULL)
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
