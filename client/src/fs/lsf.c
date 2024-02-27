#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/utils.h"
#include "lsf.h"

struct LSFValue *_parseLSFLine(const char *line, struct LSFValue *prev) {
    struct LSFValue *builder;
    char *sub;
    size_t l;

    builder = malloc(sizeof(struct LSFValue));
    if (builder == NULL) {
        // scream
        return NULL;
    }

    if (line == NULL) {
        return NULL;
    }

    sub = strchr(line, ':');

    l = sub - line;
    builder->key = malloc((l + 1) * sizeof(char));

    if (builder->key == NULL) {
        free(builder);
        return NULL;
    }

    strncpy(builder->key, line, l);
    builder->key[l] = '\0';

    sub += 2;
    l = strlen(sub);
    builder->value = malloc((l + 1) * sizeof(char));

    if (builder->value == NULL) {
        free(builder->key);
        free(builder);
        return NULL;
    }

    strcpy(builder->value, sub);

    builder->next = NULL;

    if (prev != NULL) prev->next = builder;

    return builder;
}

struct LSFValue *parseLSFFile(const char *path, int *len) {
    char buf[1024] = { 0 }, *ret = (char *) 1;
    FILE *f = fopen(path, "r");
    struct LSFValue *values = NULL, *curs = NULL;

    while (ret != 0) {
        ret = fgets(buf, 1024, f);
        if (ret == NULL) break;

        if (values == NULL) {
            values = _parseLSFLine(buf, NULL);

            if (values == NULL) {
                return NULL;
            }

            curs = values;
        } else {
            if (_parseLSFLine(buf, curs) == NULL) {
                freeLSFValues(values);
                return NULL;
            }

            curs = curs->next;
        }
    }

    return values;
}

// Rewrite to use _parseLSFLine
struct LSFValue *parseLSFString(const char *str, int *len) {
    char *tok, *strc;
    struct LSFValue *values = NULL, *curs = NULL, *ret = NULL;
    size_t l;

    l = strlen(str);
    strc = calloc((l + 1), sizeof(char));
    strcpy(strc, str);
    tok = strtok(strc, "\n");

    do {
        if (tok == NULL) break;

        if (values == NULL) {
            values = _parseLSFLine(tok, NULL);

            if (values == NULL) {
                return NULL;
            }

            curs = values;
        } else {
            ret = _parseLSFLine(tok, curs);

            if (ret == NULL) {
                freeLSFValues(values);
                return NULL;
            }

            curs = ret;
        }
    } while ((tok = strtok(NULL, "\n")));

    free(strc);

    return values;
}

struct LSFValue *createLSFValue(const char *key, const char *val) {
    size_t l;

    struct LSFValue *builder = malloc(sizeof(struct LSFValue));
    if (builder == NULL) {
        return NULL;
    }

    l = strlen(key);
    builder->key = malloc((l + 1) * sizeof(char));

    if (builder->key == NULL) {
        free(builder);
        return NULL;
    }

    strcpy(builder->key, key);

    l = strlen(val);
    builder->value = malloc((l + 1) * sizeof(char));

    if (builder->value == NULL) {
        free(builder->key);
        free(builder);
        return NULL;
    }

    strcpy(builder->value, val);

    builder->next = NULL;

    return builder;
}

int appendLSFValue(struct LSFValue *lsfValues, const char *key, const char *value) {
    struct LSFValue *curs, *builder;
    size_t l;
    builder = malloc(sizeof(struct LSFValue));

    if (builder == NULL) {
        return -1;
    }

    l = strlen(key);
    builder->key = calloc((l + 1), sizeof(char));

    if (builder->key == NULL) {
        free(builder);
        return -1;
    }

    strcpy(builder->key, key);

    l = strlen(value);
    builder->value = calloc((l + 1), sizeof(char));

    if (builder->value == NULL) {
        free(builder->key);
        free(builder);
        return -1;
    }

    strcpy(builder->value, value);

    builder->next = NULL;

    if (lsfValues == NULL) {
        lsfValues = builder;
    }

    curs = lsfValues;
    while (curs->next != NULL) {
        curs = curs->next;
    }

    curs->next = builder;

    return 0;
}

void freeLSFValues(struct LSFValue *lsfValues) {
    struct LSFValue *curs = lsfValues;

    while (lsfValues != NULL) {
        free(lsfValues->key);
        free(lsfValues->value);
        curs = lsfValues->next;
        free(lsfValues);
        lsfValues = curs;
    }
}

int writeLSFFile(const char *path, const struct LSFValue *lsfValues) {
    if (lsfValues == NULL) return -1;
    const struct LSFValue *curs = lsfValues;

    FILE *f = fopen(path, "w");

    if (f == NULL) {
        return -1;
    }

    while (curs != NULL) {
        fputs(curs->key, f);
        fputs(": ", f);
        fputs(curs->value, f);
        fputs("\n", f);
        curs = curs->next;
    }

    fclose(f);

    return 0;
}