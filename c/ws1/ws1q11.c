#include <stdio.h>

int main()
{
	/*
	int i;
	float f = 12.54;
	printf("float f*2=%f\n",f*2);
	f = i = f * 2;
	printf("int i=%d\n",i);
	printf("float f=%f\n",f);
	*/
	
	
	double d = 5;
	float f = 8/6;
	int i = 12;
	unsigned int ui = 2;
	printf("float 8/6=%f\n",f);
	printf("unsigned int ui-i=%d\n",ui-i);
	printf("unsigned int i*(ui-i)=%d\n",i*(ui-i));
	printf("double d/f=%f\n",d/f);
	i = d / f + i * (ui - i);
	printf("double d / f + i * (ui - i)=%f\n",d / f + i * (ui - i));
	printf("i=%d\n",i);
	
	
}
	
