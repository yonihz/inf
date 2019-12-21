#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 5

int IsCharPresent(char *arr, size_t size, char c);

int main()
{
    char str[5] = "abcde";
    char c = 0;

    c = 'a';
    printf("Is char %c present in %s: %d\n", c, str, IsCharPresent(str, ARR_SIZE, c));

    c = 'd';
    printf("Is char %c present in %s: %d\n", c, str, IsCharPresent(str, ARR_SIZE, c));

    c = 'f';
    printf("Is char %c present in %s: %d\n", c, str, IsCharPresent(str, ARR_SIZE, c));

    return 0;
}

int IsCharPresent(char *arr, size_t size, char c)
{
    size_t i = 0;

    while (i < size && arr[i] != c)
    {
        ++i;
    }

    return !(i == size);
}

