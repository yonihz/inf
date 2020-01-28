#include <iostream>

#include "bits_array.hpp"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

typedef unsigned long TEST_DWORD;

void REQUIRE(bool test, const char test_name[])
{
	(true == test) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

void Test1();

using namespace ilrd;

template<size_t N>
void PrintBitsArray(BitsArray<N> &ba, TEST_DWORD size);

int main()
{
    Test1();
}

void Test1()
{
    const size_t ba_size = 80;
    BitsArray<ba_size> ba1;
    BitsArray<ba_size> ba3;
    BitsArray<ba_size> ba4;

    ba1.SetBit(0, 1);
    ba1.SetBit(66, 1);

    REQUIRE(ba1.GetBit(0) == true, "ba1.GetBit(0) after ba1.SetBit(0, 1)");
    REQUIRE(ba1.GetBit(66) == true, "ba1.GetBit(66) after ba1.SetBit(66, 1)");
    REQUIRE(ba1[0] == true, "ba1[0] after ba1.SetBit(0, 1)");
    REQUIRE(ba1[66] == true, "ba1[66] after ba1.SetBit(66, 1)");

    ba1.SetBit(0, 0);
    ba1.SetBit(66, 0);

    REQUIRE(ba1.GetBit(0) == false, "ba1.GetBit(0) after ba1.SetBit(0, 0)");
    REQUIRE(ba1.GetBit(66) == false, "ba1.GetBit(66) after ba1.SetBit(66, 0)");

    for (size_t i = 0; i < ba_size; i=i+2)
    {
        ba1.SetBit(i, true);
    }

    for (size_t i = 1; i < ba_size; i=i+2)
    {
        ba4.SetBit(i, true);
    }

    BitsArray<80> ba2(ba1);
    ba3 = ba1;

    REQUIRE((ba2 == ba1) == true, "ba2 == ba1 after ba2(ba1)");
    REQUIRE((ba3 == ba1) == true, "ba3 == ba1 after ba3 = ba1");
    
    ba3.ToggleAll();
    REQUIRE((ba3 == ba4) == true, "ba4 == ba3");
    REQUIRE((ba3 != ba1) == true, "ba3 != ba1");

    ba1.ToggleOne(0);
    ba1.ToggleOne(65);
    REQUIRE(ba1.GetBit(0) == false, "ba1.GetBit(0) after ba1.ToggleOne(0)");
    REQUIRE(ba1.GetBit(65) == true, "ba1.GetBit(65) after ba1.ToggleOne(65)");

    ba1.ToggleOne(0);
    ba1.ToggleOne(65);
    REQUIRE(ba1.GetBit(0) == true, "ba1.GetBit(0) after ba1.ToggleOne(0)");
    REQUIRE(ba1.GetBit(65) == false, "ba1.GetBit(65) after ba1.ToggleOne(65)");

    ba2.SetAll(false);
    BitsArray<ba_size> ba5;
    REQUIRE((ba2 == ba5) == true, "ba2 == ba5 after ba2.SetAll(false)");

    for (size_t i = 0; i < ba_size; ++i)
    {
        ba5.SetBit(i, true);
    }

    ba2.SetAll(true);
    REQUIRE((ba2 == ba5) == true, "ba2 == ba5 after ba2.SetAll(true)");

    ba1.SetAll(true);
    ba2.SetAll(false);
    ba3.SetAll(true);
    ba1 |= ba2;
    REQUIRE((ba1 == ba3) == true, "ba1 == ba3 after ba1 |= ba2");

    ba1.SetAll(true);
    ba2.SetAll(false);
    ba3.SetAll(false);
    ba1 &= ba2;
    REQUIRE((ba1 == ba3) == true, "ba1 == ba3 after ba1 &= ba2");  

    ba1.SetAll(true);
    ba2.SetAll(true);
    ba3.SetAll(false);
    ba1 ^= ba2;
    REQUIRE((ba1 == ba3) == true, "ba1 == ba3 after ba1 ^= ba2");

    ba3.SetAll(true);
    ba1 ^= ba2;
    REQUIRE((ba1 == ba3) == true, "ba1 == ba3 after ba1 ^= ba2");

    ba1.SetAll(false);
    ba1.SetBit(0, 1);
    ba1.SetBit(1, 1);
    ba1.SetBit(3, 1);
    ba1.SetBit(66, 1);

    ba1[2] = true;
    REQUIRE(ba1[2] == true, "ba1[2] = true");
    ba1[2] = ba1[5];
    REQUIRE(ba1[2] == false, "ba1[2] = ba1[5]");

    REQUIRE((ba1.Count(true) == 4), "ba1.Count() == 4");  
    REQUIRE((ba1.Count(false) == ba_size - 4), "ba1.Count() == 76");  
}

template<size_t N>
void PrintBitsArray(BitsArray<N> &ba, TEST_DWORD size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << ba.GetBit(i);
    }

    std::cout << std::endl;
}