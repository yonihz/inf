#include <iostream>

using namespace std;

#include "fraction.hpp"

static int GCD(int a, int b);

size_t Fraction::s_count = 0;

Fraction::Fraction(int numr, int denr)
    : m_numr(numr), m_denr(denr)
{
    if (!IsUndefined())
    {
        ReduceFrac();
    }
    
    ++s_count;
}

Fraction::~Fraction()
{
    --s_count;
}

Fraction::Fraction(const Fraction& other_)
    : m_numr(other_.m_numr), m_denr(other_.m_denr)
{
    if (!IsUndefined())
    {
        ReduceFrac();
    }

    ++s_count;
}

Fraction& Fraction::operator=(const Fraction& other_)
{
    m_numr = other_.m_numr;
    m_denr = other_.m_denr;

    if (!IsUndefined())
    {
        ReduceFrac();
    }

    return *this;
}    

bool Fraction::operator==(const Fraction& other_) const
{
    if (((Fraction)*this).IsUndefined() || ((Fraction)other_).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return false;
    }
    return ((m_numr * other_.m_denr) == (other_.m_numr * m_denr));
}

bool Fraction::operator==(int n) const
{
    if (((Fraction)*this).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return false;
    }

    return (((m_numr % m_denr) == 0) && (n == (m_numr / m_denr)));  
}

Fraction Fraction::operator+(const Fraction& other_) const
{
    Fraction res;

    if (((Fraction)*this).IsUndefined() || ((Fraction)other_).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return res;
    }

    res.SetValueNum((m_numr * other_.m_denr) + (other_.m_numr * m_denr));
    res.SetValueDen(m_denr * other_.m_denr); 
    res.ReduceFrac();

    return res;
}

Fraction Fraction::operator-(const Fraction& other_) const
{
    Fraction res;
    
    if (((Fraction)*this).IsUndefined() || ((Fraction)other_).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return res;
    }

    res.SetValueNum((m_numr * other_.m_denr) - (other_.m_numr * m_denr));
    res.SetValueDen(m_denr * other_.m_denr); 
    res.ReduceFrac();

    return res;
}

Fraction Fraction::operator+() const
{
    return (*this);
}

Fraction Fraction::operator-() const
{
    return Fraction(-m_numr, m_denr);
}

// prefix inc
Fraction& Fraction::operator++()
{
    this->m_numr += this->m_denr;
    return *this;
}

// postfix inc
Fraction Fraction::operator++(int)
{
    Fraction temp(*this);
    this->m_numr += this->m_denr;
    return temp;
}

// prefix dec
Fraction& Fraction::operator--()
{
    this->m_numr -= this->m_denr;
    return *this;
}

// postfix dec
Fraction Fraction::operator--(int)
{
    Fraction temp(*this);
    this->m_numr -= this->m_denr;
    return temp;
}

Fraction& Fraction::operator+=(const Fraction& other_)
{
    if (IsUndefined() || ((Fraction)other_).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return *this;
    }

    m_numr = (m_numr * other_.m_denr) + (other_.m_numr * m_denr);
    m_denr = m_denr * other_.m_denr; 
    ReduceFrac();

    return *this;
}

Fraction& Fraction::operator+=(int n)
{
    if (IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return *this;
    }

    m_numr += n * m_denr;
    ReduceFrac();

    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other_)
{
    if (IsUndefined() || ((Fraction)other_).IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return *this;
    }

    m_numr = (m_numr * other_.m_denr) - (other_.m_numr * m_denr);
    m_denr = m_denr * other_.m_denr; 
    ReduceFrac();

    return *this;
}

Fraction& Fraction::operator-=(int n)
{
    if (IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return *this;
    }

    m_numr -= n * m_denr;
    ReduceFrac();

    return *this;
}

bool Fraction::IsUndefined()
{
    return (m_denr == 0);
}

void Fraction::Print()
{
    cout << m_numr << "/" << m_denr << "\n";
}

int Fraction::GetValueNum()
{
    return m_numr;
}

int Fraction::GetValueDen()
{
    return m_denr;
}

void Fraction::SetValueNum(int n)
{
    m_numr = n;
}

void Fraction::SetValueDen(int n)
{
    m_denr = n;
}

void Fraction::ReduceFrac()
{
    int gcd = GCD(m_numr, m_denr);

    m_numr /= gcd;
    m_denr /= gcd;
}

static int GCD(int a, int b)
{
    int gcd = 0, mod = 0;

    while (a != 0)
    {
        mod = b % a;
        b = a;
        a = mod;
    }

    gcd = b;

    return gcd;
}