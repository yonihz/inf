#include <stdio.h>

int main()
{
	
	unsigned int* ip = 0;
	float f = 3;
	float *fp = &f;
	ip = (unsigned int*) fp;
	printf("%u\n", *ip);
	
/*
	int* p = (int*)17;
	printf("%d\n", (int)(long)(p+4));
*/
	return (0);
}
