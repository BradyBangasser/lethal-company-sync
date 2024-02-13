#ifndef BLIB_HTTP_LIB_H
#define BLIB_HTTP_LIB_H

#include <stdlib.h>
#include <openssl/ssl.h>
#include "./blib_constants.h"

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <ws2tcpip.h>
#endif

#ifndef BLIB_HTTP_VERSION
// This is the version of HTTP that Blib will use for requests
// I plan to support 1.1 as soon as I figure out 
#define BLIB_HTTP_VERSION "1.0"
#endif

#ifdef __cplusplus
extern "C" {
#endif

// This represents a HTTP message header
struct Blib_Header {
    // Header name
    const char *name;
    // Header value
    const char *value;
};

struct Blib_Response_Header {
    const unsigned short int status;
    const char *statusMsg;
    const char *raw;
    const struct Blib_Header *parsedHeaders;

    const size_t numberOfHeader;
    const size_t headerLen;
};

struct UrlInfo {
    char *url;
    char *host;
    char *path;
    char *proto;
    struct addrinfo *addrInfo;
};

struct Blib_Response {
    /*
        The message sent to the server by the request
    */
    const char *httpMessage;
    struct Blib_Response_Header* header;
    const char *content;
};

/*
    This inits winsock
    Can be used on any OS
*/
inline void initWindows() {
    #ifdef _WIN32
    // Why windows why
    struct WSAData winData;
    WSAStartup(MAKEWORD(2,2), &winData);
    #endif
}

/*
This cleanup winsock
Can be used on any OS
*/
inline void cleanupWindows() {
    #ifdef _WIN32
    WSACleanup();
    #endif
}

/*
    This function converts the Blib_Header struct into a string to put into an http message
    Adds \r\n to the end of the header
    You need to call freeHeaderString when done
    returns a string in the following format: "name: value\r\n"
*/
const char *createHeaderString(struct Blib_Header *);

/*
    Frees the memeory alloced by createHeaderString
*/
void freeHeaderString(const char **);

/*
    buf, HTTP method, path, host, headers, number of headers, msg
    Creates an HTTP message to send to a server, it takes care of memory allocing
    call freeHttpMsg when done
    Buf will be the msg string on success and NULL on failure
    returns 0 on success and  <0 on failure
*/
int createHttpMsg(char **, const char *, const char *, const char *, struct Blib_Header *, size_t, const char *);

/*
    buf
    Frees the memory allocated by createHttpMsg
*/
void freeHttpMsg(char **);

/*
    address information
    create a network socket
    You must call cleanupSock when done
    return socket descripter or -1 if the socket initation fails
*/
int initSock(struct addrinfo *);

/*
    pointer to sock
    shutsdown and free the socket
*/
void cleanupSock(int);

/*
    Init the openssl library 
    Pointer to ssl and ssl_ctx struct
    if this fails, ssl and ssl_ctx will be set to null
    returns 0 on success, -1 on ctx err, -2 on ssl err, and -3 on fd error
*/
int initSSL(int sock, SSL **, SSL_CTX **);

/*
    ssl, ssl ctx
    frees up the ssl and ssl ctx memory
*/
void cleanupSSL(SSL **, SSL_CTX **);

/*
    host, port
    gets the addrinfo
    supports all operating systems
    returns a pointer to the addrinfo struct
*/
struct addrinfo *blibGetAddrInfo(const char *, const char *);

/*
    addrinfo pointer
    frees the addr info and sets the address to null
*/
void blibFreeAddrInfo(struct addrinfo **);

/*
    url
    This will parse a url
    returns a pointer to a UrlInfo struct
    You must call freeUrlInfo when done with the url info
*/
struct UrlInfo *getUrlInfo(const char *);

/*
    Takes in a pointer to a UrlInfo struct
    Attempts to free it if it isn't null and then sets the val to null
*/
void freeUrlInfo(struct UrlInfo **);

/*

*/
struct Blib_Response_Header *parseResponseHeader(const char *);

/*

*/
void freeResponseHeader(struct Blib_Response_Header **);

/*
    TBI
*/
int getErrorCode();

/*
    TBI
*/
const char *getErrorMsg();

/*
    Get the value of a header from a response 
    returns the string value or NULL
*/
const char *getHeaderValue(const struct Blib_Response_Header *, const char *);

#ifdef __cplusplus
}
#endif

#endif