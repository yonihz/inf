#include <iostream>

void Foo(const double& a);
void Bar(double& a);

int main()
{
    int a = 5;
    std::cout << "main" << std::endl;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
    Foo(a);
    Bar(reinterpret_cast<double&>(a));
    std::cout << "main" << std::endl;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
}

void Foo(const double& a)
{
    std::cout << "Foo" << std::endl;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
}

void Bar(double& a)
{
    std::cout << "Bar" << std::endl;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
    // a=6;
}

