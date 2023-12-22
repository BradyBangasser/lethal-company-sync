#ifndef WRITE_FILE_DATA_H
#define WRITE_FILE_DATE_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
    Writes data to a file
    fileName, data, dataLen
    returns 0 if success
*/
int writeFileData(const char *, char *, size_t);

/*
    Write data to a file, but opens file in append mode, will clear file if clear arg is 1
    fileName, data, dataLen, clear
    returns 0 if success
*/
int writePartData(const char *, char *, size_t, short);


#ifdef __cplusplus
}
#endif

#endif