#include <stdlib.h>
#include <stdio.h>

#include "calc.h"

int main()
{
    char *str = "-145+0.5*8";
    int status = 0;
    double res = 0;

    printf("Expression: %s\n", str);
    status = Calculate(str, &res);

    switch (status)
    {
        case SYSTEM_ERR:
        {
            printf("System error\n");
            break;
        }
        case MATH_ERR:
        {
            printf("Math error\n");
            break;
        }
        case SYNTAX_ERR:
        {
            printf("Syntax error\n");
            break;
        }

        case SUCCESS:
        {
            printf("Result: %f\n", res);
            break;
        }
    }
    return (0);
}

/* strtod check
int main()
{
    char *str = "-145+0.5*8";
    double num = 0;
    char *end = str;
    while (*str)
    {
        end = str;
        num = strtod(str, &end);
        if (str == end)
        {
            printf("%c", *str);
            ++(str);
        }
        else
        {
            printf("%f", num);
            str = end;
        }
        printf("\n");
    }
    return (0);
}
*/