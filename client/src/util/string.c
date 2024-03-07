#include "utils.h"

uint32_t countCharacters(const char *str, char c) {
    uint32_t i, j = 0;
    for (i = 0; str[i]; str[i] == c ? j++ : 0, i++);
    return j;
}