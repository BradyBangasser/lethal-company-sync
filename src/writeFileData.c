#include "writeFileData.h"
#include <stdio.h>
#include <stddef.h>

int writeFileData(const char *file, char *data, size_t dataLen) {
    printf("Writing Data (%d bytes)\n", dataLen);
    FILE *f = fopen(file, "w");

    fwrite(data, 1, dataLen, f);

    fclose(f);
    return 0;
}

