#include <stdio.h>

int main()
{
int a = 3;
int foo();
printf("%d\n",a);
printf("%p\n",foo);
printf("%d\n",foo());
printf("%d\n",a+foo());
printf("%p\n",&a);
}
