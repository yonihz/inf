#include <stdio.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ 
#define IS_LENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ 
#define IS_LENDIAN 0
#endif

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

	printf("Is Little Endian (function): %d\n", l_end);
	printf("Is Little Endian (macro): %d\n", IS_LENDIAN);

	return (l_end);
}

