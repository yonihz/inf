#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Josephus(int size, int first);
int Str2Num(char* str);
int pow10(int x);

int main( int argc, char *argv[] )
{
	int size = 0;
	int first = 0;

	printf("argc = %d, argv[1] = %s, argv[1] =  %s\n", argc, argv[0], argv[1]);

	size = Str2Num(argv[1]);

	if (size == 0)
	{
		printf("Error: input entered is not an integer\n");
		return (0);
	}

	printf("Number of soldiers = %d\n", Str2Num(argv[1]));

	printf("Last soldier = number %d\n", Josephus(size, first));

	return (0);
}

int Josephus(int size, int first)
{
	int j = 0;	
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

			for	(j=0; j < size; j++)
			{
				printf ("%d ",arr[j]);
			}
			printf ("\n\n");
	}
	while (last_stabber != i);
	
	return i;
}

int Str2Num(char* str)
{
	int num = 0;
	int i = 0;
	int len = 0;
	int digit = 0;
	char* org;

	org = str;	
	
	len = strlen(str);

	str = str + len - 1;

	while ((str - org) >= 0)
	{
		if (!isdigit(*str))
		{
			return (0);
		}
	
		digit = (int)*str - '0';

		num = num + digit * pow10(i);

		str--;
		i++;		
	}
	
	return num;
}

int pow10(int x)
{
	double result=1;
	double base=10;
	int i;

	for (i=0;i<x;i++)
	{
		result*=base;
	}

	return result;
}
	

