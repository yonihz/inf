#ifndef ILRD_OL734_FRACTION_HPP
#define ILRD_OL734_FRACTION_HPP

#include <cstdlib>

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

    Fraction& operator++(); // prefix ++
    Fraction operator++(int); // postfix ++

    Fraction& operator--(); // prefix --
    Fraction operator--(int); // postfix --
  
    void AddToSelf(Fraction& f);
    void AddToSelf(int num);

    Fraction& operator+=(const Fraction& other_);
    Fraction& operator+=(int n);

    Fraction& operator-=(const Fraction& other_);
    Fraction& operator-=(int n);

    bool IsUndefined();
    void Print();

    int GetValueNum();
    int GetValueDen();
    void SetValueNum(int n);
    void SetValueDen(int n);
    static size_t s_count;

private:
    void ReduceFrac();
    int m_numr;
    int m_denr;
};

#endif