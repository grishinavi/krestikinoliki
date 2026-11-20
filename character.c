#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "character.h"

// Читаем строку, чтобы избежать багов со scanf
static int read_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return INPUT_EOF;
    }
    // Если ввели слишком много, чистим буфер
    if (strchr(buffer, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return INPUT_OK;
}

int read_int(const char *message, int *value) {
    char buffer[100];
    char *end;
    long num;

    printf("%s", message);
    if (read_line(buffer, sizeof(buffer)) == INPUT_EOF) {
        return INPUT_EOF;
    }

    num = strtol(buffer, &end, 10); 

    // Проверка, что ввели именно число
    if (end == buffer || (*end != '\n' && *end != '\0')) {
        return INPUT_INVALID;
    }

    *value = (int)num;
    return INPUT_OK;
}

int read_symbol(const char *message, char *symbol) {
    char buffer[100];

    printf("%s", message);
    if (read_line(buffer, sizeof(buffer)) == INPUT_EOF) {
        return INPUT_EOF;
    }

    // Проверяем, что ввели ровно один символ
    if (buffer[0] == '\n' || buffer[0] == '\0') {
        return INPUT_INVALID;
    }
    if (buffer[1] != '\n' && buffer[1] != '\0') {
        return INPUT_INVALID;
    }
    if (!isprint(buffer[0]) || isspace(buffer[0])) {
        return INPUT_INVALID;
    }

    *symbol = buffer[0];
    return INPUT_OK;
}
