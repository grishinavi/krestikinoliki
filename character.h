#ifndef CHARACTER_H
#define CHARACTER_H

/* Коды возврата функций ввода */
#define INPUT_OK 1
#define INPUT_INVALID 0
#define INPUT_EOF -1

int read_int(const char *message, int *value);
int read_symbol(const char *message, char *symbol);

#endif
