#include <iostream>

class X
{
public:
    explicit X();
    X(int a_);
    explicit X(int a_, int b_);
    X(const X& other_) : m_a(other_.m_a) { }
    void Foo();

private:
    int m_a;
};

X::X() : m_a(0) { }
X::X(int a_) : m_a(a_) { }
X::X(int a_, int b_) : m_a(a_ + b_) { }

void X::Foo()
{
    std::cout << m_a << std::endl;
}

void Fifi(X x_)
{
    x_.Foo();
}

int main()
{
    int a = 8;
    std::cout << static_cast<double>(a) << std::endl;
    std::cout << double(a) << std::endl;
    

    X x1(7);
    Fifi(x1);   // (1)
    Fifi(X(7.2)); // (2)
    Fifi(9.3);    // (3)
    Fifi(X(3,4));   // (4)
    return 0;
}