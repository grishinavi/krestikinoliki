#ifndef WORLD_H
#define WORLD_H

char **create_world(int rows, int cols);
void free_world(char **board, int rows);
void print_world(char **board, int rows, int cols);
int check_winner(char **board, int rows, int cols, char *winner);
int check_draw(char **board, int rows, int cols);

#endif
