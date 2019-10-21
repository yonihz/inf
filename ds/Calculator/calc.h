#ifndef _CALC_H_
#define _CALC_H_

/* Rev. 0.1 */ 
/* 17.10.19  16:00*/

enum status {SYSTEM_ERR = -3, MATH_ERR, SYNTAX_ERR, SUCCESS};

/*
    the function receives an expression as string and pointer to double to store the result 
    the function calculates the expression, and returns the status:
     0 : success
    -1 : synatax error
    -2 : math error
    -3 : system error
*/

int Calculate(const char *expr, double *result);

#endif /* _CALC_H_ */
