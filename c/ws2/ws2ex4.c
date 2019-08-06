#include <stdio.h> /* for printf() */

void SwapPtr(int** ptr1, int** ptr2);

int main()
{
	int a = 3;
	int b = 4;
	int* ptr1 = &a;
	int* ptr2 = &b;
	
	printf("Before swap: %d %d\n",*ptr1,*ptr2);
	SwapPtr(&ptr1,&ptr2);
	printf("After swap: %d %d\n",*ptr1,*ptr2);

	return (0);
}
	

void SwapPtr(int** ptr1, int** ptr2)
{
	int* ptr_t = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = ptr_t; 
}
