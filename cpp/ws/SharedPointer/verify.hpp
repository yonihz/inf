#include <iostream>	/* cout */
#include <cstring>	/* strcmp */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

namespace ilrd
{

template <class T1, class T2>
void REQUIRE(T1 test, T2 expected, const char test_name[])
{
	(test == expected) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

template<>
void REQUIRE(void* test, void* expected, const char test_name[])
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

} // namespace ilrd