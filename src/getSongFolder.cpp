#define WIN32_LEAN_AND_MEAN
#include "getSongFolder.hpp"
#include "writeFileData.h"
#include "parseHeader.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// #pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment (lib, "AdvApi32.lib")

// https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c

template <typename ...T>
void error(const char *format, T... formatArgs) {
    printf(format, formatArgs...);

    WSACleanup();
}

// Add req status checking to make sure that the request is good
int getSongFolder(const char *id, const char *outFilePath) {
    // Why does windows have to be special
    // I also don't know why I didn't just use system("curl")
    
    int wsaResult;
    int i = 0;
    unsigned int curs = i;
    // Make this better
    char msg[256];
    char writeData[WRITE_BUF_LEN];
    char buf[RCV_BUF_LEN];

    WSAData wsaData;
    struct addrinfo *result = NULL, hints;
    SOCKET sock = INVALID_SOCKET;

    struct Header header = {};
    unsigned int writes = 0, bytesReceived = 0;
    // Create the HTTP message
    HTTP_MESSAGE(msg, id);

    // Set request hints
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // start windows request stuff
    wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (wsaResult != 0) {
        error("Windows failed again: %d\n", WSAGetLastError());
    }

    // Get the address information, uses port 443 because it it doing https
    // SERVER_URL is defined in the header
    wsaResult = getaddrinfo(SERVER_URL, "443", &hints, &result);

    if (wsaResult != 0) {
        error("Failed to get addr info: %d\n", WSAGetLastError());
    }

    // Create the socket
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (sock == INVALID_SOCKET) {
        freeaddrinfo(result);
        error("Error creating socket\n");
    }

    // Connects the socket, 
    // make this attempt multiple addresses
    wsaResult = connect(sock, result->ai_addr, result->ai_addrlen);

    if (wsaResult != 0) {
        freeaddrinfo(result);
        error("Error connecting http socket: %d\n", wsaResult);
        return wsaResult;
    }

    // Init ssl
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    SSL_CTX *sslContext = SSL_CTX_new(SSLv23_client_method());

    SSL *ssl = SSL_new(sslContext);

    SSL_set_fd(ssl, sock);


    wsaResult = SSL_connect(ssl);
    if (wsaResult < 0) {
        ERR_print_errors_fp(stdout);
        freeaddrinfo(result);
        closesocket(sock);
        SSL_free(ssl);
        SSL_CTX_free(sslContext);
        error("Error connecting socket %i\n", wsaResult);
        return wsaResult;
    }

    freeaddrinfo(result);

    wsaResult = SSL_write(ssl, msg, strlen(msg));

    if (wsaResult == SOCKET_ERROR) {
        ERR_print_errors_fp(stderr);
        closesocket(sock);
        SSL_free(ssl);
        SSL_CTX_free(sslContext);
        error("Failed to send data:\n", wsaResult);
        return wsaResult;
    }

    printf("Sent request\n");

    do {
        wsaResult = SSL_read(ssl, buf, sizeof(buf));

        if (wsaResult < 0) {
            error("Error reading SSL data: %d\n", wsaResult);
            freeHeader(&header);
            return wsaResult;
        } else if (wsaResult == 0) break;

        i = 0;

        while (i < wsaResult) {
            if (curs >= sizeof(writeData)) {
                if (header.headerComplete != 1) error("Header is too big lol");
                if (writes == 0) {
                    if (writePartData(outFilePath, &writeData[header.contentStart], curs - 4 - header.headerRawLen, 1) < 0) {
                        freeHeader(&header);
                        error("Error writing data1\n");
                        return -1;
                    }
                } else {
                    if (writePartData(outFilePath, writeData, curs, 0) < 0) {
                        freeHeader(&header);
                        error("Error writing data2\n");
                        return -1;
                    }
                }
                writes++;

                curs = 0;
            }

            writeData[curs] = buf[i];
            curs++;
            i++;
            bytesReceived++;
        }

        int result = parseHeader(writeData, curs, &header);

        if (result != 0) {
            error("Error parsing header: %d\n", result);
            return result;
        }
    } while (header.headerComplete != 1 || (header.contentLen + header.headerRawLen + 4) > bytesReceived);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(sslContext);
    shutdown(sock, SD_BOTH);
    closesocket(sock);

    WSACleanup();
    freeHeader(&header);

    if (writePartData(outFilePath, writeData, curs, 0) < 0) {
        error("Error writing data\n");
        return -1;
    }

    return 0; 
}