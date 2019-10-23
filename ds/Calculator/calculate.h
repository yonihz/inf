#ifndef _CALCULATE_H_
#define _CALCULATE_H_

/* Rev. 0.1 */ 
/* 17.10.19  16:00*/
enum status {ALLOC_ERR = -3, MATH_ERR, INVAL_INPUT, SUCCESS};

/*
    the function receives an expression as string and pointer to double to store the result 
    the function calculates the expression, and returns the status:
     0 : success
    -1 : synatax error
    -2 : math error
    -3 : system error
*/

int Calculate(const char *expr, double *result);

#endif /*_CALCULATE_H_*/
