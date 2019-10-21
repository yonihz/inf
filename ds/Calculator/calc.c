#include <stdlib.h> /* strtod */
#include <math.h> /* pow */
#include <string.h> /* strlen */

#include "calc.h"
#include "stack.h"

#define UNUSED(x) (void)(x)

enum state {STATE_NUM = 1, STATE_OPR = 2};

typedef struct calc calc_t;
typedef int(*calc_func_t)(calc_t *calc);

struct calc
{
    calc_func_t calc_lut[2][256];
    int prec[256];
    stack_t *stack_num;
    stack_t *stack_opr;
    const char *expr;
};

static void InitCalcLUT(calc_t *calc);
static int CalcSyntaxError(calc_t *calc);
static int CalcPushNum(calc_t *calc);
static int CalcPushIfNum(calc_t *calc);
static int CalcOpenP(calc_t *calc);
static int CalcNotNum(calc_t *calc);
static int CalcPushOrUseOpr(calc_t *calc);
static int CalcPushOpr(calc_t *calc);
static int CalcUseOpr(calc_t *calc);
static int CalcCloseP(calc_t *calc);
static int CalcStrEnd(calc_t *calc);
static int CalcAdd(calc_t *calc);
static int CalcSubstract(calc_t *calc);
static int CalcMultiply(calc_t *calc);
static int CalcDivide(calc_t *calc);
static int CalcPower(calc_t *calc);

int Calculate(const char *expr, double *result)
{
    int state = 1;
    static int is_init_lut = 0;
    size_t len = 0;
    static calc_t *calc;

    calc = (calc_t*)malloc(sizeof(calc_t));
    calc->expr = expr;
    len = strlen(expr);
    calc->stack_num = StackCreate(len, sizeof(double));
    calc->stack_opr = StackCreate(len, sizeof(char));
    /*
    if (!is_init_lut)
    {
        InitCalcLUT(calc);
        is_init_lut = 1;
    }
    */
    InitCalcLUT(calc);
    while (state == 1 || state == 2)
    {
        state = calc->calc_lut[state - 1][(int)*(calc->expr)](calc);
    }

    *result = (state == SUCCESS) ? *(double*)StackPeek(calc->stack_num) : 0;
    StackDestroy(calc->stack_num);
    StackDestroy(calc->stack_opr);
    return state;
}

void InitCalcLUT(calc_t *calc)
{
    size_t i = 0;

    for (i = 0; i < 256; i++)
    {
        calc->calc_lut[0][i] = CalcNotNum;
    }

    for (i = 0; i < 256; i++)
    {
        calc->calc_lut[1][i] = CalcSyntaxError;
    }

    for (i = 0; i < 256; i++)
    {
        calc->prec[i] = 0;
    }

    calc->calc_lut[0]['0'] = CalcPushNum;
    calc->calc_lut[0]['1'] = CalcPushNum;
    calc->calc_lut[0]['2'] = CalcPushNum;
    calc->calc_lut[0]['3'] = CalcPushNum;
    calc->calc_lut[0]['4'] = CalcPushNum;
    calc->calc_lut[0]['5'] = CalcPushNum;
    calc->calc_lut[0]['6'] = CalcPushNum;
    calc->calc_lut[0]['7'] = CalcPushNum;
    calc->calc_lut[0]['8'] = CalcPushNum;
    calc->calc_lut[0]['9'] = CalcPushNum;

    calc->calc_lut[0]['+'] = CalcPushIfNum;
    calc->calc_lut[0]['-'] = CalcPushIfNum;
    calc->calc_lut[0]['.'] = CalcPushIfNum;
    calc->calc_lut[0][' '] = CalcPushIfNum;

    calc->calc_lut[0]['('] = CalcOpenP;

    calc->calc_lut[1]['+' + 128] = CalcAdd;
    calc->calc_lut[1]['-' + 128] = CalcSubstract;
    calc->calc_lut[1]['*' + 128] = CalcMultiply;
    calc->calc_lut[1]['/' + 128] = CalcDivide;
    calc->calc_lut[1]['^' + 128] = CalcPower;

    calc->calc_lut[1]['+'] = CalcPushOrUseOpr;
    calc->calc_lut[1]['-'] = CalcPushOrUseOpr;
    calc->calc_lut[1]['*'] = CalcPushOrUseOpr;
    calc->calc_lut[1]['/'] = CalcPushOrUseOpr;
    calc->calc_lut[1]['^'] = CalcPushOrUseOpr;

    calc->calc_lut[1][')'] = CalcCloseP;
    calc->calc_lut[1][0] = CalcStrEnd;

    calc->calc_lut[1][1] = CalcPushOpr;
    calc->calc_lut[1][2] = CalcUseOpr;

    calc->prec['('] = 0;
    calc->prec['+'] = 1;
    calc->prec['-'] = 1;
    calc->prec['*'] = 2;
    calc->prec['/'] = 2;
    calc->prec['^'] = 3;
}

static int CalcSyntaxError(calc_t *calc)
{
    UNUSED(calc);
    return SYNTAX_ERR;
}

