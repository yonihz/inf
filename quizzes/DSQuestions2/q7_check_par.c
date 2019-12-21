/* compile command:
gd q7_check_par.c ../../ds/stack.c -I../../ds/include
*/

#include <stdio.h>
#include <string.h>

#include "stack.h"

#define LUT_SIZE 256

typedef enum {INVALID = 0, VALID = 1} status_t;

unsigned char par_lut[LUT_SIZE];

status_t IsValidPar(char str[]);
void InitLUT();

int main()
{
	IsValidPar("(x + 3 * [4 + 6]) <>") ?
	printf("VALID\n") : printf("INVALID\n");

	IsValidPar("(8 ]* (6 + 2) + 1)") ?
	printf("VALID\n") : printf("INVALID\n");

	IsValidPar("[(8 ]* (6 + 2) + 1)") ?
	printf("VALID\n") : printf("INVALID\n");

	return(0);
}

status_t IsValidPar(char str[])
{
    static int is_lut_init = 0;
	size_t i = 0, len = 0;
    char op = 0;
	stack_t* stack = NULL;

    if (0 == is_lut_init)
    {
        is_lut_init = 1;
        InitLUT();
    }

	len = strlen(str);
	printf("%s ", str);

	stack = StackCreate(len, sizeof(char));

	while (*(str+i))
	{
		op = par_lut[(size_t)*(char*)(str+i)];
	
		if (op == 1)
		{
			StackPush(stack, (str+i));
		}
		else if (op > 1)
		{
			if (StackIsEmpty(stack))
			{
                StackDestroy(stack);
				return (INVALID);
			}

			if (*(char*)StackPeek(stack) == op)
			{
				StackPop(stack);
			}
            else
            {
                StackDestroy(stack);
                return (INVALID);
            } 
		}

		i++;
	}

	if (StackIsEmpty(stack))
	{
        StackDestroy(stack);
		return (VALID);
	}
	

    StackDestroy(stack);
    return (INVALID);
}

void InitLUT()
{
	size_t i = 0;

	for (i = 0; i < LUT_SIZE; i++)
	{
		par_lut[i] = 0;
	}

    par_lut['('] = 1;
	par_lut['['] = 1;
	par_lut['{'] = 1;
    par_lut['<'] = 1;

	par_lut[')'] = '(';
	par_lut[']'] = '[';
	par_lut['}'] = '{';
    par_lut['>'] = '<';
}
