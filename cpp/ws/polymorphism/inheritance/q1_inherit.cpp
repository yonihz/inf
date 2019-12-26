#include <iostream>

class Base
{
public:
    Base(int a_ = 8) : m_a(a_) {std::cout << "B::Ctor" << std::endl; }
    virtual ~Base(){ std::cout << "B::Dtor" << std::endl; }

    virtual void Print1() const { std::cout << "B::Print1 B::m_a - " << m_a << std::endl; }

}