static int CalcPushNum(calc_t *calc)
{
    char *end = NULL;
    double *num = NULL;

    num = (double*)malloc(sizeof(double));
    end = (char*)calc->expr;
    *num = strtod(calc->expr, &end);
    /* TODO: add error detection. errno = 0. if errno != 0 return SYSTEM_ERR */
    StackPush(calc->stack_num, num);
    calc->expr = end;
    return STATE_OPR;
}

static int CalcPushIfNum(calc_t *calc)
{
    char *end = NULL;
    int strtod_res = 0;

    end = (char*)calc->expr;
    strtod(calc->expr, &end);
    strtod_res = calc->expr == end ? 'a' : '0';
    return (calc->calc_lut[STATE_NUM - 1][strtod_res](calc));
}

static int CalcOpenP(calc_t *calc)
{
    StackPush(calc->stack_opr, calc->expr);
    ++(calc->expr);
    return STATE_NUM;
}

static int CalcNotNum(calc_t *calc)
{
    UNUSED(calc);
    return SYNTAX_ERR;
}

static int CalcPushOrUseOpr(calc_t *calc)
{
    int state = 0, is_higher_prec = 0;
    int curr_opr_prec = 0, new_opr_prec = 0;
    
    new_opr_prec = calc->prec[(int)*(char*)(calc->expr)];
    if (StackIsEmpty(calc->stack_opr))
    {
        curr_opr_prec = 0;
    }
    else
    {
        curr_opr_prec = calc->prec[(int)*(char*)StackPeek(calc->stack_opr)];
    }
    
    is_higher_prec = new_opr_prec <= curr_opr_prec;

    /* Push new opr: calc_lut[1][1], Use current opr: calc_lut[1][2] */
    state = calc->calc_lut[1][is_higher_prec + 1](calc);
    return (state);
}

static int CalcPushOpr(calc_t *calc)
{
    StackPush(calc->stack_opr, calc->expr);
    ++(calc->expr);
    return STATE_NUM;
}

static int CalcUseOpr(calc_t *calc)
{
    calc->calc_lut[1][*(char*)StackPeek(calc->stack_opr)+128](calc);
    return STATE_OPR;
}

static int CalcCloseP(calc_t *calc)
{
    int state = STATE_OPR;
    while (!StackIsEmpty(calc->stack_opr) && (state == STATE_OPR) &&
            *(char*)StackPeek(calc->stack_opr) != '(')
    {
        state = calc->calc_lut[1][*(char*)StackPeek(calc->stack_opr) + 128](calc);
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (StackIsEmpty(calc->stack_opr))
    {
        return SYNTAX_ERR;
    }

    StackPop(calc->stack_opr);
    ++(calc->expr);
    return STATE_OPR;
}

static int CalcStrEnd(calc_t *calc)
{
    int state = STATE_OPR;
    while (!StackIsEmpty(calc->stack_opr) && (state == STATE_OPR) &&
            *(char*)StackPeek(calc->stack_opr) != '(')
    {
        state = calc->calc_lut[1][*(char*)StackPeek(calc->stack_opr) + 128](calc);
    }

    if (state == MATH_ERR)
    {
        return MATH_ERR;
    }

    if (!StackIsEmpty(calc->stack_opr) && 
        *(char*)StackPeek(calc->stack_opr) == '(')
    {
        return SYNTAX_ERR;
    }
    return SUCCESS;
}

static int CalcAdd(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc->stack_opr);
    num_right = (double*)StackPeek(calc->stack_num);
    StackPop(calc->stack_num);
    num_left = (double*)StackPeek(calc->stack_num);
    *num_left = *num_left + *num_right;
    return STATE_OPR;
}

static int CalcSubstract(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc->stack_opr);
    num_right = (double*)StackPeek(calc->stack_num);
    StackPop(calc->stack_num);
    num_left = (double*)StackPeek(calc->stack_num);
    *num_left = *num_left - *num_right;
    return STATE_OPR;
}

static int CalcMultiply(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc->stack_opr);
    num_right = (double*)StackPeek(calc->stack_num);
    StackPop(calc->stack_num);
    num_left = (double*)StackPeek(calc->stack_num);
    *num_left = *num_left * *num_right;
    return STATE_OPR;
}

static int CalcDivide(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc->stack_opr);
    num_right = (double*)StackPeek(calc->stack_num);
    if (0 == *num_right)
    {
        return MATH_ERR;
    }
    StackPop(calc->stack_num);
    num_left = (double*)StackPeek(calc->stack_num);
    *num_left = *num_left / *num_right;
    return STATE_OPR;
}

static int CalcPower(calc_t *calc)
{
    double *num_left = NULL, *num_right = NULL;
    StackPop(calc->stack_opr);
    num_right = (double*)StackPeek(calc->stack_num);
    StackPop(calc->stack_num);
    num_left = (double*)StackPeek(calc->stack_num);
    *num_left = pow(*num_left, *num_right);
    return STATE_OPR;
}