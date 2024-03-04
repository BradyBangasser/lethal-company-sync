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