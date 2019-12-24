#include <iostream>

#include "fraction.hpp"

using namespace ilrd;

int main()
{
    Fraction frac1(3, 4);
    Fraction frac2(6, 8);
    Fraction frac3(4, 2);
    Fraction frac4(2);
    Fraction frac5(2, 0);
    Fraction frac6(7, 12);
    Fraction frac7(7, 12);

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;
    
    std::cout << "Print frac1: 3/4: ";
    frac1.Print();
    std::cout << "Print frac2: 6/8: ";
    frac2.Print();
    std::cout << "Print frac3: 4/2: ";
    frac3.Print();
    std::cout << "Print frac4: 2: ";
    frac4.Print();
    std::cout << "Print frac5: 2/0: ";
    frac5.Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;
    
    std::cout << "Print -frac1:" << std::endl;
    (-frac1).Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "Print +frac1:" << std::endl;
    (+frac1).Print();
    std::cout << std::endl;

    std::cout << "Print frac1 before ++frac1:" << std::endl;
    frac1.Print();
    std::cout << "Print ++frac1:" << std::endl;
    (++frac1).Print();
    std::cout << "Print frac1 after ++frac1:" << std::endl;
    frac1.Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "Print frac1 before frac1++:" << std::endl;
    frac1.Print();
    std::cout << "Print frac1++:" << std::endl;
    (frac1++).Print();
    std::cout << "Print frac1 after frac1++:" << std::endl;
    frac1.Print();
    std::cout << std::endl; 

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "Print frac1 before --frac1:" << std::endl;
    frac1.Print();
    std::cout << "Print --frac1:" << std::endl;
    (--frac1).Print();
    std::cout << "Print frac1 after --frac1:" << std::endl;
    frac1.Print();
    std::cout << std::endl;        

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "Print frac1 before frac1--:" << std::endl;
    frac1.Print();
    std::cout << "Print frac1--:" << std::endl;
    (frac1--).Print(); 
    std::cout << "Print frac1 after frac1--:" << std::endl;
    frac1.Print();
    std::cout << std::endl;
    
    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "frac1 = ";
    frac1.Print();
    std::cout << "frac6 = ";
    frac6.Print();
    std::cout << "frac7 = ";
    frac7.Print();
    std::cout << "frac1 == frac6: " << (frac1 == frac6) << std::endl;
    std::cout << "frac6 == frac7: " << (frac6 == frac7) << std::endl;
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "frac1 = ";
    frac1.Print();
    std::cout << "frac6 = ";
    frac6.Print();
    std::cout << "+frac1 + -(++frac6): ";
    (+frac1 + -(++frac6)).Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "frac1 = ";
    frac1.Print();
    std::cout << "frac6 = ";
    frac6.Print();
    std::cout << "(frac1++) - +(frac6--): ";
    ((frac1++) - +(frac6--)).Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "frac1 = ";
    frac1.Print();
    std::cout << "frac6 = ";
    frac6.Print();
    std::cout << "frac1 += frac6, frac1 = ";
    frac1 += frac6;
    frac1.Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;

    std::cout << "frac1 = ";
    frac1.Print();
    std::cout << "frac6 = ";
    frac6.Print();
    std::cout << "frac1 -= frac6, frac1 = ";
    frac1 -= frac6;
    frac1.Print();
    std::cout << std::endl;

    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;
    {
        Fraction frac8(1, 6);
        std::cout << "Count Fractions (8) : " << Fraction::s_count << std::endl;
    }
    std::cout << "Count Fractions (7) : " << Fraction::s_count << std::endl;
    
    std::cout << "frac1: " << frac1 << "frac6: " << frac6 << std::endl;
    std::cout << "HALF: " << Fraction::HALF << std::endl;
    std::cout << "ONE: " << Fraction::ONE << std::endl;
    std::cout << "ZERO: " << Fraction::ZERO << std::endl;
}