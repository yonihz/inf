#include <iostream>

template<typename T>
void foo(T t)
{
    std::cout << t << " Generic foo\n";
}

template<>
void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

// void foo(int t)
// {
//     std::cout << t << " Specialized foo (for int param)\n";
// }

int main()
{
    foo(5);
    foo<int>(5);

    return 0;
}