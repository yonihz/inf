#include <stdio.h>
#include <stdlib.h>

/* Use system("stty -icanon -echo") to stop terminal buffering, and stop echoing keyboard pressing */
/* Use system("stty icanon echo") to return termical to its default state */

void PressChar(char c);
void DoNothing(void);

int main()
{
	char c = 0;

	printf("Press any key\n");

	c = getchar();

	while (27 != c)
	{
		switch (c)
		{
			case 'A':
			{
				PressChar(c);
				break;
			}
			case 'T':
			{
				PressChar(c);
				break;
			}
			default:
			{
				DoNothing();
			}
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
