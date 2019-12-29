#include <iostream>

int main()
{
    int i = 78;
    double d = 3.14;

    std::cout << "hello" << i << std::endl;
    std::cin >> i;
    std::cerr << "wrong?" << i << " " << d;
}