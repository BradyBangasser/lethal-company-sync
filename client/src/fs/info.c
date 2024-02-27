#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants.hpp"
#include "files.hpp"
#include "lsf.h"

int mkInfo(const char *path) {
    struct LSFValue *vals = createLSFValue("version", LCS_VERSION);
    writeLSFFile(path, vals);
    freeLSFValues(vals);
    return 0;
}