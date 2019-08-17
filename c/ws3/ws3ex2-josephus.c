#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for calloc(), free() */

int Josephus(int size, int first);
int NextAlive(int i, int size, int arr[]);

int main( int argc, char *argv[] )
{
	int size = 0;
	int first = 0;

	(void)argc;
	(void)argv;

	if (2 != argc)
	{
		printf("Error: please enter one argument (integer > 1)\n");
		return (0);
	}	

	size = atoi(argv[1]);

	if (1 >= size)
	{
		printf("Error: please enter an integer > 1\n");
		return (0);
	}	

	printf("Number of soldiers = %d\n", size);

	printf("Last soldier = number %d\n", Josephus(size, first));

	return (0);
}

int Josephus(int size, int first)
{
	int i = first;
	int last_stabber = -1;
	int* arr = 0;

	arr = calloc(size, sizeof(int));

	while (last_stabber != i)
	{
			last_stabber = i;

			i = NextAlive(i, size, arr); /* find next soldier to be stabbed */

			arr[i] = 1;

			i = NextAlive(i, size, arr); /* find next soldier alive */	
	}

	free(arr);

	return i;
}

int NextAlive(int i, int size, int arr[])
{
	do 
	{
		if (i == size-1)
		{
			i = 0;
			continue;
		}
			
		i++;
	}
	while (arr[i] == 1);

	return (i);
}
