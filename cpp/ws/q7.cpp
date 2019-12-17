#include <stdio.h>

int main()
{
    int i = 8;
    int& ip = i;
    char c = 48;
    char& cp = c;
    ip = 9;
    printf("%d\n", i);
}