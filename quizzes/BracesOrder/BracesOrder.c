#include <stdio.h>
#include <string.h>

#include "stack.h"

#define LUT_SIZE 256

int IsBracesValid(char str[], int braces_lut[]);

int main()
{
	int braces_lut[LUT_SIZE];
	int i = 0;

	for (i = 0; i < LUT_SIZE; i++)
	{
		braces_lut[i] = 0;
	}

	braces_lut['('] = 1;
	braces_lut['['] = 1;
	braces_lut['{'] = 1;

	braces_lut[')'] = '(';
	braces_lut[']'] = '[';
	braces_lut['}'] = '{';

	IsBracesValid("({5+3*6+4*{(8*9)}*10}", braces_lut) ?
	printf("SUCCESS\n\n") : printf("FAIL\n\n");

	IsBracesValid("({5+3*6+4*{(8*9)}*10})", braces_lut) ?
	printf("SUCCESS\n\n") : printf("FAIL\n\n");

	IsBracesValid(")({5+3*6+4*{(8*9)}*10}", braces_lut) ?
	printf("SUCCESS\n\n") : printf("FAIL\n\n");

	IsBracesValid("5+3*(5+3*6+4*{(8*9)}*10}", braces_lut) ?
	printf("SUCCESS\n\n") : printf("FAIL\n\n");

	IsBracesValid("5+798+**777", braces_lut) ?
	printf("SUCCESS\n\n") : printf("FAIL\n\n");

	return(0);
}

int IsBracesValid(char str[], int braces_lut[])
{
	int i = 0;
	size_t len = 0;
	stack_t* stack = NULL;

	len = strlen(str);
	printf("%s\n", str);

	stack = StackCreate(len, sizeof(char));
	i = 0;

	while (*(str+i))
	{
		char op = braces_lut[*(char*)(str+i)];
	
		if (op == 1)
		{
			StackPush(stack, (str+i));
		}
		else if (op)
		{

			if (!StackPeek(stack))
			{
				return (0);
			}
			
			if (*(char*)StackPeek(stack) == op)
			{
				StackPop(stack);
			}
			else
			{
				return (0);
			}
		}

		i++;
	}

	if (!StackPeek(stack))
	{
		return (1);
	}
	
	if (*(char*)StackPeek(stack))
	{
		return (0);
	}

	return (1);	
}
