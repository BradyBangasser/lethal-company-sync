#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants.hpp"
#include "files.hpp"

#define INFO_FORMAT "LCS Info:\nversion: %s"

int mkInfo(const char *path) {
    size_t result, infoLen;
    char *info;
    FILE *f = fopen(path, "w");

    if (f == NULL) {
        return -1;
    }

    infoLen = snprintf(NULL, 0, INFO_FORMAT, LCS_VERSION);
    infoLen++;
    info = malloc(sizeof(char) * infoLen);


    if (info == NULL) {
        fclose(f);
        remove(path);
        return -2;
    }

    snprintf(info, infoLen, INFO_FORMAT, LCS_VERSION);

    result = fwrite(info, sizeof(char), infoLen, f);

    free(info);
    fclose(f);

    if (result <= 0) {
        return -2;
    } else {
        return 0;
    }
}