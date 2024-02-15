#include "files.hpp"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include "../constants.hpp"

// This will be set to 1 if the checkSystemFiles has been run
static int systemFilesVerified = 0;

/**
 * @brief Checks if a folder exists, if it doesn't, it creates it
 * 
 * @param subpath subpath of the folder in question, it will be appended to @ref PROGRAM_FILES
 * @return 1 if error, 0 if ok
 */
int _verifyFolder(const char *subpath) {
    static char path[PATH_MAX];
    sprintf(path, "%s\\%s", PROGRAM_FILES, subpath);
    
    struct stat s = {0};
    if (stat(path, &s) == -1) {
        if (mkdir(path) != 0) {
            return 1;
        }
    }

    return 0;
}

int checkSystemFiles() {
    if (systemFilesVerified) return 0;

    struct stat s = {0};
    char infoPath[PATH_MAX];

    sprintf(infoPath, "%s\\%s", PROGRAM_FILES, "info.txt");

    // Verify folder will check if the folder exists and create it otherwise, returns 0 on success 1 on error
    if (_verifyFolder("")) return -1;
    if (_verifyFolder("tmp")) return -1;
    if (_verifyFolder("cache")) return -1;
    if (_verifyFolder("installs")) return -1;

    if (stat(infoPath, &s) == -1) {
        if (mkInfo(infoPath) != 0) return -1;
    }

    systemFilesVerified = 1;

    return 0;
}

const char *checkInstall(const char *id) {

    // GID: {6 hex characters}
    // MID: GIDXXX:{56 hex character}
    // MPID: GIDXXX:{8 hex character

    size_t result, len;
    char gameId[7], *subId;

    len = strlen(id);


    result = checkSystemFiles();

    if (result != 0) return NULL;

    

    return "";
}