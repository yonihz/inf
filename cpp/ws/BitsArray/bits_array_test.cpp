#include <iostream>

#include "bits_array.hpp"

void Test1();
void Test2();

using namespace ilrd;

template<size_t N>
void PrintBitsArray(BitsArray<N> &ba, DWORD size);

int main()
{
    // Test1();
    Test2();
}

void Test1()
{
    std::cout << "BitsArray<80> ba1" << std::endl;
    BitsArray<80> ba1;
    BitsArray<80> ba3;

    // std::cout << ba1[1] << std::endl;
    std::cout << "----- test: SetBit() to 1" << std::endl;
    std::cout << "ba1.SetBit(1, 1)" << std::endl; ba1.SetBit(1, 1);
    std::cout << "ba1.SetBit(3, 1)" << std::endl; ba1.SetBit(3, 1);
    std::cout << "ba1.SetBit(5, 1)" << std::endl; ba1.SetBit(5, 1);
    std::cout << "ba1.SetBit(65, 1)" << std::endl; ba1.SetBit(65, 1);
    PrintBitsArray(ba1, 80);

    std::cout << "ba1.GetBit(1) " << ba1.GetBit(1) << std::endl;
    std::cout << "ba1.GetBit(2) " << ba1.GetBit(2) << std::endl;
    std::cout << "ba1.GetBit(3) " << ba1.GetBit(3) << std::endl;
    std::cout << "ba1.GetBit(4) " << ba1.GetBit(4) << std::endl;
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "ba1.GetBit(64) " << ba1.GetBit(64) << std::endl;
    std::cout << "ba1.GetBit(65) " << ba1.GetBit(65) << std::endl;
    std::cout << "ba1[65] " << ba1[65] << std::endl;

    std::cout << "----- test: CCtor" << std::endl;
    std::cout << "BitsArray<80> ba2(ba1)" << std::endl;
    BitsArray<80> ba2(ba1);
    PrintBitsArray(ba2, 80);

    std::cout << "----- test: op=" << std::endl;
    std::cout << "ba3 = ba1" << std::endl;
    ba3 = ba1;
    PrintBitsArray(ba3, 80);

    std::cout << "----- test: SetBit() to 0" << std::endl;
    std::cout << "ba1.SetBit(3, 0)" << std::endl; ba1.SetBit(3, 0);
    std::cout << "ba1.SetBit(65, 0)" << std::endl; ba1.SetBit(65, 0);
    PrintBitsArray(ba1, 80);
    std::cout << "ba1.GetBit(3) " << ba1.GetBit(3) << std::endl;
    std::cout << "ba1.GetBit(65) " << ba1.GetBit(65) << std::endl;
    std::cout << "ba1[65] " << ba1[65] << std::endl;

    std::cout << "----- test: ToggleOne()" << std::endl;
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "ba1.GetBit(65) " << ba1.GetBit(65) << std::endl;
    std::cout << "ba1.ToggleOne(5)" << std::endl; ba1.ToggleOne(5);
    std::cout << "ba1.ToggleOne(65)" << std::endl; ba1.ToggleOne(65);
    PrintBitsArray(ba1, 80);
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "ba1.GetBit(65) " << ba1.GetBit(65) << std::endl;

    std::cout << "----- test: ToggleAll()" << std::endl;
    std::cout << "ba1.GetBit(1) " << ba1.GetBit(1) << std::endl;
    std::cout << "ba1.GetBit(2) " << ba1.GetBit(2) << std::endl;
    std::cout << "ba1.GetBit(3) " << ba1.GetBit(3) << std::endl;
    std::cout << "ba1.GetBit(4) " << ba1.GetBit(4) << std::endl;
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "ba1.ToggleAll()" << std::endl; ba1.ToggleAll();
    PrintBitsArray(ba1, 80);
    std::cout << "ba1.GetBit(1) " << ba1.GetBit(1) << std::endl;
    std::cout << "ba1.GetBit(2) " << ba1.GetBit(2) << std::endl;
    std::cout << "ba1.GetBit(3) " << ba1.GetBit(3) << std::endl;
    std::cout << "ba1.GetBit(4) " << ba1.GetBit(4) << std::endl;
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "----- test: op[]" << std::endl;  
}

void Test2()
{
    std::cout << "BitsArray<80> ba1, ba2" << std::endl;
    BitsArray<80> ba1;
    BitsArray<80> ba2;
    PrintBitsArray(ba1, 80);
    PrintBitsArray(ba2, 80);

    std::cout << "ba1.SetBit(1, 1)" << std::endl; ba1.SetBit(1, 1);
    std::cout << "ba1.SetBit(3, 1)" << std::endl; ba1.SetBit(3, 1);
    std::cout << "ba1.SetBit(5, 1)" << std::endl; ba1.SetBit(5, 1);
    std::cout << "ba1.SetBit(65, 1)" << std::endl; ba1.SetBit(65, 1);
    PrintBitsArray(ba1, 80);

    std::cout << "ba1.GetBit(1) " << ba1.GetBit(1) << std::endl;
    std::cout << "ba1.GetBit(2) " << ba1.GetBit(2) << std::endl;
    std::cout << "ba1.GetBit(3) " << ba1.GetBit(3) << std::endl;
    std::cout << "ba1.GetBit(4) " << ba1.GetBit(4) << std::endl;
    std::cout << "ba1.GetBit(5) " << ba1.GetBit(5) << std::endl;
    std::cout << "ba1.GetBit(64) " << ba1.GetBit(64) << std::endl;
    std::cout << "ba1.GetBit(65) " << ba1.GetBit(65) << std::endl;

    std::cout << "ba2 == ba1 " << (ba2 == ba1) << std::endl;
    std::cout << "ba2 != ba1 " << (ba2 != ba1) << std::endl;
    std::cout << "----- test: ba2 =| ba1" << std::endl;
    ba2 |= ba1;
    PrintBitsArray(ba2, 80);

    std::cout << "ba2.GetBit(1) " << ba2.GetBit(1) << std::endl;
    std::cout << "ba2.GetBit(2) " << ba2.GetBit(2) << std::endl;
    std::cout << "ba2.GetBit(3) " << ba2.GetBit(3) << std::endl;
    std::cout << "ba2.GetBit(4) " << ba2.GetBit(4) << std::endl;
    std::cout << "ba2.GetBit(5) " << ba2.GetBit(5) << std::endl;
    std::cout << "ba2.GetBit(64) " << ba2.GetBit(64) << std::endl;
    std::cout << "ba2.GetBit(65) " << ba2.GetBit(65) << std::endl;

    std::cout << "ba2 == ba1 " << (ba2 == ba1) << std::endl; 
    std::cout << "ba2 != ba1 " << (ba2 != ba1) << std::endl;

    std::cout << "----- test: ba2.SetAll(true)" << std::endl;
    ba2.SetAll(true);
    PrintBitsArray(ba2, 80);
    std::cout << "----- test: ba2.SetAll(false)" << std::endl;
    ba2.SetAll(false);
    PrintBitsArray(ba2, 80);
}

template<size_t N>
void PrintBitsArray(BitsArray<N> &ba, DWORD size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << ba.GetBit(i);
    }

    std::cout << std::endl;
}