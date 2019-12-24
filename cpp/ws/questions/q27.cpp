#include <iostream>

using namespace std;


class X
{
    friend ostream& operator<<(ostream& os_, const X& x_);

public:
    X(int a) : m_a(a) { }

    int GetValue() const { return m_a; }

private:
    int m_a;
};

int main()
{
    X x1(3);
    X x2(6);

    int i = 78;
    double d = 3.14;
    char c = 'Y';

    std::cout
        << " x1:" << x1
        << " x2:" << x2
        << " " << i << " " << &i
        << " " << d << " " << &d
        << " " << c << " " << (void*)&c << std::endl;

    return 0;
}

// ostream& operator<<(ostream& os_, const X& x_);

ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}