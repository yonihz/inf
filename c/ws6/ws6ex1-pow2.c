#include <stdio.h>

long pow2(unsigned int x, unsigned int y);

int main()
{
	unsigned int x = 3;
	unsigned int y = 3;
	printf("%d * (2 ^ %d) = %ld\n", x, y, pow2(x,y));

	return (0);
}

long pow2(unsigned int x, unsigned int y)
{
	return x << y; /* x * (2 ^ y) */
}
