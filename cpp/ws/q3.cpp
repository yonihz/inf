#include <stdio.h>

struct Counter
{
    void Inc();
    void Dec();

    int m_a;
    int m_b;                                                                                     
};

void Counter::Inc()
{
    ++this->m_a;
    this->m_b += 2;
    printf("Inc this: %lu\n", this);
}

void Counter::Dec()
{
    --this->m_a;
    this->m_b /= 2;
    printf("Dec this: %lu\n", this);
}

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

    printf("x2.Inc()\n");
    x2.Inc();
    printf("x2.m_a %d\n", x2.m_a);
    printf("x2.m_b %d\n", x2.m_b);

    printf("x2.Dec()\n");
    x2.Dec();
    printf("x2.m_a %d\n", x2.m_a);
    printf("x2.m_b %d\n", x2.m_b);

    return 0;
}