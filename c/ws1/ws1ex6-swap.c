#include <stdio.h>

void swap(int* x, int* y);

int main()
{
	int x, y;
	x=3;
	y=4;
	printf("Before swap: x = %d, y = %d\n",x,y);
	swap(&x,&y);
	printf("After swap: x = %d, y = %d\n",x,y);
}

void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}	

