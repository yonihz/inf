#ifndef ILRD_OL734_FRACTION_HPP
#define ILRD_OL734_FRACTION_HPP

#include <stdlib.h>

class Fraction {
public:
    explicit Fraction(int numr = 0, int denr = 1);
    
    ~Fraction();

    Fraction(const Fraction& other_);

    Fraction& operator=(const Fraction& other_);    

    bool IsUndefined();
    void AddToSelf(Fraction& f);
    void AddToSelf(int num);
    void Print();
    bool IsEqual(Fraction& f);
    bool IsEqual(int num);
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