#include <stdlib.h>
#include <stdio.h>

#define NROWS 8
#define NCOLS 8
#define NOPTIONS 8
#define NSQUARES 64

enum {SUCCESS = 0, FAILURE = 1} status_t;

/* row and col are zero based: [0,7] */
void KnightsTour(unsigned char row, unsigned char col, unsigned int LUT_moves[NROWS][NCOLS]);

int RecKnightsTour(size_t bit_arr, int square, unsigned int count, unsigned int LUT_moves[NROWS][NCOLS], int move_options[8][3]);
void SortOptionsArr(int move_options[NOPTIONS][3], size_t bit_arr, int square);
void BubbleSort(int arr[NOPTIONS][3]);
static void SwapInt(int *a, int *b);
void PrintLUT(unsigned int arr[NROWS][NCOLS], size_t size1, size_t size2);
void CheckLUT(unsigned int arr[NROWS][NCOLS], size_t size1, size_t size2);

int main()
{
    unsigned int LUT_moves[NROWS][NCOLS] = {0};

    KnightsTour(2, 2, LUT_moves);

    CheckLUT(LUT_moves, NROWS, NCOLS);
    PrintLUT(LUT_moves, NROWS, NCOLS);

    return 0;
}

void KnightsTour(unsigned char row, unsigned char col, unsigned int LUT_moves[NROWS][NCOLS])
{
    size_t bit_arr_start = 0ul;
    unsigned int count = 0;

    /* each row is {number of adjacent unvisited, row offset, offset} */
    int move_options[NOPTIONS][3] = {
        {0, 2, 1}, {0, 2, -1}, {0, 1, 2}, {0, 1, -2},
        {0, -1, 2}, {0, -1, -2}, {0, -2, 1}, {0, -2, -1}};
    
    int first_square = row * NROWS + col;

    RecKnightsTour(bit_arr_start, first_square, count, LUT_moves, move_options);
}

int RecKnightsTour(size_t bit_arr, int square, unsigned int count, unsigned int LUT_moves[NROWS][NCOLS], int move_options[NOPTIONS][3])
{
    size_t i = 0;
    int next_square = 0, next_square_row = 0, next_square_col = 0;
    int status = FAILURE;

    count++;
    bit_arr |= (1ul << square);

    SortOptionsArr(move_options, bit_arr, square);

    if (count == NSQUARES)
    {
        LUT_moves[square / NROWS][square % NROWS] = count;

        return SUCCESS;
    }

    for (i = 0; i < NOPTIONS && status != SUCCESS; i++)
    {
        next_square_row = square / NROWS + move_options[i][1];
        next_square_col = square % NROWS + move_options[i][2];
        next_square = next_square_row * NROWS + next_square_col;
        
        /* skip option if out of board or was already visited */
        if (next_square_row < 0 || next_square_row >= NROWS ||
            next_square_col < 0 || next_square_col >= NROWS ||
            ((bit_arr & (1ul << next_square)) != 0))
        {
            continue;
        }
        
        status = RecKnightsTour(bit_arr, next_square, count, LUT_moves, move_options);
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

void SortOptionsArr(int move_options[NOPTIONS][3], size_t bit_arr, int square)
{
    size_t i = 0, j = 0, count_unvisited = 0;
    int next_square = 0, next_square_row = 0, next_square_col = 0;
    int check_square = 0, check_square_row = 0, check_square_col = 0;

    for (i = 0; i < NOPTIONS; i++)
    {
        next_square_row = square / NROWS + move_options[i][1];
        next_square_col = square % NROWS + move_options[i][2];
        next_square = next_square_row * NROWS + next_square_col;
        
        /* set unvisited number to 0 if out of board or was already visited */
        if (next_square_row < 0 || next_square_row >= NROWS ||
            next_square_col < 0 || next_square_col >= NROWS ||
            ((bit_arr & (1ul << next_square)) != 0))
        {
            move_options[i][0] = 0;
            continue;
        }

        count_unvisited = 0;

        for (j = 0; j < NOPTIONS; j++)
        {
            check_square_row = next_square / NROWS + move_options[j][1];
            check_square_col = next_square % NROWS + move_options[j][2];
            check_square = check_square_row * NROWS + check_square_col;
            
            /* skip option if out of board or was already visited */
            if (check_square_row < 0 || check_square_row >= NROWS ||
                check_square_col < 0 || check_square_col >= NROWS ||
                ((bit_arr & (1ul << check_square)) != 0))
            {
                continue;
            }

            ++count_unvisited;
        }

        move_options[i][0] = count_unvisited;
    }

    BubbleSort(move_options);
}

void BubbleSort(int arr[NOPTIONS][3])
{
    size_t i = 0;
    size_t size = NOPTIONS;
    while (size > 1)
    {
        for (i = 0; i < size - 1; ++i)
        {
            if (arr[i][0] > arr[i + 1][0])
            {
                SwapInt(&arr[i][0], &arr[i+1][0]);
                SwapInt(&arr[i][1], &arr[i+1][1]);
                SwapInt(&arr[i][2], &arr[i+1][2]);
            }
        }
        --size;
    }
}

static void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

void CheckLUT(unsigned int arr[NROWS][NCOLS], size_t size1, size_t size2)
{
    size_t i = 0, j = 0, count = 0;
    int square = 0;
    int next_square_row = 0, next_square_col = 0;
    int move_options[NOPTIONS][3] = {
        {0, 2, 1}, {0, 2, -1}, {0, 1, 2}, {0, 1, -2},
        {0, -1, 2}, {0, -1, -2}, {0, -2, 1}, {0, -2, -1}};

    for (i = 0; i < size1; i++)
    {
        for (j = 0; j < size2; j++)
        {
            if (1 == arr[i][j])
            {
                break;
            }
        }

        if (1 == arr[i][j])
        {
            break;
        }
    }
    
    square = i * NROWS + j;

    for (count = 1; count <= NSQUARES; count++)
    {
        for (i = 0; i < NOPTIONS; i++)
        {
            next_square_row = square / NROWS + move_options[i][1];
            next_square_col = square % NROWS + move_options[i][2];
            
            if (next_square_row < 0 || next_square_row >= NROWS ||
                next_square_col < 0 || next_square_col >= NROWS)
            {
                continue;
            }

            if (arr[next_square_row][next_square_col] == (count + 1))
            {
                square = next_square_row * NROWS + next_square_col;
                break;
            }
        }

        if (i == NOPTIONS)
        {
            break;
        }
    }

    (count == NSQUARES) ? printf("TEST PASS\n") : printf("TEST FAIL\n");
}