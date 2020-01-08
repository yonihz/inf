#include "verify.hpp"
#include "shared_ptr.hpp"

using namespace ilrd;

class X
{
public:
    X() : m_1(1), m_2(2) {}
    int m_1;
    int m_2;
};

class Y : public X
{
public:
    Y() : m_3(3) {}
    int m_3;
};

class Z
{
public:
    Z() : m_1(1), m_2(2) {}
    int m_1;
    int m_2;
};

int main()
{
    int *int_ptr1 = new int(4);
    int *int_ptr2 = new int(5);
    X *x_ptr = new X;

    SharedPtr<int> sp1(int_ptr1);
    REQUIRE(sp1.UseCount(), 1ul, "sp1 count = 1");
    SharedPtr<int> sp2(int_ptr2);
    REQUIRE(sp2.UseCount(), 1ul, "sp2 count = 1");
    SharedPtr<X> sp3(x_ptr);
    REQUIRE(sp3.UseCount(), 1ul, "sp3 count = 1");
    SharedPtr<X> sp4(sp3);
    REQUIRE(sp4.UseCount(), 2ul, "sp3 count = 2");
    REQUIRE(sp4.UseCount(), 2ul, "sp4 count = 2");
    
    std::cout << "sp1 = sp2" << std::endl;
    sp2 = sp1;
    REQUIRE(sp1.UseCount(), 2ul, "sp1 count = 2");
    REQUIRE(sp2.UseCount(), 2ul, "sp2 count = 2");

    REQUIRE(*sp1, 4, "*sp1 = 4");
    REQUIRE(sp3->m_1, 1, "sp3->m_1 = 1");

    SharedPtr<Y> y_sp(new Y);
    REQUIRE(y_sp.UseCount(), 1ul, "y_sp count = 1");
    SharedPtr<X> x_sp(new X);
    REQUIRE(x_sp.UseCount(), 1ul, "x_sp count = 1");
    SharedPtr<Z> z_sp(new Z);
    REQUIRE(z_sp.UseCount(), 1ul, "z_sp count = 1");

    std::cout << "x_sp1 = y_sp2" << std::endl;
    x_sp = y_sp;
    // x_sp = z_sp;
    REQUIRE(x_sp.UseCount(), 2ul, "x_sp count = 2");
    REQUIRE(y_sp.UseCount(), 2ul, "y_sp count = 2");
}