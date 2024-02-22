#include <stdio.h>
#include "util/utils.h"
#include "network/network.hpp"
#include <cstdint>
#include <http.hpp>
#include "constants.hpp"
#include "mod/mod.hpp"
#include "fs/files.hpp"
#include <limits.h>
#include "fs/lsf.h"

int init() {
    checkAndInstallSystemFiles();
    return 0;
}

int main() {
    init();
    int len;

    std::string test = "swhsadfgh: sadhfg\nhello: yo";
    
    struct LSFValue *vals = parseLSFString(test.c_str(), &len);

    // struct LSFValue *vals = parseLSFFile("test.lsf", &len);

    // printf("%x %s %s %s\n", vals, vals->next->key, vals->key, vals->value);

    // writeLSFFile("test0.lsf", vals);
    // printf("%x\n", vals);
    // appendLSFValue(vals, "there", "value");
    // writeLSFFile("test.lsf", vals);
    // freeLSFValues(vals);
    return 0;
}