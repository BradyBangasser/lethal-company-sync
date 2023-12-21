#define WIN32_LEAN_AND_MEAN
#include "getSongFolder.hpp"
#include "writeFileData.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c

template <typename ...T>
void error(const char *format, T... formatArgs) {
    printf(format, formatArgs...);

    WSACleanup();

    printf("\n\npress any key...");
    getchar();
    exit(1);
}

const char *getSongFolder(const char *url, const char *port) {
    // Why does windows have to be special
    
    int wsaResult;
    char msg[80];
    
    sprintf(msg, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: keep-alive\r\n\r\n", url);

    // malloc this
    char data[65534];

    WSAData wsaData;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET sock = INVALID_SOCKET;

    // Set request hints
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // start windows request stuff
    wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (wsaResult != 0) {
        error("Windows failed again: %d", WSAGetLastError());
    }

    wsaResult = getaddrinfo(url, "80", &hints, &result);

    if (wsaResult != 0) {
        error("Failed to get addr info: %d", WSAGetLastError());
    }

    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (sock == INVALID_SOCKET) {
        freeaddrinfo(result);
        error("Error creating socket");
    }

    // make this attempt multiple addresses
    if (connect(sock, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR) {
        freeaddrinfo(result);
        closesocket(sock);
        error("Error connecting socket: ", WSAGetLastError());
    }

    freeaddrinfo(result);

    printf("Sending request to %s\n", url);

    wsaResult = send(sock, msg, strlen(msg), 0);

    if (wsaResult == SOCKET_ERROR) {
        closesocket(sock);
        error("Failed to send data: ", WSAGetLastError());
    }

    printf("Sent request\n");

    char buf[DEFAULT_BUF_LEN];
    int i = 0;
    int curs = i;
    int test = 0;

    // Get length out of header
    do {
        printf("Attempting to receive data\n");
        wsaResult = recv(sock, buf, sizeof(buf), 0);

        if (wsaResult < 0) {
            error("AHHHHHHHHHH: %d", WSAGetLastError());
        } else if (wsaResult == 0) break;

        printf("Receiving data... (%d)\n", wsaResult);

        test++;
        i = 0;

        printf("\n%c\n", buf[wsaResult - 1]);

        while (i < wsaResult && (buf[i] == '\n' || buf[i] == '\r' || buf[i] >= 32)) {
            data[curs] = buf[i];
            curs++;
            i++;
        }

        // Fix this
        if (wsaResult < DEFAULT_BUF_LEN) break;
    } while (wsaResult > 0);

    printf("Writing Data\n");


    writeFileData("data.txt", data, curs);

    closesocket(sock);
    WSACleanup();

    return url; 
}