#include <stdio.h> /* for printf() */

void SevenBoom(int from, int to);

int main()
{
	int a = 1; /* from */
	int b = 117; /* to */
	
	printf("SevenBoom %d %d\n",a,b);

	SevenBoom(a,b);

	return (0);
}

void SevenBoom(int from, int to) /* without string functions */
{
	int i = from;
	int n;
	int found = 0;

	while (i <= to)
	{
		found = 0;

		if (i % 7 == 0) /* if mod 7 is zero - BOOM */
		{
			printf("BOOM ");

			found = 1;
		}

		n = i;

		while (found == 0 && n != 0) /* if contains 7 - BOOM */
		{
			if (n % 10 == 7)
			{
				printf("BOOM ");
				n /= 10;
				found = 1;
			}

			n /= 10;				
		}
		
		if (found == 0)
		{
			printf("%d ",i);
		}

		i++;
	}

	printf("\n");
}
