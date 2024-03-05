#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void printHexValues(uint8_t *values, size_t len, char separator) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x%c", values[i], separator);
    }
    printf("\n");
}