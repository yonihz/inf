#include <stdlib.h> /* strtod */
#include <math.h> /* pow */
#include <string.h> /* strlen */
#include <errno.h>

#include "calc.h"
#include "stack.h"

enum state {STATE_NUM = 1, STATE_OPR = 2};

typedef struct calc_struct calc_t;
typedef int(*calc_func_t)(void);

struct calc_struct
{
    calc_func_t calc_lut[2][256];
    int prec[256];
    stack_t *stack_num;
    stack_t *stack_opr;
    const char *expr;
};

calc_t calc;

static int CalcCreate(const char *expr);
static void CalcInitLUT(void);
static int CalcSyntaxError(void);
static int CalcPushNum(void);
static int CalcPushIfNum(void);
static int CalcOpenP(void);
static int CalcNotNum(void);
static int CalcPushOrUseOpr(void);
static int CalcCloseP(void);
static int CalcStrEnd(void);
static int CalcAdd(void);
static int CalcSubstract(void);
static int CalcMultiply(void);
static int CalcDivide(void);
static int CalcPower(void);

int Calculate(const char *expr, double *result)
{
    int state = 1;
    
    state = CalcCreate(expr);
    while (state == 1 || state == 2)
    {
        state = calc.calc_lut[state - 1][(int)*(calc.expr)]();
    }

    *result = (state == SUCCESS) ? *(double*)StackPeek(calc.stack_num) : 0;
    StackDestroy(calc.stack_num);
    StackDestroy(calc.stack_opr);
    return state;
}

static int CalcCreate(const char *expr)
{
    static int is_init_lut = 0;
    size_t len = 0;

    calc.expr = expr;
    len = strlen(expr);
    calc.stack_num = StackCreate(len, sizeof(double));
    calc.stack_opr = StackCreate(len, sizeof(char));

    if (!calc.stack_num || !calc.stack_opr)
    {
        return SYSTEM_ERR;
    }

    if (!is_init_lut)
    {
        CalcInitLUT();
        is_init_lut = 1;
    }

    return STATE_NUM;
}

void CalcInitLUT(void)
{
    size_t i = 0;

    for (i = 0; i < 256; i++)
    {
        calc.calc_lut[0][i] = CalcNotNum;
    }

    for (i = 0; i < 256; i++)
    {
        calc.calc_lut[1][i] = CalcSyntaxError;
    }

    for (i = 0; i < 256; i++)
    {
        calc.prec[i] = 0;
    }

    calc.calc_lut[0]['0'] = CalcPushNum;
    calc.calc_lut[0]['1'] = CalcPushNum;
    calc.calc_lut[0]['2'] = CalcPushNum;
    calc.calc_lut[0]['3'] = CalcPushNum;
    calc.calc_lut[0]['4'] = CalcPushNum;
    calc.calc_lut[0]['5'] = CalcPushNum;
    calc.calc_lut[0]['6'] = CalcPushNum;
    calc.calc_lut[0]['7'] = CalcPushNum;
    calc.calc_lut[0]['8'] = CalcPushNum;
    calc.calc_lut[0]['9'] = CalcPushNum;

    calc.calc_lut[0]['+'] = CalcPushIfNum;
    calc.calc_lut[0]['-'] = CalcPushIfNum;
    calc.calc_lut[0]['.'] = CalcPushIfNum;
    calc.calc_lut[0][' '] = CalcPushIfNum;

    calc.calc_lut[0]['('] = CalcOpenP;

    calc.calc_lut[1]['+' + 128] = CalcAdd;
    calc.calc_lut[1]['-' + 128] = CalcSubstract;
    calc.calc_lut[1]['*' + 128] = CalcMultiply;
    calc.calc_lut[1]['/' + 128] = CalcDivide;
    calc.calc_lut[1]['^' + 128] = CalcPower;

    calc.calc_lut[1]['+'] = CalcPushOrUseOpr;
    calc.calc_lut[1]['-'] = CalcPushOrUseOpr;
    calc.calc_lut[1]['*'] = CalcPushOrUseOpr;
    calc.calc_lut[1]['/'] = CalcPushOrUseOpr;
    calc.calc_lut[1]['^'] = CalcPushOrUseOpr;

    calc.calc_lut[1][')'] = CalcCloseP;
    calc.calc_lut[1][0] = CalcStrEnd;

    calc.prec['('] = 0;
    calc.prec['+'] = 1;
    calc.prec['-'] = 1;
    calc.prec['*'] = 2;
    calc.prec['/'] = 2;
    calc.prec['^'] = 3;
}

