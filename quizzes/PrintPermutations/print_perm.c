#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintPerm(const char *str);
void RecPrintPerm(char *str, size_t left, size_t right);
void Swap(char *a, char *b);

int main()
{
    char str[5] = "abc";

    PrintPerm(str);

    return (0);
}

void PrintPerm(const char *str)
{
    size_t len = strlen(str);
    char *buf = malloc(len + 1);
    strcpy(buf, str);
    RecPrintPerm(buf, 0, len);
}

void RecPrintPerm(char *str, size_t left, size_t right)
{
    size_t i = 0;

    if (left == right)
    {
        printf("%s\n", str);
    }
    else
    {
        for (i = 1; i <= right; i++)
        {
            Swap((str + left), (str + i));
            RecPrintPerm(str, left + 1, right);
            Swap((str + left), (str + i));
        }
    }
}

void Swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;    
}