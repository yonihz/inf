#include <stdio.h>

struct Counter
{
    void Inc();
    void Inc(unsigned int delta);    
    void Dec();
//    void Inc2();

    int m_a;
    int m_b;                                                                                     
};

void Counter::Inc()
{
    ++m_a;
    m_b += 2;
}

void Counter::Inc(unsigned int delta)
{
    m_a += delta;
    m_b += 2*delta;
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

// void Counter::Inc2()
// {
//     ++m_a;
//     m_b += 2;
// }

// typedef struct Counter Counter;

int main()
{
    Counter x1;
    Counter x2;

    printf("sizeof(Counter) %lu\n", sizeof(Counter));

    x1.m_a = 7;
    printf("x1.m_a %d\n", x1.m_a);
    printf("x1.m_b %d\n", x1.m_b);

    x2.m_a = 0;
    x2.m_b = 16;
    printf("x2.m_a %d\n", x2.m_a);
    printf("x2.m_b %d\n", x2.m_b);

    printf("x1.Inc()\n");
    x1.Inc();
    printf("x1.m_a %d\n", x1.m_a);
    printf("x1.m_b %d\n", x1.m_b);
    
    printf("x1.Inc()\n");
    x1.Inc();
    printf("x1.m_a %d\n", x1.m_a);
    printf("x1.m_b %d\n", x1.m_b);

    printf("x2.Dec()\n");
    x2.Dec();
    printf("x2.m_a %d\n", x2.m_a);
    printf("x2.m_b %d\n", x2.m_b);

    printf("x1.Dec()\n");
    x1.Inc(5);
    printf("x1.m_a %d\n", x1.m_a);
    printf("x1.m_b %d\n", x1.m_b);

    return 0;
}