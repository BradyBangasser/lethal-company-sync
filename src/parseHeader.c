#include <stdio.h>

#include "parseHeader.h"
#include "getSongFolder.hpp"

int parseHeader(const char *stream, int streamLen, struct Header *header) {
    int i;

    for (i = 0; i < streamLen; i++) {
        printf("%c", stream[i]);
    }   

    return 0;
}