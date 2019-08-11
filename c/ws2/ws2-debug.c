#include <stdio.h>

int main()
{
	/* valgrind tests */
	/*
	int* arr;
	int aa;

	arr = malloc(10*sizeof(int));

	if (*arr == 1)
		return 0;

	arr[1] = 1;	

	aa = arr[11];

	arr[12] = 8;

	free(arr);

	aa = *arr;
	*/

	/* core dump tests */

	int i = 0;
	
	while (1)
		i++;
	
	return 0;
}

/* send SIGABRT: kill -SIGABRT <process-number> */
/* set unlimited core dump file limit: ulimit -c unlimited
/* the file "core" is generated after sending the SIGABRT in the program directory */
/* to debug: gdb -tui a.out core */
