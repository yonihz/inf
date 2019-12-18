#include <stdio.h>

struct X
{
    explicit X();

    explicit X(int a_, int b_);

    ~X();

    X(const X& other_);

    X& operator=(const X& other_);

    int m_a;
    const int m_b;
};

X::X()
    : m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void*)this, m_a, m_b);
    m_a = 9;
    // m_b = 11;
}

X::X(int a_, int b_)
    : m_a(a_), m_b(b_)
{
    printf("Ctor(int,int): %p, %d, %d\n", (void*)this, m_a, m_b);
}

X::X(const X& other_)
    : m_a(other_.m_a), m_b(other_.m_b)
{
    printf("Copy Ctor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    //m_b = other_.m_b;

    printf("Copy Assignment: %p, %d, %d\n", (void*)this, m_a, m_b);

    return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

struct Y
{
    X m_x;
    int m_i;
};

int main()
{
    X x1;
    X x2(7,1);
    X x3(9, 10);
    X x4(x1);

    x1 = x3;

    Y y1 = {X(0, 0), 0};
    y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3 = {X(0, 0), 0};
    y3 = y1;

    return 0;
}

/* code has ctor, cctor, assignment operator, dtor
0000000000000b50 W Y::operator=(Y const&)
0000000000000b1c W Y::Y(Y const&)
0000000000000ae4 W Y::Y()
0000000000000b1c W Y::Y(Y const&)
0000000000000ae4 W Y::Y()
0000000000000b00 W Y::~Y()
0000000000000b00 W Y::~Y()
*/

/* code only has ctor
0000000000000a5a W Y::Y()
0000000000000a5a W Y::Y()
0000000000000a76 W Y::~Y()
0000000000000a76 W Y::~Y()
*/

/* code only has cctor

*/

/* code when removing assignment operator
0000000000000af2 W Y::Y(Y const&)
0000000000000aba W Y::Y()
0000000000000af2 W Y::Y(Y const&)
0000000000000aba W Y::Y()
0000000000000ad6 W Y::~Y()
0000000000000ad6 W Y::~Y()
*/

/* code only has dtor

*/