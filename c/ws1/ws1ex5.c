#include <stdio.h>

int pow10(int x);
int flip(int x);

int main()
{
	int x = 12340;
	printf("x = %d\n",x);
	printf("flip(x) = %d\n",flip(x));
}

int flip(int x)
{
	int x_size10=0;

	while(x%(pow10(x_size10))-x) /* find the power of 10 of the last digit */
	{
		x_size10++;
	}

	//printf("x_size10=%d\n",x_size10);
	
	int result=0;
	int result_t, mod_t;
	int i;
	result_t=x;	

	for (i=0;i<x_size10;i++)
	{
		mod_t=result_t%10;		
		result_t=(result_t-mod_t)/10;
		result+=mod_t*(pow10(x_size10-i-1));
		//printf("i=%d\n",i);
		//printf("mod_t=%d\n",mod_t);
		//printf("result_t=%d\n",result_t);
		//printf("result=%d\n",result);
	}

	return result;
}

int pow10(int x)
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
