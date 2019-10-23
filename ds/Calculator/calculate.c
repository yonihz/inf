#include <stdlib.h> /* strtod */
#include <math.h> /* pow */
#include <string.h> /* strlen */
#include <errno.h>

#include "calculate.h"
#include "stack.h"

enum state {STATE_NUM = 0, STATE_OPR = 1, STATE_SUCCESS = 2};

#define NSTATES 2
#define ASCII_SIZE 256

typedef struct calc_struct calc_t;
typedef int(*calc_func_t)(void);

struct calc_struct
{
    calc_func_t calc_lut[NSTATES][ASCII_SIZE];
    int prec[ASCII_SIZE];
    stack_t *stack_num;
    stack_t *stack_opr;
    const char *expr;
};

static calc_t calc;

static int CalcCreate(const char *expr);
static int CalcUseOpr(void);
static void CalcInitLUT(void);
static int CalcSyntaxError(void);
static int CalcPushNum(void);
static int CalcPushIfNum(void);
static int CalcOpenP(void);
static int CalcNotNum(void);
static int CalcPushOrUseOpr(void);
static int CalcCloseP(void);
static int CalcStrEnd(void);

int Calculate(const char *expr, double *result)
{
    int state = STATE_NUM;
    
    state = CalcCreate(expr);
    while (state == STATE_NUM || state == STATE_OPR)
    {
        state = calc.calc_lut[state][(int)*(calc.expr)]();
    }

    *result = (state == STATE_SUCCESS) ? *(double*)StackPeek(calc.stack_num) : 0;
    state = (state == STATE_SUCCESS) ? SUCCESS : state;
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
        return ALLOC_ERR;
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

    /* Num-state LUT init */
    for (i = 0; i < ASCII_SIZE; i++)
    {
        calc.calc_lut[STATE_NUM][i] = CalcNotNum;
    }

    calc.calc_lut[STATE_NUM]['0'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['1'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['2'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['3'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['4'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['5'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['6'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['7'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['8'] = CalcPushNum;
    calc.calc_lut[STATE_NUM]['9'] = CalcPushNum;

    calc.calc_lut[STATE_NUM]['+'] = CalcPushIfNum;
    calc.calc_lut[STATE_NUM]['-'] = CalcPushIfNum;
    calc.calc_lut[STATE_NUM]['.'] = CalcPushIfNum;
    calc.calc_lut[STATE_NUM][' '] = CalcPushIfNum;

    calc.calc_lut[STATE_NUM]['('] = CalcOpenP;

    /* Operator-state LUT init */
    for (i = 0; i < ASCII_SIZE; i++)
    {
        calc.calc_lut[STATE_OPR][i] = CalcSyntaxError;
    }

    calc.calc_lut[STATE_OPR]['+'] = CalcPushOrUseOpr;
    calc.calc_lut[STATE_OPR]['-'] = CalcPushOrUseOpr;
    calc.calc_lut[STATE_OPR]['*'] = CalcPushOrUseOpr;
    calc.calc_lut[STATE_OPR]['/'] = CalcPushOrUseOpr;
    calc.calc_lut[STATE_OPR]['^'] = CalcPushOrUseOpr;

    calc.calc_lut[STATE_OPR][')'] = CalcCloseP;
    calc.calc_lut[STATE_OPR][0] = CalcStrEnd;

    /* Precedence LUT init */
    for (i = 0; i < ASCII_SIZE; i++)
    {
        calc.prec[i] = 0;
    }

    calc.prec['('] = 0;
    calc.prec['+'] = 1;
    calc.prec['-'] = 1;
    calc.prec['*'] = 2;
    calc.prec['/'] = 2;
    calc.prec['^'] = 3;
}

static int CalcSyntaxError(void)
{
    return INVAL_INPUT;
}

static int CalcPushNum(void)
{
    char *end = NULL;
    double num = 0;
    errno = 0;

    num = strtod(calc.expr, &end);
    if (errno)
    {
        return ALLOC_ERR;
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
        return ALLOC_ERR;
    }
    strtod_res = (!end) ? ('a') : ('0');

    return (calc.calc_lut[STATE_NUM][strtod_res]());
}

static int CalcOpenP(void)
{
    StackPush(calc.stack_opr, calc.expr);
    ++(calc.expr);

    return STATE_NUM;
}

static int CalcNotNum(void)
{
    return INVAL_INPUT;
}

static int CalcPushOrUseOpr(void)
{
    int curr_opr_prec = 0, new_opr_prec = 0;
    int state = STATE_OPR;
    
    new_opr_prec = calc.prec[(int)*(char*)(calc.expr)];
    if (!StackIsEmpty(calc.stack_opr))
    {
        curr_opr_prec = calc.prec[(int)*(char*)StackPeek(calc.stack_opr)];
    }
    
    if (new_opr_prec <= curr_opr_prec)
    {
        state = CalcUseOpr();
        return state;
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
        state = CalcUseOpr();
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (StackIsEmpty(calc.stack_opr))
    {
        return INVAL_INPUT;
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
        state = CalcUseOpr();
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (!StackIsEmpty(calc.stack_opr) && 
        *(char*)StackPeek(calc.stack_opr) == '(')
    {
        return INVAL_INPUT;
    }
    
    return STATE_SUCCESS;
}

static int CalcUseOpr(void)
{
    double *num_left = NULL, *num_right = NULL;
    char opr = 0;

    opr = *(char*)StackPeek(calc.stack_opr);
    StackPop(calc.stack_opr);
    num_right = (double*)StackPeek(calc.stack_num);
    StackPop(calc.stack_num);
    num_left = (double*)StackPeek(calc.stack_num);

    switch (opr)
    {
        case '+':
        {
            *num_left = *num_left + *num_right;
            break;
        }
        case '-':
        {
            *num_left = *num_left - *num_right;
            break;
        }
        case '*':
        {
            *num_left = *num_left * *num_right;
            break;
        }
        case '/':
        {
            if (0 == *num_right)
            {
                return MATH_ERR;
            }
            *num_left = *num_left / *num_right;
            break;
        }
        case '^':
        {
            *num_left = pow(*num_left, *num_right);
            break;
        }
    }

    return STATE_OPR;    
}