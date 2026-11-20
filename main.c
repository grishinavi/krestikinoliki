#include <stdio.h>
#include <stdlib.h>

#include "world.h"
#include "character.h"

#define MIN_SIZE 2
#define MAX_SIZE 50

int main(void)
{
#ifdef _WIN32
    /* Включаем UTF-8 в консоли Windows, чтобы русский текст отображался */
    system("chcp 65001 > nul");
#endif

    int rows, cols;
    int status;

    char player1, player2;
    char winner = ' ';

    printf("=== КРЕСТИКИ-НОЛИКИ ===\n\n");

    /* Выбор размера поля */
    while (1)
    {
        status = read_int("Введите количество строк: ", &rows);
        if (status == INPUT_EOF)
            return 0;

        if (status == INPUT_OK)
        {
            status = read_int("Введите количество столбцов: ", &cols);
            if (status == INPUT_EOF)
                return 0;

            if (status == INPUT_OK &&
                rows >= MIN_SIZE && rows <= MAX_SIZE &&
                cols >= MIN_SIZE && cols <= MAX_SIZE)
                break;
        }

        printf("Неверный размер. Введите числа от %d до %d.\n",
               MIN_SIZE, MAX_SIZE);
    }

    /* Выбор символов игроков */
    while (1)
    {
        status = read_symbol("Символ игрока 1: ", &player1);
        if (status == INPUT_EOF)
            return 0;
        if (status != INPUT_OK)
        {
            printf("Неверный символ. Введите один видимый ASCII-символ.\n");
            continue;
        }

        status = read_symbol("Символ игрока 2: ", &player2);
        if (status == INPUT_EOF)
            return 0;
        if (status != INPUT_OK)
        {
            printf("Неверный символ. Введите один видимый ASCII-символ.\n");
            continue;
        }

        if (player1 != player2)
            break;

        printf("У игроков должны быть разные символы.\n");
    }

    char **board = create_world(rows, cols);

    if (board == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    int current_player = 1;

    while (1)
    {
        print_world(board, rows, cols);

        char symbol = (current_player == 1) ? player1 : player2;

        printf("Ход игрока %d (%c)\n", current_player, symbol);

        int row, col;

        while (1)
        {
            status = read_int("Введите строку: ", &row);
            if (status == INPUT_EOF)
            {
                free_world(board, rows);
                return 0;
            }
            if (status != INPUT_OK)
            {
                printf("Неверный ввод. Попробуйте снова.\n");
                continue;
            }

            status = read_int("Введите столбец: ", &col);
            if (status == INPUT_EOF)
            {
                free_world(board, rows);
                return 0;
            }
            if (status != INPUT_OK)
            {
                printf("Неверный ввод. Попробуйте снова.\n");
                continue;
            }

            row--;
            col--;

            if (row < 0 || row >= rows ||
                col < 0 || col >= cols)
            {
                printf("Координаты вне поля. Строка: 1-%d, столбец: 1-%d.\n",
                       rows, cols);
                continue;
            }

            if (board[row][col] != ' ')
            {
                printf("Эта клетка уже занята.\n");
                continue;
            }

            break;
        }

        board[row][col] = symbol;

        if (check_winner(board, rows, cols, &winner))
        {
            print_world(board, rows, cols);

            printf("Игрок %d (%c) победил!\n", current_player, winner);

            break;
        }

        if (check_draw(board, rows, cols))
        {
            print_world(board, rows, cols);

            printf("Ничья!\n");

            break;
        }

        current_player = (current_player == 1) ? 2 : 1;
    }

    free_world(board, rows);

    return 0;
}
