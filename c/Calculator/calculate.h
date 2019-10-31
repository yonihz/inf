#ifndef _CALCULATE_H_
#define _CALCULATE_H_

/* Rev. 0.1 */ 
/* 17.10.19  16:00*/


typedef enum status {ALLOC_ERR = -3, MATH_ERR, INVAL_INPUT, SUCCESS} status_t;

/*
    the function receives an expression as string and pointer to double var to store the result 
    the func calculate the expression, and returns the status:
    0 : success
    -1 : invalid input
    -2 : math error
    -3 : allocation error
*/
status_t Calculate(const char *expression, double *result);



#endif /*_CALCULATE_H_*/
