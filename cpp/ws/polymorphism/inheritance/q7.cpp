#include <iostream>

class X;

void Foo(X x);

class X
{
public:
    X() {std::cout << "X Ctor" << this << "\n";}
    virtual ~X() {std::cout << "X Dtor" << this << "\n";}
    // int m_x_public;

private:
    double m_a;
};

class Y: public X
{
public:
    Y() {std::cout << "Y Ctor" << this << "\n";}
    virtual ~Y() {std::cout << "Y Dtor" << this << "\n";}
    // int m_y_public;

private:
    int m_b;
};

// void Foo(X x)
// {
// std::cout << x.m_x_public << std::endl;
// x.m_x_public = 3;
// std::cout << x.m_x_public << std::endl;
// }

int main()
{
    // Y y1;
    // y1.m_x_public = 2;
    // Foo(y1);
    // std::cout << y1.m_x_public << std::endl;
    X x1;
    Y y1;
    std::cout << "sizeof(x1) " << sizeof(x1) << std::endl;
    std::cout << "sizeof(y1) " << sizeof(y1) << std::endl;

    X *xp = new Y[3];
    delete[] xp; // crash - expected size of X but gets ptr to Y
    return 0;
}