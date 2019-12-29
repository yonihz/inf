#include <iostream>

using namespace std;

class X;



class X
{
public:
    X(int a) : m_a(a) { }

    bool operator==(const X& o_) const { return m_a == o_.m_a; }

    int GetValue() const { return m_a; }

private:
    int m_a;
};

int operator+(const X& x1_, const X& x2_)
{
    return (x1_.GetValue() + x2_.GetValue());
}

// X operator+(const X& x1_, const X& x2_)
// {
//     return X(x1_.GetValue() + x2_.GetValue());
// }

X operator-(const X& x1_, const X& x2_)
{
    return X(x1_.GetValue() - x2_.GetValue());
}

int main()
{
    X x1(3);
    X x2(6);

    //cout << "x1 + x2 : " << (x1+x2).GetValue() << endl;
    cout << "x1 + x2 : " << (x1+x2) << endl;
    cout << "x1 == x2 : " << int(x1 == x2) << endl;
    cout << "x1 - x2 : " << (x1-x2).GetValue() << endl;
    
}
