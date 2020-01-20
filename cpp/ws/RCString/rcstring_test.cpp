#include <cstring>

#include "rcstring.hpp"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

void REQUIRE(bool test, const char test_name[])
{
	(true == test) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

using namespace ilrd;

int main()
{
    std::cout << "RCString s1 = \"string1\"" << std::endl;
    std::cout << "RCString s2 = \"string2\"" << std::endl;

    const char *str1 = "string1";
    RCString s1 = "string1";
    RCString s2 = "string2";

    std::cout << "op<< s1: " << s1 << std::endl;
    std::cout << "op<< s2: " << s2 << std::endl;

    REQUIRE(strcmp(s1.GetCStr(), (char*)str1) == 0, "s1.GetCStr()");
    REQUIRE(s1.Length() == 7, "s1.Length() == 7");

    REQUIRE((s1 < s2) == true, "(s1 < s2)");
    REQUIRE((s2 > s1) == true, "(s2 > s1)");

    REQUIRE(s1.IsShared() == false, "s1 is unique after s1 = \"string1\"");
    REQUIRE(s2.IsShared() == false, "s2 is unique after s2 = \"string2\"");

    std::cout << "RCString s3(s1)" << std::endl;
    RCString s3(s1);

    REQUIRE((s1 != s2) == true, "(s1 != s2)");
    REQUIRE((s1 == s3) == true, "(s1 == s3)");

    REQUIRE(s1.IsShared() == true, "s1 is not unique after RCString s3(s1)");
    REQUIRE(s3.IsShared() == true, "s3 is not unique after RCString s3(s1)");

    std::cout << "s2 = s1" << std::endl;
    s2 = s1;

    REQUIRE(s2[6] == '1', "s2[6] == 1");

    std::cout << "s1[6] = 3" << std::endl;
    s1[6] = '3';
    std::cout << "op<< s1: " << s1 << std::endl;

    REQUIRE(s1.IsShared() == false, "s1 is unique after s1[6] = 3");
    REQUIRE(s3.IsShared() == true, "s3 is not unique after s1[6] = 3");

    std::cout << "s2[6] = 4" << std::endl;
    s2[6] = '4';

    REQUIRE(s2.IsShared() == false, "s2 is unique after s2[6] = 4");
    REQUIRE(s3.IsShared() == false, "s3 is unique after s2[6] = 4");

}