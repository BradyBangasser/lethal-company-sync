// C:\Users\2024b\AppData\Roaming\Thunderstore Mod Manager\DataFolder

#include "loadFilesIntoCompany.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <zlib.h>
#include <direct.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#include "unzip.h"

int mkd(const char *path) {
    return _mkdir(path);
}

int makedir(const char *path) {
    char *buf;
    char *p;
    size_t pathLen = strlen(path);

    if (pathLen == 0)
        return 0;

    buf = (char *) malloc(pathLen + 1);
    if (buf == NULL) {
        printf("No memory :(\n");
        return -1;
    }

    strcpy(buf, path);

    if (buf[pathLen - 1] == '/')
        buf[pathLen - 1] = '\0';

    if (mkd(buf) == 0) {
        free(buf);
        return 1;
    }

    // attempts to make sub directories

    p = buf + 1;

    while (1) {
        char hold;
        while (*p && *p != '\\' && *p != '/') p++;
        hold = *p;
        *p = 0;
        if ((mkd(buf) == -1) && (errno == ENOENT))
        {
            printf("Couldn't make dir\n");
            free(buf);
            return 0;
        }

        if (hold == 0)
            break;

        *p++ = hold;
    }

    free(buf);
    return 1;
}

int extractCurrentFile(unzFile file) {
    char infName[256];
    char *fnameWOPath;
    char *curs;

    int err = UNZ_OK;
    FILE *fout = NULL;

    void *buf;
    uInt bufSize;

    unz_file_info64 fileInfo;
    err = unzGetCurrentFileInfo64(file, &fileInfo, infName, sizeof(infName), NULL, 0, NULL, 0);

    printf("extracting: %s\n", infName);

    if (err != UNZ_OK) {
        printf("Error getting current file info %d\n", err);
        return err;
    }

    bufSize = UNZIP_BUFFER_SIZE;
    buf = (void *) malloc(bufSize);
    if (buf == NULL) {
        printf("No memory :(\n");
        return UNZ_INTERNALERROR;
    }

    curs = fnameWOPath = infName;

    while ((*curs) != '\0') {
        if ((*curs) == '\\' || (*curs) == '/') {
            fnameWOPath = curs + 1;
        }
        curs++;
    }

    if ((*fnameWOPath) == '\0') {
        makedir(infName);
    } else {
        fout = fopen(infName, "wb");

        if (fout == NULL) {
            char c = *(fnameWOPath - 1);
            *(fnameWOPath - 1) = '\0';
            makedir(infName);
            *(fnameWOPath - 1) = c;
            fout = fopen(infName, "wb");
        }

        if (fout == NULL) {
            printf("Couldn't open out file 💀\n");
            return -1;
        }

        err = unzOpenCurrentFile(file);

        if (err != UNZ_OK) {
            printf("error opening file\n");
            return err;
        }

        do {
            err = unzReadCurrentFile(file, buf, bufSize);
            if (err < 0) {
                printf("Error reading current file: %d %s\n", err, infName);
                break;
            }

            if (err > 0) {
                if (fwrite(buf, (unsigned) err, 1, fout) != 1) {
                    printf("Error writing data to file\n");
                    err = UNZ_ERRNO;
                    break;
                }
            }
        } while (err > 0);

        if (fout != NULL) fclose(fout);

        if (err == UNZ_OK) {
            err = unzCloseCurrentFile(file);

            if (err != UNZ_OK) {
                printf("Errr");
                
            }
        } else unzCloseCurrentFile(file);
    }

    free(buf);
    return 0;
}

int extractFolder(unzFile file) {
    uLong i;
    unz_global_info64 gi;
    int err;

    err = unzGetGlobalInfo64(file, &gi);

    if (err != UNZ_OK) {
        printf("Error getting global zip info: %d\n", err);
    }

    for (i = 0; i < gi.number_entry; i++) {
        if (extractCurrentFile(file) != UNZ_OK) {
            break;
        }

        if ((i + 1) < gi.number_entry) {
            err = unzGoToNextFile(file);

            if (err != UNZ_OK) {
                printf("Error going to next file: %d\n", err);
                break;
            }
        }
    }

    return 0;
}

int unzipFolder(const char *dloadPath, const char *inflatePath) {
    char originalCwd[PATH_MAX];
    // Error handling needed here
    getcwd(originalCwd, sizeof(originalCwd));

    unzFile uf;

    zlib_filefunc64_def ffunc;
    fill_win32_filefunc64A(&ffunc);
    uf = unzOpen2_64(dloadPath, &ffunc);

    if (uf == NULL)
    {
        printf("Couldn't open .zip file\n");
        return -1;
    }


    if (chdir(inflatePath) != 0) {
        if (mkdir(inflatePath) != 0 || chdir(inflatePath) != 0) {
            perror("AHHHHH");
            printf("Couldn't access %s", inflatePath);
            return -1;
        }
    }

    extractFolder(uf);

    printf("opened zip bomb\n");

    unzClose(uf);

    if (chdir(originalCwd) != 0) {
        printf("Unable to change cwd back to original\n");
    }

    return 0;
}

int loadFilesIntoCompany(const char *dloadPath, const char *outPath) {
    return unzipFolder(dloadPath, outPath);
}