static int CalcSyntaxError(void)
{
    return SYNTAX_ERR;
}

static int CalcPushNum(void)
{
    char *end = NULL;
    double num = 0;
    errno = 0;

    num = strtod(calc.expr, &end);
    if (errno)
    {
        return SYSTEM_ERR;
    }
    StackPush(calc.stack_num, &num);
    calc.expr = end;
    return STATE_OPR;
}

static int CalcPushIfNum(void)
{
    char *end = NULL;
    int strtod_res = 0;
    errno = 0;

    strtod(calc.expr, &end);
    if (errno)
    {
        return SYSTEM_ERR;
    }
    strtod_res = (!end) ? ('a') : ('0');
    return (calc.calc_lut[STATE_NUM - 1][strtod_res]());
}

static int CalcOpenP(void)
{
    StackPush(calc.stack_opr, calc.expr);
    ++(calc.expr);
    return STATE_NUM;
}

static int CalcNotNum(void)
{
    return SYNTAX_ERR;
}

static int CalcPushOrUseOpr(void)
{
    int curr_opr_prec = 0, new_opr_prec = 0;
    
    new_opr_prec = calc.prec[(int)*(char*)(calc.expr)];
    if (!StackIsEmpty(calc.stack_opr))
    {
        curr_opr_prec = calc.prec[(int)*(char*)StackPeek(calc.stack_opr)];
    }
    
    if (new_opr_prec <= curr_opr_prec)
    {
        calc.calc_lut[1][*(char*)StackPeek(calc.stack_opr)+128]();
        return STATE_OPR;
    }

    StackPush(calc.stack_opr, calc.expr);
    ++(calc.expr);
    return STATE_NUM;
}

static int CalcCloseP(void)
{
    int state = STATE_OPR;
    while (!StackIsEmpty(calc.stack_opr) && (state == STATE_OPR) &&
            *(char*)StackPeek(calc.stack_opr) != '(')
    {
        state = calc.calc_lut[1][*(char*)StackPeek(calc.stack_opr) + 128]();
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (StackIsEmpty(calc.stack_opr))
    {
        return SYNTAX_ERR;
    }

    StackPop(calc.stack_opr);
    ++(calc.expr);
    return STATE_OPR;
}

static int CalcStrEnd(void)
{
    int state = STATE_OPR;
    while (!StackIsEmpty(calc.stack_opr) && (state == STATE_OPR) &&
            *(char*)StackPeek(calc.stack_opr) != '(')
    {
        state = calc.calc_lut[1][*(char*)StackPeek(calc.stack_opr) + 128]();
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (!StackIsEmpty(calc.stack_opr) && 
        *(char*)StackPeek(calc.stack_opr) == '(')
    {
        return SYNTAX_ERR;
    }
    return SUCCESS;
}

static int CalcAdd(void)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);
    *num_left = *num_left + *num_right;
    return STATE_OPR;
}

static int CalcSubstract(void)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);
    *num_left = *num_left - *num_right;
    return STATE_OPR;
}

static int CalcMultiply(void)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);
    *num_left = *num_left * *num_right;
    return STATE_OPR;
}

static int CalcDivide(void)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    if (0 == *num_right)
    {
        return MATH_ERR;
    }
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);
    *num_left = *num_left / *num_right;
    return STATE_OPR;
}

static int CalcPower(void)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);
    *num_left = pow(*num_left, *num_right);
    return STATE_OPR;
}