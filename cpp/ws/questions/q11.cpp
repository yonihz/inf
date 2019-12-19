#include <stdio.h>

int main()
{
    bool b1 = true;
    bool b2;
    int i = b1;

    printf("%d\n", b1);
    printf("%d\n", b2);

    i = 7;
    b2 = i;
    printf("%d\n", b2);
}