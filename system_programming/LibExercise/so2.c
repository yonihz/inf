#include <stdio.h>

extern void Foo2();

void Bar2()
{
    printf("Bar2()\n");
    Foo2();
}
