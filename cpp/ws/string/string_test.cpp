#include <iostream>	/* cout */
#include <cstring>	/* strcmp */

#include "string.hpp"

#define UNUSED(x) (void)(x)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

using namespace ilrd;

// Verify functions
void VerifyInt(int test, int expected, const char test_name[]);
void VerifySizet(size_t test,size_t expected, const char test_name[]);
void VerifyVoidptr(void* test, void* expected, const char test_name[]);
void VerifyChar(char test[], char expected[], const char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, const char test_name[]);

// API test funtions
void TestBasic();

int main()
{
    TestBasic();

    return 0;
}

void TestBasic()
{
    char s1[] = "abcd";
    char s2[] = "abce";
    char s3[] = "abcd";
    char s4[] = "dsfdsfdsffds";

    String str1(s1);
    String str2(s2);
    String str3(s3);
    String str4("Hello");
    String str5(str1);
    String str6(s4);

    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;
    std::cout << "str4(\"Hello\"): " << str4 << std::endl;
    std::cout << "str5(str1): " << str5 << std::endl;

    VerifySizet(str1.Length(), strlen(s1), "str1.Length()");
    VerifyInt(str1 == str3, 1, "str1 == str3");
    VerifyInt(str1 == str5, 1, "str1 == str5");
    VerifyInt(str1 < str2, 1, "str1 < str2");
    VerifyInt(str2 > str1, 1, "str2 > str1");
    VerifyInt("abce" > str1, 1, "\"abce\" > str1");
    VerifyInt( str1 < "abce", 1, "str1 < \"abce\"");
}

void VerifyInt(int test, int expected, const char test_name[])
{
	(test == expected) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

void VerifySizet(size_t test,size_t expected, const char test_name[])
{
	(test == expected) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

void VerifyVoidptr(void* test, void* expected, const char test_name[])
{
	if (NULL == expected)
	{
		(test == NULL) ?
	    std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	    std::cout << RED << "TEST FAIL: " << test_name << std::endl;
        std::cout << RESET;
		return;
	}

	(*(int*)test == *(int*)expected) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

void VerifyChar(char test[], char expected[], const char test_name[])
{
	(!strcmp(test, expected)) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

void VerifyStrncmp(char test[], char expected[], size_t n, const char test_name[])
{
	(!strncmp(test, expected, n)) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}