#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHexValues(uint8_t *values, size_t len, char separator) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x%c", values[i], separator);
    }
    printf("\n");
}

int toHexString(uint8_t *values, size_t len, char *buffer) {
    memset(buffer, 0, len * 2 + 1);
    for (size_t i = 0; i < len; i++) {
        sprintf(buffer, "%s%02x", buffer, values[i]);
    }

    return 0;
}