#ifndef LCS_LS_FORMAT_H
#define LCS_LS_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

struct LSFValue {
    char *key;
    char *value;
    struct LSFValue *next;
};

struct LSFValue *parseLSFFile(const char *path, int *len);
struct LSFValue *parseLSFString(const char *str, int *len);
void freeLSFValues(struct LSFValue *values);
int appendLSFValue(struct LSFValue *values, const char *key, const char *value);
int writeLSFFile(const char *path, const struct LSFValue *values);

#ifdef __cplusplus
}
#endif

#endif