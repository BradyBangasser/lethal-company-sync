#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>
#include <stdint.h>
#include <openssl/evp.h>

#ifdef __cplusplus
extern "C" {
#endif

// Base64 encode/decode found at https://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c
// See base64.c for more details on the license

unsigned char *base64Encode(const unsigned char *src, size_t len, size_t *outLen);
unsigned char *base64Decode(const unsigned char *src, size_t len, size_t *outLen);

// Hashing and encryption
#define INVALID_ALGORITHM -11
#define ALGORITHM_INIT_ERROR -12
#define ALGORITHM_UPDATE_ERROR -13
#define ALGORITHM_FINAL_ERROR -14

int hash(const EVP_MD *algorithm, uint8_t *buffer, const char *msg, uint32_t *hashLen);

inline int sha224(uint8_t *buffer, const char *msg, uint32_t *hashLen) { return hash(EVP_sha224(), buffer, msg, hashLen); };

#ifdef __cplusplus
}
#endif

#endif