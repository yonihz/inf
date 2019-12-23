#ifndef ILRD_OL734_FRACTION_HPP
#define ILRD_OL734_FRACTION_HPP

#include <stdlib.h>

class Fraction {
public:
    explicit Fraction(int numr = 0, int denr = 1);
    
    ~Fraction();

    Fraction(const Fraction& other_);

    Fraction& operator=(const Fraction& other_);

    bool operator==(const Fraction& other_) const;
    bool operator==(int n) const;

    Fraction operator+(const Fraction& other_) const;
    Fraction operator-(const Fraction& other_) const;

    Fraction operator+() const; // unary +
    Fraction operator-() const; // unary -

    Fraction operator++(); // prefix ++
    Fraction operator++(int); // postfix ++

    Fraction operator--(); // prefix --
    Fraction operator--(int); // postfix --
  
    bool IsUndefined();
    void AddToSelf(Fraction& f);
    void AddToSelf(int num);
    void Print();

    int GetValueNum();
    int GetValueDen();
    void SetValueNum(int n);
    void SetValueDen(int n);

private:
    void ReduceFrac();
    int m_numr;
    int m_denr;
};

#endif