#include <iostream>

using namespace std;

#include "fraction.hpp"

int main()
{
    Fraction frac1(3, 4);
    Fraction frac2(6, 8);
    Fraction frac3(4, 2);
    Fraction frac4(2);
    Fraction frac5(2, 0);
    Fraction frac6(7, 12);

    cout << "Print frac1: 3/4: ";
    frac1.Print();
    cout << "Print frac2: 6/8: ";
    frac2.Print();
    cout << "Print frac3: 4/2: ";
    frac3.Print();
    cout << "Print frac4: 2: ";
    frac4.Print();
    cout << "Print frac5: 2/0: ";
    frac5.Print();

    cout << "Print -frac1:" << endl;
    (-frac1).Print();

    cout << "Print +frac1:" << endl;
    (+frac1).Print();

    cout << "Print frac1 before ++frac1:" << endl;
    frac1.Print();
    cout << "Print ++frac1:" << endl;
    (++frac1).Print();
    cout << "Print frac1 after ++frac1:" << endl;
    frac1.Print();

    cout << "Print frac1 before frac1++:" << endl;
    frac1.Print();
    cout << "Print frac1++:" << endl;
    (frac1++).Print();
    cout << "Print frac1 after frac1++:" << endl;
    frac1.Print();    

    cout << "Print frac1 before --frac1:" << endl;
    frac1.Print();
    cout << "Print --frac1:" << endl;
    (--frac1).Print();
    cout << "Print frac1 after --frac1:" << endl;
    frac1.Print();        

    cout << "Print frac1 before frac1--:" << endl;
    frac1.Print();
    cout << "Print frac1--:" << endl;
    (frac1--).Print(); 
    cout << "Print frac1 after frac1--:" << endl;
    frac1.Print();       
}