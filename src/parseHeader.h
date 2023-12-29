#ifndef PARSE_HEADER_H
#define PARSE_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

struct Header {
    unsigned long long contentLen, contentStart, headerLen, headerRawLen;
    unsigned short headerComplete;
    unsigned int status;
    const char *rawHeader, *contentType, **headers;
};

/*
    Data, Data Length, Header struct
    parses the header from raw http request
    returns 0 if ok
*/
int parseHeader(const char *, int, struct Header *);

/*
    Header struct
    Frees the memory malloced by parseHeader
    returns 0 if ok
*/
int freeHeader(struct Header *);

/*
    Header struct, header name
    Gets the value of a header from a header struct
    returns value of header if ok and NULL otherwise
*/
const char *getHeader(struct Header *, const char *);

#ifdef __cplusplus 
}
#endif

#endif