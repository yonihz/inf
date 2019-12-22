#include <iostream>

using namespace std;

#include "fraction.hpp"

Fraction::Fraction(int numr, int denr)
    : m_numr(numr), m_denr(denr)
{
}

Fraction::~Fraction()
{
}

Fraction::Fraction(const Fraction& other_)
    : m_numr(other_.m_numr), m_denr(other_.m_denr)
{
}

Fraction& Fraction::operator=(const Fraction& other_)
{
    m_numr = other_.m_numr;
    m_denr = other_.m_denr;

    return *this;
}    

bool Fraction::IsUndefined()
{
    return (m_denr == 0);
}

void Fraction::AddToSelf(Fraction& f)
{
    if (f.IsUndefined())
    {
        cout << "Error: undefined number!\n"; 
    }

    m_numr = (m_numr * f.m_denr) + (f.m_numr * m_denr);
    m_denr = m_denr * f.m_denr; 
}

void Fraction::AddToSelf(int num)
{
    m_numr += num * m_denr;
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
    }

    return ((m_numr * f.m_denr) == (f.m_numr * m_denr)); 
}

bool Fraction::IsEqual(int num)
{
    if (IsUndefined())
    {
        cout << "Error: undefined number!\n"; 
    }

    return (((m_numr % m_denr) == 0) && (num == (m_numr / m_denr)));  
}

int Fraction::GetNumerator()
{
    return m_numr;
}

int Fraction::GetDenominator()
{
    return m_denr;
}

void Fraction::SetNumerator(int n)
{
    m_numr = n;
}

void Fraction::SetDenominator(int n)
{
    m_denr = n;
}

void Fraction::ReduceFrac()
{
    
}