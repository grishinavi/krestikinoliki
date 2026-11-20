#include <stdio.h>
#include <stdlib.h>
#include "world.h"

void create_world(char ***board, int rows, int cols) {
    // Выделяем память под массив
    *board = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        (*board)[i] = (char*)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            (*board)[i][j] = ' '; // Поле пустое
        }
    }
}

void free_world(char **board, int rows) {
    for (int i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}


void print_world(char **board, int rows, int cols)
{
    printf("\n");

    // Верхняя граница
    for (int j = 0; j < cols; j++)
    {
        printf("+---+");
        if (j < cols - 1)
            printf(" ");
    }
    printf("\n");

    // Содержимое поля
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("| %c |", board[i][j]);

            if (j < cols - 1)
                printf(" ");
        }
        printf("\n");
    }

    // Нижняя граница
    for (int j = 0; j < cols; j++)
    {
        printf("+---+");
        if (j < cols - 1)
            printf(" ");
    }
    printf("\n\n");
}
int check_winner(char **board, int rows, int cols, char *winner) {
    // Проверка строк
    for (int i = 0; i < rows; i++) {
        int count = 0;
        for (int j = 0; j < cols; j++) {
            if (board[i][j] != ' ' && board[i][j] == board[i][0]) count++;
        }
        if (count == cols) {
            *winner = board[i][0];
            return 1;
        }
    }

    // Проверка столбцов
    for (int j = 0; j < cols; j++) {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            if (board[i][j] != ' ' && board[i][j] == board[0][j]) count++;
        }
        if (count == rows) {
            *winner = board[0][j];
            return 1;
        }
    }

    // Проверка диагоналей (если поле квадратное)
    if (rows == cols) {
        int count1 = 0, count2 = 0;
        for (int i = 0; i < rows; i++) {
            if (board[i][i] != ' ' && board[i][i] == board[0][0]) count1++;
            if (board[i][cols - 1 - i] != ' ' && board[i][cols - 1 - i] == board[0][cols - 1]) count2++;
        }
        if (count1 == rows) {
            *winner = board[0][0];
            return 1;
        }
        if (count2 == rows) {
            *winner = board[0][cols - 1];
            return 1;
        }
    }

    return 0;
}

int check_draw(char **board, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == ' ') return 0; // Есть свободные клетки
        }
    }
    return 1; // Ничья
}
