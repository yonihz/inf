#include <stdio.h>
#include <math.h>

int isPow2Loop(unsigned int n);
int isPow2NoLoop(unsigned int n);

int main()
{
	unsigned int n = 128;

	printf("%u is a power of two? %d\n", n, isPow2Loop(n));

	printf("%u is a power of two? %d\n", n, isPow2NoLoop(n));

	return (0);
}

int isPow2Loop(unsigned int n)
{
	unsigned int m = 1;

	while (m <= n)
	{
		if (n == m)
		{
			return (1);
		}

		m = m << 1;
	}

	return (0);
}

int isPow2NoLoop(unsigned int n)
{
	if ( ( n ^ (-(~n))) == 1 )
	{
		return (1);
	}

	return (0);	
}
