class X
{
public:
    X(double d_):m_a(d_){}
    virtual ~X(){}

private:
    double m_a;
};

class Y: public X
{
public:
    Y(double d_, int i_): X(d_), m_b(i_){}

private:
    int m_b;
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X& x1 = y1;
    X& x2 = y2;

// (gdb) p x1
// $1 = (X &) @0x7fffffffdc30: {_vptr.X = 0x555555755d58 <vtable for Y+16>, m_a = 0}
// (gdb) p x2
// $2 = (X &) @0x7fffffffdc50: {_vptr.X = 0x555555755d58 <vtable for Y+16>, m_a = 14.199999999999999}

    x1 = x2;
    y3 = y4;

// (gdb) p x1
// $1 = (X &) @0x7fffffffdc30: {_vptr.X = 0x555555755d58 <vtable for Y+16>, m_a = 14.199999999999999}
// (gdb) p y1
// $2 = {<X> = {_vptr.X = 0x555555755d58 <vtable for Y+16>, m_a = 14.199999999999999}, m_b = 0}
// (gdb) p y3
// $3 = {<X> = {_vptr.X = 0x555555755d58 <vtable for Y+16>, m_a = 14.199999999999999}, m_b = 5}

    return 0;
}