#include <stdio.h>
#include <stdlib.h>

struct Counter
{
    void Inc();  
    void Dec();

    int m_a;
    int m_b;                                                                                     
};

void Counter::Inc()
{
    ++m_a;
    m_b += 2;
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

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
    Counter x2;

    float *f = new float(12.6);
    delete f;

    f = NULL;
    delete f;

    f = new float[15];
    delete[] f;

    Counter *c1 = new Counter;
    
    X *x1 = new X;
    Y *y1 = new Y;
    X *x3 = (X*)malloc(sizeof(X));
    X *x4 = new X;

    delete x3;
    free(x4);
    delete y1;
    delete c1;
    delete x1;

    X* xp = new X[10];
    delete[] xp;

    return 0;
}
