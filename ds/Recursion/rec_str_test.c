#include <stdio.h>

#include "rec_str.h"

void TestFib(unsigned int n);

int main()
{
    TestFib(0);
    TestFib(1);
    TestFib(2);
    TestFib(3);
    TestFib(4);
    TestFib(5);
    TestFib(6);

    return (0);
}

void TestFib(unsigned int n)
{
    printf("Test Fibonacci with n=%u\n", n);
    printf("Iterative: %u\n", ItrFib(n));
    printf("Recursive: %u\n\n", RecFib(n));   
}