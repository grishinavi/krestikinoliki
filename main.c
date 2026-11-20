#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "character.h"

#define MIN_SIZE 2
#define MAX_SIZE 20

int main(void) {
    // Для русского текста в Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif

    int rows, cols, status;
    char player1, player2;
    char **board = NULL;
    int current_player = 1;
    char current_symbol, winner;

    printf("=== крестики-нолики ===\n\n");

    // Ввод размера поля
    while (1) {
        status = read_int("Введите количество строк: ", &rows);
        if (status == INPUT_EOF) return 0;

        status = read_int("Введите количество столбцов: ", &cols);
        if (status == INPUT_EOF) return 0;

        if (status == INPUT_OK && rows >= MIN_SIZE && rows <= MAX_SIZE &&
            cols >= MIN_SIZE && cols <= MAX_SIZE) break;

        printf("Неверный размер. Введите числа от %d до %d.\n", MIN_SIZE, MAX_SIZE);
    }

    // Ввод символов
    while (1) {
        status = read_symbol("Символ игрока 1: ", &player1);
        if (status == INPUT_EOF) return 0;
        if (status != INPUT_OK) {
            printf("Ошибка. Введите один видимый символ.\n");
            continue;
        }

        status = read_symbol("Символ игрока 2: ", &player2);
        if (status == INPUT_EOF) return 0;
        if (status != INPUT_OK) {
            printf("Ошибка. Введите один видимый символ.\n");
            continue;
        }

        if (player1 != player2) break;
        printf("Символы должны быть разными!\n");
    }

    // Создаем игровое поле
    create_world(&board, rows, cols);

    // Главный цикл игры
    while (1) {
        print_world(board, rows, cols);

        current_symbol = (current_player == 1) ? player1 : player2;
        printf("Ход игрока %d (%c)\n", current_player, current_symbol);

        int row, col;

        // Ввод координат
        while (1) {
            status = read_int("Введите строку: ", &row);
            if (status == INPUT_EOF) {
                free_world(board, rows);
                return 0;
            }
            if (status != INPUT_OK) {
                printf("Ошибка ввода. Попробуйте снова.\n");
                continue;
            }

            status = read_int("Введите столбец: ", &col);
            if (status == INPUT_EOF) {
                free_world(board, rows);
                return 0;
            }
            if (status != INPUT_OK) {
                printf("Ошибка ввода. Попробуйте снова.\n");
                continue;
            }

            row--; // Переводим в индексы от 0
            col--;

            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                printf("Вне поля! Строка: 1-%d, Столбец: 1-%d.\n", rows, cols);
                continue;
            }

            if (board[row][col] != ' ') {
                printf("Клетка занята!\n");
                continue;
            }
            break;
        }

        // Ставим символ и проверяем условия
        board[row][col] = current_symbol;

        if (check_winner(board, rows, cols, &winner)) {
            print_world(board, rows, cols);
            printf("Игрок %d (%c) победил!\n", current_player, winner);
            break;
        }

        if (check_draw(board, rows, cols)) {
            print_world(board, rows, cols);
            printf("Ничья!\n");
            break;
        }

        // Меняем игрока
        current_player = (current_player == 1) ? 2 : 1;
    }

    free_world(board, rows);
    return 0;
}
