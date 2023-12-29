#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parseHeader.h"
#include "getSongFolder.hpp"

int parseHeader(const char *data, int dataLen, struct Header *header) {
    unsigned int i;
    unsigned int headerEnd, dataStart;
    const char **headers;
    unsigned int headersLen = 0;
    char *rawHeader = NULL;
    char dataSlice[5];
    dataSlice[sizeof(dataSlice) - 1] = '\0';

    // only do work once lol
    if (header->headerComplete == 1) return 0;

    // Find end of header
    for (i = 4; i < dataLen - 4; i++) {
        memcpy(dataSlice, &data[i], sizeof(dataSlice) - sizeof(char));

        if (!strcmp(dataSlice, "\r\n\r\n")) {
            headerEnd = i - 1;
            dataStart = i + 4;
            rawHeader = malloc(sizeof(char) * (headerEnd + 1));
            memcpy((char *) rawHeader, data, sizeof(char) * (headerEnd + 1));
            header->headerRawLen = strlen(rawHeader);
            break;
        }
    }

    // If the end of the header was found, fill the header struct
    if (rawHeader != NULL) {
        header->rawHeader = rawHeader;

        const char *tmp = rawHeader;
        while ((tmp = strstr(tmp, "\r\n"))) {
            headersLen++;
            tmp++;
        }

        headers = malloc(headersLen * sizeof(const char *));

        const char *token = strtok(rawHeader, "\r\n");
        i = 0;

        while ((token = strtok(NULL, "\r\n"))) {
            headers[i] = token;
            i++;
        }

        header->headers = headers;
        header->headerLen = headersLen;

        header->contentType = getHeader(header, "Content-Type");
        header->contentLen = (unsigned long long) atoi(getHeader(header, "Content-Length"));
        header->contentStart = dataStart;
        header->headerComplete = 1;
    } else {
        free(rawHeader);
        header->headerComplete = 0;
    }

    return 0;
}

int freeHeader(struct Header *header) {
    if (header == NULL) return -2;
    free((void *) header->rawHeader);
    free((void *) header->headers);
    return -1;
}

const char *getHeader(struct Header *header, const char *headerName) {
    unsigned int i;

    for (i = 0; i < header->headerLen; i++) {
        char *token = strtok((char *) header->headers[i], ": ");

        if (strcmp(token, headerName) == 0) {
            // For some reason this had a leading space
            return &strtok(NULL, "")[1];
        }
    }

    return NULL;
}