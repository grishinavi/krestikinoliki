#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "character.h"

/* Считывает строку; если она длиннее буфера, остаток отбрасывается */
static int read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL)
        return INPUT_EOF;

    if (strchr(buffer, '\n') == NULL)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }

    return INPUT_OK;
}

int read_int(const char *message, int *value)
{
    char buffer[100];
    char *end;

    printf("%s", message);

    int status = read_line(buffer, sizeof(buffer));
    if (status != INPUT_OK)
        return status;

    errno = 0;
    long number = strtol(buffer, &end, 10);

    if (end == buffer || errno != 0 ||
        number > INT_MAX || number < INT_MIN)
        return INPUT_INVALID;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return INPUT_INVALID;

    *value = (int)number;

    return INPUT_OK;
}

int read_symbol(const char *message, char *symbol)
{
    char buffer[100];

    printf("%s", message);

    int status = read_line(buffer, sizeof(buffer));
    if (status != INPUT_OK)
        return status;

    /* Ровно один символ в строке */
    if (buffer[0] == '\0' || buffer[0] == '\n')
        return INPUT_INVALID;

    if (buffer[1] != '\n' && buffer[1] != '\0')
        return INPUT_INVALID;

    unsigned char ch = (unsigned char)buffer[0];

    /* Любой печатный ASCII-символ, кроме пробела */
    if (ch > 127 || !isprint(ch) || isspace(ch))
        return INPUT_INVALID;

    *symbol = (char)ch;

    return INPUT_OK;
}
