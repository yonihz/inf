#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

/* "stty -icanon -echo" - stop terminal buffering and stop echoing keyboard pressing */
/* "stty icanon echo" - return termical to default state*/

void PressChar(char c);
void DoNothing(char c);

int main()
{
	int i = 0;
	int size_arr = 256; 	
	char c = 0;

	typedef void (*f_ptr_t)(char);
	
	f_ptr_t *f_arr = malloc(256 * sizeof(f_ptr_t));

	if (NULL == f_arr)
	{
		fprintf(stderr,"Out of memory\n");
		exit (1);
	}

	for (i = 0; i < size_arr; i++)	/* init array of function pointers to DoNothing() */
	{
		f_arr[i] = &DoNothing;
	}

	f_arr[(int)'A'] = &PressChar;
	f_arr[(int)'T'] = &PressChar;

	printf("Press any key\n");

	c = getchar();

	while (27 != c)
	{
		f_arr[(int)c](c);		

		printf("Press any key\n");

		c = getchar();
	}

	printf("ESC pressed\n\n");

	free(f_arr);
		
	return (0);
}

void PressChar(char c)
{
	printf("%c pressed\n\n", c);
}

void DoNothing(char c)
{
	UNUSED(c);
}
