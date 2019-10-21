#include <stdlib.h> /* strtod */
#include <math.h> /* pow */

#include "calc.h"
#include "stack.h"

enum state {STATE_NUM = 1, STATE_OPR = 2};

typedef int(*calc_func_t)(calc_t *calc);

typedef struct
{
    calc_func_t *calc_lut[2][256];
    stack_t *stack_num;
    stack_t *stack_opr;
    int state;
    char *expr;
} calc_t;

void InitCalcLUT(calc_t *calc);

int CalcPushNum(calc_t *calc);
int CalcPushIfNum(calc_t *calc);
int CalcOpenP(calc_t *calc);
int CalcNotNum(calc_t *calc);
int CalcPushOpr(calc_t *calc);
int CalcUseOpr(calc_t *calc);
int CalcCloseP(calc_t *calc);
int CalcStrEnd(calc_t *calc);
int CalcAdd(calc_t *calc);
int CalcSubstract(calc_t *calc);
int CalcMultiply(calc_t *calc);
int CalcDivide(calc_t *calc);
int CalcPower(calc_t *calc);

int Calculate(const char *expr, double *result)
{
    int state = 1;
    int is_init_lut = 0;
    size_t len = strlen(expr);
    static calc_t *calc;
    calc = (calc_t*)malloc(sizeof(calc_t));
    calc->stack_num = StackCreate(len, sizeof(double));
    calc->stack_opr = StackCreate(len, sizeof(char));
    
    if (is_init_lut)
    {
        InitCalcLUT(calc);
    }

    while (state == 1 || state == 2)
    {
        state = calc->calc_lut[state][*(calc->expr)];
    }

    return state;
}

