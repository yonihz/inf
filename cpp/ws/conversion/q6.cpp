#include <iostream>

class X
{
public:
    explicit X();
    operator unsigned int();
    operator int();
    // operator double();

private:
    int m_a;
};

X::X() : m_a(7)
{

}

X::operator int()
{
    return m_a;
}

X::operator unsigned int()
{
    return m_a;
}

void Fifi(double x_)
{
    std::cout << x_ << std::endl;
}


int main()
{
    X x1;

    Fifi(9);    // (1)
    Fifi(x1);   // (2)

    return 0;
}