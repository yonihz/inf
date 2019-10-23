#include <stdio.h>

unsigned int ItrFib(unsigned int n);
unsigned int RecFib(unsigned int n);
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

unsigned int ItrFib(unsigned int n)
{
    unsigned int prev_prev = 0, prev = 1, curr = 1;
    unsigned int i = 0;

    curr = n;
    for (i = 1; i < n; i++)
    {
        curr = prev + prev_prev;
        prev_prev = prev;
        prev = curr;
    }

    return curr;
}

unsigned int RecFib(unsigned int n)
{
    if (n <= 1)
    {
        return n;
    }

    return (RecFib(n-1) + RecFib(n-2));
}

void TestFib(unsigned int n)
{
    printf("Test Fibonacci with n=%u\n", n);
    printf("Iterative: %u\n", ItrFib(n));
    printf("Recursive: %u\n\n", RecFib(n));   
}