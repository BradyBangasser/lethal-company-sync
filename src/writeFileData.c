#include "writeFileData.h"
#include <stdio.h>
#include <stddef.h>

int writeFileData(const char *file, char *data, size_t dataLen) {
    printf("Writing Data (%lld bytes)\n", dataLen);
    FILE *f = fopen(file, "w");

    fwrite(data, 1, dataLen, f);

    fclose(f);
    return 0;
}

int writePartData(const char *file, char *data, size_t dataLen, short clear) {
    return 1;
}