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

    cout << "Print frac1: 3/4: ";
    frac1.Print();
    cout << "Print frac2: 2: ";
    frac4.Print();

    cout << "Check if 3/4 = 6/8: " << frac1.IsEqual(frac2) << "\n";
    cout << "Check if 3/4 = 4/2: " << frac1.IsEqual(frac3) << "\n";
    cout << "Check if 4/2 = 2: " << frac3.IsEqual(frac4) << "\n";
    cout << "Check if 2 = 2/0: " << frac4.IsEqual(frac5) << "\n";

    frac5 = frac1;
    cout << "frac5 = frac1, print frac5:\n";
    frac5.Print();

    cout << "3/4 + 6/8 = ";
    frac1.AddToSelf(frac2);
    frac1.Print();
}