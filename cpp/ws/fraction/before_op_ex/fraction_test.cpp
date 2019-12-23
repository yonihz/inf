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

    cout << "Check if frac1(3/4) = frac2(6/8): " << frac1.IsEqual(frac2) << "\n";
    cout << "Check if frac1(3/4) = frac3(4/2): " << frac1.IsEqual(frac3) << "\n";
    cout << "Check if frac3(4/2) = frac4(2): " << frac3.IsEqual(frac4) << "\n";
    cout << "Check if frac4(2) = frac5(2/0): " << frac4.IsEqual(frac5) << "\n";

    frac5 = frac1;
    cout << "assign: frac5 = frac1, print frac5:\n";
    frac5.Print();

    cout << "AddToSelf: 3/4 + 7/12 = ";
    frac1.AddToSelf(frac6);
    frac1.Print();

    cout << "AddToSelf: 7/12 + (int)3 = ";
    frac6.AddToSelf(3);
    frac6.Print();

    cout << "SetValue frac6 to (5,7)" << endl;
    frac6.SetValueNum(5);
    frac6.SetValueDen(7);
    cout << "GetValueNum frac6 :" << frac6.GetValueNum() << endl;
    cout << "GetValueDen frac6 :" << frac6.GetValueDen() << endl;

}