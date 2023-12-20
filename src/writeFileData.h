#ifndef WRITE_FILE_DATA_H
#define WRITE_FILE_DATE_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int writeFileData(const char *file, char *data, size_t dataLen);

#ifdef __cplusplus
}
#endif

#endif