#include <iostream>	/* cout */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

namespace ilrd
{

void REQUIRE(bool test, const char test_name[])
{
	(true == test) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

} // namespace ilrd