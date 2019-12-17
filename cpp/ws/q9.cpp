#include <stdio.h>

struct X
{
    void Foo();
    void Foo() const;
};

void X::Foo()
{
    printf("Foo\n");
}

void X::Foo() const
{
    printf("const Foo\n");
}

int main()
{
    X x1;
    const X x2;
    const X &x3 = x1;

    x1.Foo(); // (1)
    x2.Foo(); // (2)
    x3.Foo(); // (3)

    return 0;
}