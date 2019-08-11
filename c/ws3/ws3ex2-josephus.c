#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for calloc(), free() */

int Josephus(int size, int first);

int main( int argc, char *argv[] )
{
	int size = 0;
	int first = 0;

	(void)argc;
	(void)argv;

	size = atoi(argv[1]);

	printf("Number of soldiers = %d\n", size);

	printf("Last soldier = number %d\n", Josephus(size, first));

	return (0);
}

int Josephus(int size, int first)
{
	int i = first;
	int last_stabber = first;
	int* arr = 0;

	arr = calloc(size, sizeof(int));

	do
	{
			last_stabber = i;
			
			do /* find next soldier to be stabbed */
			{
				if (i == size-1)
				{
					i = 0;
					continue;
				}
			
				i++;
			}
			while (arr[i] == 1);

			arr[i] = 1;

			do /* find next soldier alive */
			{
				if (i == size-1)
				{
					i = 0;
					continue;
				}
			
				i++;
			}
			while (arr[i] == 1);
	}
	while (last_stabber != i);
	
	return i;
}
