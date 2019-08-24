#include <stdio.h>

int isLEndian(void);

int main()
{
	isLEndian();

	return (0);
}

int isLEndian(void)
{
	int x = 1;
	int l_end = *((char*)&x);

	printf("Is Little Endian: %d\n", l_end);

	return (l_end);
}

