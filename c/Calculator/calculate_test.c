/****************************************************************
* 																*
* FILE NAME: calculate_test.c		            			   	*
* 																*
* PURPOSE: Testing Calculate functions      		            *
*                                                               *
* DATE: 01.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

/* compile command:
gd ../stack.c calculate.c calculate_test.c -I../include -lm
*/

#include <stdlib.h>
#include <stdio.h>

#include "calculate.h"

void TestCalc(char *str);

int main()
{
    TestCalc("3e1000+0.5*8");
    TestCalc("5+0.5*2^4");
    TestCalc("(1.5+0.5)*2^4");
    TestCalc("((1+1)))");
    TestCalc("((1+1)");
    TestCalc("((1.5+0.5)*2^(2/0*0))");    
    TestCalc("((1.5+0.5)*2^(2*2))^");

    TestCalc("7+8");
    TestCalc("8+8*3+-2^5");
    TestCalc("2/0");
    TestCalc("8++8*((3-2)*5)");
    TestCalc("3-2)*5");    
    TestCalc("(3-2)*5+ 5*(4+4+4");     

    return (0);
}

void TestCalc(char *str)
{
    int status = 0;
    double res = 0;

    printf("\nExpression: %s\n", str);
    status = Calculate(str, &res);

    switch (status)
    {
        case ALLOC_ERR:
        {
            printf("System error\n");
            break;
        }
        case MATH_ERR:
        {
            printf("Math error\n");
            break;
        }
        case INVAL_INPUT:
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
}