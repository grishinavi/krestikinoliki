#ifndef WORLD_H
#define WORLD_H

// Создание, удаление и отрисовка поля
void create_world(char ***board, int rows, int cols);
void free_world(char **board, int rows);
void print_world(char **board, int rows, int cols);

// Проверки на победу и ничью
int check_winner(char **board, int rows, int cols, char *winner);
int check_draw(char **board, int rows, int cols);

#endif
