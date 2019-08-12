#include <stdio.h>
#include <stdlib.h>

/* Use system("stty -icanon -echo") to stop terminal buffering, and stop echoing keyboard pressing */
/* Use system("stty icanon echo") to return termical to its default state */

void PressChar(char c);
void DoNothing(void);

int main()
{
	int c = 0;

	printf("Press any key\n");

	c = getchar();

	while (27 != c)
	{
		if ('A' == c)
		{
			PressChar(c);
		}
		else if ('T' == c)
		{
			PressChar(c);
		}
		else
		{
			DoNothing();
		}

		printf("Press any key\n");

		c = getchar();
	}	
	
	printf("ESC pressed\n\n");	

	return (0);
}

void PressChar(char c)
{
	printf("%c pressed\n\n", c);
}

void DoNothing(void)
{ }
