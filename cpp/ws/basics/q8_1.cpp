#include <stdio.h>

struct Counter
{
    Counter *Inc(); 
    Counter *Dec();

    int m_a;
    int m_b;                                                                                     
};

Counter *Counter::Inc()
{
    ++m_a;
    m_b += 2;

    return this;
}

Counter *Counter::Dec()
{
    --m_a;
    m_b /= 2;

    return this;
}

// typedef struct Counter Counter;

int main()
{
    Counter x1;

    x1.m_a = 7;
    x1.Inc()->Inc()->Inc();

    printf("x1.m_a %d\n", x1.m_a);

    return 0;
}