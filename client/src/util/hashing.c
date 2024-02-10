#include <openssl/evp.h>
#include <openssl/evperr.h>
#include "../constants.hpp"
#include "utils.h"
#include <string.h>
#include <stdint.h>

int hash(const EVP_MD *algorithm, uint8_t *buffer, const char *msg, uint32_t *hashLen) {
    if (algorithm == NULL) return INVALID_ALGORITHM;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    int result;

    result = EVP_DigestInit_ex(ctx, algorithm, NULL);
    if (result == 0) {
        EVP_MD_CTX_free(ctx);
        return ALGORITHM_INIT_ERROR;
    }

    result = EVP_DigestUpdate(ctx, msg, strlen(msg));
    if (result == 0) {
        EVP_MD_CTX_free(ctx);
        return ALGORITHM_UPDATE_ERROR;
    }

    result = EVP_DigestFinal_ex(ctx, buffer, hashLen);

    EVP_MD_CTX_free(ctx);

    if (result == 0) {
        return ALGORITHM_FINAL_ERROR;
    }

    return OK;
}