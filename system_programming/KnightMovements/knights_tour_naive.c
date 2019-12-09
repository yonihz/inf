#include <stdlib.h>
#include <stdio.h>

#define NROWS 8
#define NCOLS 8
#define NOPTIONS 8
#define NSQUARES 64

enum {SUCCESS = 0, FAILURE = 1} status_t;

/* row and col are zero based: [0,7] */
void KnightsTour(unsigned char row, unsigned char col, unsigned int LUT_moves[NROWS][NCOLS]);

int RecKnightsTour(size_t bit_arr, int square, unsigned int count, unsigned int LUT_moves[NROWS][NCOLS]);

void PrintLUT(unsigned int arr[NROWS][NCOLS], size_t size1, size_t size2);

int main()
{
    unsigned int LUT_moves[NROWS][NCOLS] = {0};

    KnightsTour(1, 1, LUT_moves);

    PrintLUT(LUT_moves, NROWS, NCOLS);

    return 0;
}

void KnightsTour(unsigned char row, unsigned char col, unsigned int LUT_moves[NROWS][NCOLS])
{
    size_t bit_arr_start = 0ul;
    unsigned int count = 0;
    int first_square = row * NROWS + col;

    RecKnightsTour(bit_arr_start, first_square, count, LUT_moves);
}

int RecKnightsTour(size_t bit_arr, int square, unsigned int count, unsigned int LUT_moves[NROWS][NCOLS])
{
    size_t i = 0;
    int next_square = 0, next_square_row = 0, next_square_col = 0;
    int status = FAILURE;
    int move_options[8][2] = {
        {2, 1}, {2, -1}, {1, 2}, {1, -2},
        {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

    count++;
    bit_arr |= (1ul << square);

    if (count == NSQUARES)
    {
        LUT_moves[square / NROWS][square % NROWS] = count;

        return SUCCESS;
    }

    for (i = 0; i < NOPTIONS && status != SUCCESS; i++)
    {
        next_square_row = square / NROWS + move_options[i][0];
        next_square_col = square % NROWS + move_options[i][1];
        next_square = next_square_row * NROWS + next_square_col;
        
        /* skip option if out of board or was already visited */
        if (next_square_row < 0 || next_square_row >= NROWS ||
            next_square_col < 0 || next_square_col >= NROWS ||
            ((bit_arr & (1ul << next_square)) != 0))
        {
            continue;
        }
        
        status = RecKnightsTour(bit_arr, next_square, count, LUT_moves);
    }

    if (SUCCESS == status)
    {
        LUT_moves[square / NROWS][square % NROWS] = count;

        return SUCCESS;        
    }
    else
    {
        return FAILURE;
    }
}

void PrintLUT(unsigned int arr[NROWS][NCOLS], size_t size1, size_t size2)
{
    size_t i = 0, j = 0;

    for (i = 0; i < size1; i++)
    {
        for (j = 0; j < size2; j++)
        {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}