void InitCalcLUT(calc_t *calc)
{
    for (i = 0; i < 256; i++)
    {
        calc->calc_lut[0][i] = CalcNotNum;
    }

    for (i = 0; i < 256; i++)
    {
        calc->calc_lut[1][i] = CalcSyntaxError;
    }

    calc->calc_lut[0]['0'] = CalcPushNum;
    calc->calc_lut[0]['1'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['2'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['3'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['4'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['5'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['6'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['7'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['8'] = calc->calc_lut[0]['0'];
    calc->calc_lut[0]['9'] = calc->calc_lut[0]['0'];

    calc->calc_lut[0]['+'] = CalcPushIfNum;
    calc->calc_lut[0]['-'] = calc->calc_lut[0]['+'];
    calc->calc_lut[0]['.'] = calc->calc_lut[0]['+'];
    calc->calc_lut[0][' '] = calc->calc_lut[0]['+'];
    calc->calc_lut[0]['/t'] = calc->calc_lut[0]['+'];

    calc->calc_lut[0]['('] = CalcOpenP;

    calc->calc_lut[1]['+' + 128] = CalcAdd;
    calc->calc_lut[1]['-' + 128] = CalcSubstract;
    calc->calc_lut[1]['*' + 128] = CalcMultiply;
    calc->calc_lut[1]['/' + 128] = CalcDivide;
    calc->calc_lut[1]['^' + 128] = CalcPower;

    calc->calc_lut[1]['+'] = CalcUseOpr;
    calc->calc_lut[1]['-'] = calc->calc_lut[1]['+'];
    calc->calc_lut[1]['*'] = calc->calc_lut[1]['+'];
    calc->calc_lut[1]['/'] = calc->calc_lut[1]['+'];
    calc->calc_lut[1]['^'] = calc->calc_lut[1]['+'];

    calc->calc_lut[1][')'] = CalcCloseP;
    calc->calc_lut[1]['/0'] = CalcStrEnd;

    calc->calc_lut[1][0] = CalcUseOpr;
    calc->calc_lut[1][1] = CalcPushOpr;    
}

int CalcSyntaxError(calc_t calc)
{
    /* TODO: return SYNTAX_ERROR */
}

int CalcPushNum(calc_t *calc)
{
    char **end = NULL;
    double *num = NULL;

    num = (double*)malloc(sizeof(double));
    end = &(calc->expr);
    *num = strtod(calc->expr, end);
    /* TODO: add error detection. errno = 0. if errno != 0 return STATE_SYSTEM_ERROR */
    StackPush(calc->stack_num, num);
    calc->expr = *end;
    return STATE_OPR;
}

int CalcPushIfNum(calc_t *calc)
{
    char **end = NULL;
    char strtod_res = 0;

    end = &(calc->expr);
    strtod(calc->expr, end);
    strtod_res = calc->expr == *end ? 'a' : '0';
    return (calc->calc_lut[STATE_NUM - 1][strtod_res]);
}

int CalcOpenP(calc_t *calc)
{
    StackPush(calc->stack_opr, calc->expr);
    ++(calc->expr);
    return STATE_NUM;
}

int CalcNotNum(calc_t *calc)
{
    return SYNTAX_ERR;
}

int CalcPushOpr(calc_t *calc)
{
    calc->calc_lut[2][*(char*)StackPeek(calc->stack_opr)+128];
    return STATE_OPR;
}

int CalcUseOpr(calc_t *calc)
{
    StackPush(calc->stack_opr, *(calc->expr));
    ++(calc->expr);
    return STATE_NUM;
}

int CalcCloseP(calc_t *calc)
{
    char *open_p;
    while (*(char*)StackPeek(calc->stack_opr) != '(' &&
            !StackIsEmpty(calc->stack_opr));
    {
        calc->calc_lut[1][*(char*)StackPeek(calc->stack_opr) + 128];
    }

    if (StackIsEmpty(calc->stack_opr))
    {
        return SYNTAX_ERR;
    }

    open_p = StackPeek(calc->stack_opr); 
    StackPop(calc->stack_opr);
    free(open_p);
    return STATE_OPR;
}

int CalcStrEnd(calc_t *calc)
{
    /* TODO: if stack_opr empty return success */ 
}

int CalcAdd(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    char *opr = NULL;
    opr = StackPeek(calc->stack_opr);
    free(opr);
    StackPop(calc->stack_opr);
    num_right = StackPeek(calc->stack_num);
    free(num_right);
    StackPop(calc->stack_num);
    num_left = StackPeek(calc->stack_num);
    *num_left = *num_left + *num_right;
    return STATE_OPR;
}

int CalcSubstract(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    char *opr = NULL;
    opr = StackPeek(calc->stack_opr);
    free(opr);
    StackPop(calc->stack_opr);
    num_right = StackPeek(calc->stack_num);
    free(num_right);
    StackPop(calc->stack_num);
    num_left = StackPeek(calc->stack_num);
    *num_left = *num_left - *num_right;
    return STATE_OPR;
}

int CalcMultiply(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    char *opr = NULL;
    opr = StackPeek(calc->stack_opr);
    free(opr);
    StackPop(calc->stack_opr);
    num_right = StackPeek(calc->stack_num);
    free(num_right);
    StackPop(calc->stack_num);
    num_left = StackPeek(calc->stack_num);
    *num_left = *num_left * *num_right;
    return STATE_OPR;
}

int CalcDivide(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    char *opr = NULL;
    opr = StackPeek(calc->stack_opr);
    free(opr);
    StackPop(calc->stack_opr);
    num_right = StackPeek(calc->stack_num);
    free(num_right);
    StackPop(calc->stack_num);
    num_left = StackPeek(calc->stack_num);
    *num_left = *num_left / *num_right;
    return STATE_OPR;
}

int CalcPower(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    char *opr = NULL;
    opr = StackPeek(calc->stack_opr);
    free(opr);
    StackPop(calc->stack_opr);
    num_right = StackPeek(calc->stack_num);
    free(num_right);
    StackPop(calc->stack_num);
    num_left = StackPeek(calc->stack_num);
    *num_left = pow(*num_left, *num_right);
    return STATE_OPR;
}