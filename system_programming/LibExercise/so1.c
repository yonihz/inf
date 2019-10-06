#include <stdio.h>

extern void Foo1();

void Bar1()
{
    printf("Bar1()\n");
    Foo1();
}
