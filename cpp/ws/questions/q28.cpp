#include <cstdio>

int i_notconst = 5;
const int i_const2 = 4;
const int i = 3;

int main()
{
    int* ip = (int*)&i;
    *ip = 5;

    printf("%d %d\n", i, *ip);
    return 0;
}