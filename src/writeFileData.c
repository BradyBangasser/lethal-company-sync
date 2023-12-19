#include "writeFileData.h"
#include <stdio.h>

int writeFileData(const char *file, char *data) {
    printf("Writing Data\n");
    FILE *f = fopen(file, "w");

    fwrite(data, 1, sizeof(data), f);

    fclose(f);
    return 0;
}

