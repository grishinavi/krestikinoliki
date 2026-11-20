#include <stdio.h>
#include <stdlib.h>
#include "world.h"

char **create_world(int rows, int cols)
{
    char **board = malloc(rows * sizeof(char *));

    if (board == NULL)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        board[i] = malloc(cols * sizeof(char));

        if (board[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(board[j]);

            free(board);
            return NULL;
        }

        for (int j = 0; j < cols; j++)
            board[i][j] = ' ';
    }

    return board;
}

void free_world(char **board, int rows)
{
    for (int i = 0; i < rows; i++)
        free(board[i]);

    free(board);
}

void print_world(char **board, int rows, int cols)
{
    printf("\n");

    /* Верхняя граница */
    printf("+");
    for (int j = 0; j < cols; j++)
        printf("-");
    printf("+\n");

    /* Строки поля: рамка, символы подряд, рамка */
    for (int i = 0; i < rows; i++)
    {
        printf("|");

        for (int j = 0; j < cols; j++)
            printf("%c", board[i][j]);

        printf("|\n");
    }

    /* Нижняя граница */
    printf("+");
    for (int j = 0; j < cols; j++)
        printf("-");
    printf("+\n");

    printf("\n");
}

/*
 * Проверяет линию, которая начинается в клетке (r, c) на краю поля
 * и идёт в направлении (dr, dc) до противоположного края.
 * Линия выигрышная, если вся она состоит из одного символа.
 */
static int check_line(
    char **board,
    int rows,
    int cols,
    int r,
    int c,
    int dr,
    int dc,
    char *winner
)
{
    char symbol = board[r][c];

    if (symbol == ' ')
        return 0;

    /* Начало линии должно лежать на краю поля */
    int pr = r - dr;
    int pc = c - dc;

    if (pr >= 0 && pr < rows &&
        pc >= 0 && pc < cols)
        return 0;

    int count = 0;

    while (r >= 0 && r < rows &&
           c >= 0 && c < cols)
    {
        if (board[r][c] != symbol)
            return 0;

        count++;

        r += dr;
        c += dc;
    }

    if (count > 1)
    {
        *winner = symbol;
        return 1;
    }

    return 0;
}

int check_winner(
    char **board,
    int rows,
    int cols,
    char *winner
)
{
    int directions[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (int d = 0; d < 4; d++)
            {
                if (check_line(
                    board,
                    rows,
                    cols,
                    i,
                    j,
                    directions[d][0],
                    directions[d][1],
                    winner
                ))
                    return 1;
            }
        }
    }

    return 0;
}

int check_draw(char **board, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }

    return 1;
}
