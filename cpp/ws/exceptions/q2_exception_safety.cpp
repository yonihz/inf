#include <iostream>
#include <typeinfo>
#include <cstdlib>

class X
{
public:
    X();
    ~X();

    int m_a;
};

int Foo(int)
{
    throw std::bad_alloc();
}

void Bar()
{
    throw std::bad_cast();
}

X::X() {}

X::~X()
{
    // try
    // {
    //     std::cerr << Foo(m_a) << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    std::cerr << Foo(m_a) << std::endl;
}

void Fishi()
{
    X x1;
    
    Bar();
}

int main()
{
    // try
    // {
    //     Fishi();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    Fishi();

    return 0;
}