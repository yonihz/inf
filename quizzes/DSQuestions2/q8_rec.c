#include <stdio.h>
#include <stdlib.h>

int RecMulti(int x, int y);
unsigned int Increment(unsigned int x);
unsigned int RecIncrement(unsigned int x, unsigned int m);

int main()
{
    printf("RecMulti tests:\n");
    printf("8*7 = %d\n", RecMulti(8,7));
    printf("8*(-7) = %d\n", RecMulti(8,-7));
    printf("(-8)*7 = %d\n", RecMulti(-8,7));
    printf("0*7 = %d\n", RecMulti(0,7));
    printf("8*0 = %d\n", RecMulti(8,0));
    printf("9*1 = %d\n", RecMulti(9,1));
    printf("1*10 = %d\n", RecMulti(1,10));
    
    printf("\n");
    printf("RecInc tests:\n");
    printf("Increment 1: %u\n", Increment(1));
    printf("Increment 7: %u\n", Increment(7));
    printf("Increment 8: %u\n", Increment(8));
    printf("Increment 64: %u\n", Increment(64));
    printf("Increment 1023: %u\n", Increment(1023));
    printf("Increment 1000000: %u\n", Increment(1000000));


    return 0;
}

int RecMulti(int x, int y)
{
    if (0 == y)
    {
        return 0;
    }

    if (y < 0)
    {
        y = -y;
        x = -x;
    }

    return (x + RecMulti(x, (y - 1)));
}

unsigned int Increment(unsigned int x)
{
    return RecIncrement(x, 1);
}

unsigned int RecIncrement(unsigned int x, unsigned int m)
{
    x = x ^ m;

    if ((x & m) == 0)
    {
        x = RecIncrement(x, m << 1);
    }
    
    return x;
}