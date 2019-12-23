#include <iostream>

using namespace std;

#include "fraction.hpp"

static int GCD(int a, int b);

Fraction::Fraction(int numr, int denr)
    : m_numr(numr), m_denr(denr)
{
    if (!IsUndefined())
    {
        ReduceFrac();
    }
}

Fraction::~Fraction()
{
}

Fraction::Fraction(const Fraction& other_)
    : m_numr(other_.m_numr), m_denr(other_.m_denr)
{
    if (!IsUndefined())
    {
        ReduceFrac();
    }
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

bool Fraction::IsUndefined()
{
    return (m_denr == 0);
}

void Fraction::AddToSelf(Fraction& f)
{
    if (IsUndefined() || f.IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return;
    }

    m_numr = (m_numr * f.m_denr) + (f.m_numr * m_denr);
    m_denr = m_denr * f.m_denr; 
    ReduceFrac();
}

void Fraction::AddToSelf(int num)
{
    if (IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return;
    }

    m_numr += num * m_denr;
    ReduceFrac();
}

void Fraction::Print()
{
    cout << m_numr << "/" << m_denr << "\n";
}

bool Fraction::IsEqual(Fraction& f)
{
    if (IsUndefined() || f.IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return false;
    }

    return ((m_numr * f.m_denr) == (f.m_numr * m_denr)); 
}

bool Fraction::IsEqual(int num)
{
    if (IsUndefined())
    {
        cout << "Error: undefined number!\n";
        return false;
    }

    return (((m_numr % m_denr) == 0) && (num == (m_numr / m_denr)));  
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