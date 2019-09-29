#include <stdio.h>

/* disable ASLR: echo 0 | sudo tee /proc/sys/kernel/randomize_va_space */
/* enable ASLR echo 2 | sudo tee /proc/sys/kernel/randomize_va_space */

FILE *fp;

int main()
{
    int j = 200;
    int* p = &j;

    printf("p2: &j %p\n", (void*)p);
    fp = fopen("test.txt","r");
    fscanf(fp,"%p", (void**)&p);
    printf("p2: &j %p\n", (void*)p);
    printf("p points to %d\n", *p);

    return(0);
}

/* 
ASLR disabled:
p1: &j 0x7fffffffdb6c
p2: &j 0x7fffffffdb6c
p2: &j 0x7fffffffdb6c
p points to 200

ASLR enabled:
p1: &j 0x7ffc97eb85fc
p2: &j 0x7ffd27d55e7c
p2: &j 0x7ffc97eb85fc
Segmentation fault (core dumped)
*/