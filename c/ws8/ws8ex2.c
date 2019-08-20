#include <stdio.h>

#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define MAX3_1(a, b, c) (MAX2((a), (b)) > MAX2((a), (c)) ? MAX2((a), (b)) : MAX2((a), (c)))

#define MAX3_2(a, b, c) (MAX2((a), MAX2((b), (c))));

#define SIZEOF_VAR(x) (char*)(&x + 1) - (char*)(&x)

#define SIZEOF_TYPE(type) (char*)((type*)(10) + 1) - (char*)(type*)(10)

int main()
{
	int n1 = 0;
	int n2 = 0;
	n1 = MAX2(5,2);
	n2 = MAX3_2(5,8,2);

	printf("max2 is %d\n", n1);
	printf("max3 is %d\n", n2);
	printf("SIZEOF_VAR(n1) is %ld\n", SIZEOF_VAR(n1));
	printf("SIZEOF_TYPE(int) is %ld\n", SIZEOF_TYPE(int*));

	return (0);
}
