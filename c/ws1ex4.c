#include <stdio.h>

double pow10(int x);
int main()
{
int x;

x=4;
printf("10^(%d)	= %.0f\n",x,pow10(x));

x=1;
printf("10^(%d)	= %.0f\n",x,pow10(x));

x=0;
printf("10^(%d)	= %.0f\n",x,pow10(x));

x=-3;
printf("10^(%d)	= %.3f\n",x,pow10(x));
}

double pow10(int x)
{
double result=1;
double base=10;
int i;

if (x < 0)
{
	x*=-1;
	base=0.1;
}

for (i=0;i<x;i++)
{
	result*=base;
}

return result;
}
