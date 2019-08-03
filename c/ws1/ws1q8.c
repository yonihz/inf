/* #include <stdio.h> */

long l = 8;
long *foo(){ return &l; }

int main()
{
	*(foo()) = 5;
	printf("%ld\n", l);
	return 0;
}
