#ifndef LOAD_FILES_INTO_COMPANY
#define LOAD_FILES_INTO_COMPANY

#define UNZIP_BUFFER_SIZE 8192
#define CASE_SENSITIVITY 0
#define MAX_FILE_NAME_LENGTH 512

#ifdef _WIN32
    #define USEWIN32IOAPI
    #include "iowin32.h"
#endif

#if (!defined(_WIN32) && !defined(WIN32) && !defined(__APPLE__))
    #ifndef __USE_FILE_OFFSET64
        #define __USE_FILE_OFFSET64
    #endif

    #ifndef __USE_LARGEFILE64
        #define __USE_LARGEFILE64
    #endif

    #ifndef _LARGEFILE64_SOURCE
        #define _LARGEFILE64_SOURCE
    #endif

    #ifndef _FILE_OFFSET_BIT
        #define _FILE_OFFSET_BIT
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
    downloaded file path, unzip path
    This function will unzip the downloaded file and copy all files to their respective directories 
*/
int loadFilesIntoCompany(const char *, const char *);

#ifdef __cplusplus
}
#endif

#endif