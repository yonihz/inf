#include <stdio.h>
#include <stdlib.h>

#define NCOLS 8
#define NROWS 8
#define NADJS 8

size_t CountIslands(char bitmap[][NCOLS], int nrows, int ncols);
void VisitAdj(
    char bitmap[][NCOLS], char visited[][NCOLS], int adj[][2],
    int nrows, int ncols, int row, int col);

int main()
{
     char bitmap[NROWS][NCOLS] = {
        {1, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0}};

/*     char bitmap[NROWS][NCOLS] = {
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0}}; */

    printf("Island count is: %lu\n", CountIslands(bitmap, NROWS, NCOLS));

    return 0;
}

size_t CountIslands(char bitmap[][NCOLS], int nrows, int ncols)
{
    int i = 0, j = 0;    
    size_t count = 0;
    char visited[NROWS][NCOLS] = {0};
    
    int adj[NADJS][2] = {
        {1, 1}, {1, 0}, {1, -1}, {0, 1},
        {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

    for (i = 0; i < nrows; ++i)
    {
        for (j = 0; j < ncols; ++j)
        {
            if ((bitmap[i][j] == 1) && (visited[i][j] == 0))
            {
                visited[i][j] = 1;
                ++count;
                printf("Island %lu at (%d, %d)\n", count, i, j);
                VisitAdj(bitmap, visited, adj, nrows, ncols, i, j);
            }
        }
    }

    return count;
}

void VisitAdj(
    char bitmap[][NCOLS], char visited[][NCOLS], int adj[][2],
    int nrows, int ncols, int row, int col)
{
    int i = 0;
    int check_row = 0, check_col = 0;
    
    for(i = 0; i < NADJS; ++i)
    {
        check_row = row + adj[i][0];
        check_col = col + adj[i][1];

        if (
            check_row >= 0 && check_row < nrows &&
            check_col >= 0 && check_col < ncols &&
            (bitmap[check_row][check_col] == 1) &&
            (visited[check_row][check_col] == 0))
        {
           visited[check_row][check_col] = 1;
           VisitAdj(bitmap, visited, adj, ncols, nrows, check_row, check_col);
        }
    }

}