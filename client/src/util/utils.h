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

// Hex
void printHexValues(uint8_t *values, size_t len, char separator);
int toHexString(uint8_t *values, size_t len, char *buffer);

// Hashing and encryption
#define INVALID_ALGORITHM -11
#define ALGORITHM_INIT_ERROR -12
#define ALGORITHM_UPDATE_ERROR -13
#define ALGORITHM_FINAL_ERROR -14
#define FAILED_TO_OPEN_FILE -20

int hash(const EVP_MD *algorithm, uint8_t *buffer, const char *msg, uint32_t *hashLen);
int hashFile(const EVP_MD *algorithm, uint8_t *buffer, const char *filePath, uint32_t *hashLen);

/*
    Uses the sha224 algorithm to hash a msg, buffer should be 28 characters long
*/
inline int sha224(uint8_t *buffer, const char *msg, uint32_t *hashLen) { return hash(EVP_sha224(), buffer, msg, hashLen); }
inline int sha512(uint8_t *buffer, const char *msg, uint32_t *hashLen) { return hash(EVP_sha512(), buffer, msg, hashLen); }

inline int fsha512(uint8_t *buffer, const char *filePath, uint32_t *hashLen) { return hashFile(EVP_sha512(), buffer, filePath, hashLen); }

// String stuff
uint32_t countCharacters(const char *str, char c);

#ifdef __cplusplus
}
#endif

#endif