#include <cstdio>

class X
{
public:
    explicit X(int a_ = 0);
    void Foo();
    friend void Foo(const X &x1);

private:
    int m_a;
};

X::X(int a_)
    : m_a(a_ )
{
}

void X::Foo()
{
    printf("%d\n", m_a);
}

void Foo(const X &x1)
{
    printf("%d\n", x1.m_a);
}

int main()
{
    X x1;

    x1.Foo();
    //printf("%d\n", x1.m_a);
    Foo(x1);

    return 0;
}