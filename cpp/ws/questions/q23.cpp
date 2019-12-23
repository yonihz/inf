#include <iostream>
#include <stdlib.h>

class StaticCounter
{
private:
    static size_t s_cntr;

public:
    StaticCounter();
    size_t GetId();

private:
    size_t m_id;
};

size_t StaticCounter::s_cntr = 0;

StaticCounter::StaticCounter()
    : m_id(++s_cntr)
{
}

size_t StaticCounter::GetId() {
    std::cout << m_id << std::endl;
    return m_id;
}

int main()
{
    StaticCounter x1;
    StaticCounter x2;

    x1.GetId();
    x2.GetId();

    return 0;
}