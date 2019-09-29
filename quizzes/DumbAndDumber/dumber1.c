#include <stdio.h>

FILE *fp;

int main()
{
    int j = 100;
    int* p = &j;

    fp = fopen("test.txt","w");
    printf("p1: &j %p\n", (void*)p);
    fprintf(fp, "%p\n", (void*)p);

    return(0);
}