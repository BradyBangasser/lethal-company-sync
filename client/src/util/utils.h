#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>

#ifdef c_plus_plus
extern "C" {
#endif

// Base64 encode/decode found at https://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c
// See base64.c for more details on the license

unsigned char *base64Encode(const unsigned char *src, size_t len, size_t *outLen);
unsigned char *base64Decode(const unsigned char *src, size_t len, size_t *outLen);

#ifdef c_plus_plus
}
#endif

#endif