#include "files.hpp"
#include "../constants.hpp"

#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int mkSubDirs(const char *path) {
    char mpath[PATH_MAX], pathBuilder[PATH_MAX] = { 0 };
    char *curs;
    static char separtator[2] = { PATH_SLASH, 0 };
    size_t i = 0, len = strlen(path);

    if (len > PATH_MAX - 1) {
        return -1;
    }

    strcpy(mpath, path);

    curs = strtok(mpath, separtator);

    if (curs == NULL) {
        return 1;
    }

    strcpy(pathBuilder, curs);

    // Will create all but last file
    do {
        // Check if the path is C:\\ or / but only on the first iteration, if not, attempt to make the dir
        if (i++ == 0 && (strcmp(pathBuilder, "C:") == 0 || strcmp(pathBuilder, "") == 0)) {
            continue;
        } else {
            if (mkdir(pathBuilder) != 0) {
                if (errno != EEXIST) return -1;
            }
            sprintf(pathBuilder, "%s%c%s", pathBuilder, PATH_SLASH, curs);
        }
    } while (curs = strtok(NULL, separtator), curs != NULL);

    return 0;
}

// TODO, add error checking
int fcopy(const char *from, const char *to) {
    int result;
    size_t n;
    char buffer[4096];

    result = mkSubDirs(to);

    if (result != 0) {
        return -1;
    }

    FILE *t = fopen(to, "w");

    if (t == NULL) {
        return -2;
    }

    FILE *f = fopen(from, "r");
    if (f == NULL) {
        fclose(t);
        return -3;
    }

    while ((n = fread(buffer, 1, sizeof(buffer), f))) {
        fwrite(buffer, 1, sizeof(buffer), t);
    }

    fclose(f);
    fclose(t);

    return 0;
}