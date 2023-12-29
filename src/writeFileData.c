#include "writeFileData.h"
#include <stdio.h>
#include <stddef.h>

int writeFileData(const char *file, char *data, size_t dataLen) {
    return writePartData(file, data, dataLen, 1);
}

int writePartData(const char *file, char *data, size_t dataLen, short clear) {
    printf("Writing %lld bytes to %s\n", dataLen, file);
    FILE *f = fopen(file, (clear == 1) ? "wb" : "ab");

    size_t written = fwrite(data, 1, dataLen, f);

    fclose(f);

    return written;
}