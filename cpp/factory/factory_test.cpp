#include <iostream>

#include "factory.hpp"

using namespace ilrd;

class Base1
{
public:
    Base1() : m_i(0)
    {
        std::cout << "base1 ctor" << std::endl;
    }

    int m_i;
};

Base1 *CreateBase1()
{
    std::cout << "base1 create" << std::endl;
    Base1* ptr_base1 = new Base1();
    return ptr_base1;
}

class Base2
{
public:
    Base2(int i) : m_i(i)
    {
        std::cout << "base2 ctor" << std::endl;
    }

    int m_i;
};

Base2 *CreateBase2(int i)
{
    std::cout << "base2 create" << std::endl;
    Base2* ptr_base2 = new Base2(i);
    return ptr_base2;
}

int main()
{
    Factory <Base1 *, std::string, void, Base1 *(*)(void)> factory1;
    factory1.Add("base1", CreateBase1);
    factory1.Create("base1");

    Factory <Base2 *, std::string, int, Base2 *(*)(int)> factory2;
    factory2.Add("base2", CreateBase2);
    factory2.Create("base2", 10);
}


