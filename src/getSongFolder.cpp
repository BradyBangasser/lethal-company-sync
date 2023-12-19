#define WIN32_LEAN_AND_MEAN
#include "getSongFolder.hpp"
#include "writeFileData.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c

template <typename ...T>
void error(const char *format, T... formatArgs) {
    printf(format, formatArgs...);

    WSACleanup();

    scanf("");
    exit(1);
}

const char *getSongFolder(const char *url, const char *port) {
    char *zipFilePath;

    struct addrinfo *result = NULL, *ptr = NULL, hints;
    int wsaResults;
    SOCKET sockfd = INVALID_SOCKET;

    const char *message = "";

    // Why does windows have to be special
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    WSAData wsaData;
    wsaResults = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (wsaResults != 0) {
        error("Windows failed again: %d\n", wsaResults);
    }

    wsaResults = getaddrinfo("google.com", "80", &hints, &result);

    if (wsaResults != 0) {
        error("Failed to get address information: %d\n", wsaResults);
    }

    SOCKET sock = INVALID_SOCKET;

    printf("Attempting to connect...\n");

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (sock == INVALID_SOCKET) continue; 

        wsaResults = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);

        // Change this so it tries all of the returned addresses from getaddrinfo
        if (wsaResults == SOCKET_ERROR) {
            closesocket(sock);
            sock = INVALID_SOCKET;
            continue;
        } 
    }

    freeaddrinfo(result);

    if (sock == INVALID_SOCKET) {
        error("Error connecting to server: %d", WSAGetLastError());
    }

    printf("Connected\n");

    int resLen = DEFAULT_BUF_LEN;
    char resBuf[DEFAULT_BUF_LEN];

    wsaResults = send(sock, message, (int) strlen(message), 0);

    if (wsaResults == SOCKET_ERROR) {
        closesocket(sock);
        error("Failed to send data: %d", WSAGetLastError());
    }

    wsaResults = shutdown(sock, SD_SEND);

    if (wsaResults == SOCKET_ERROR) {
        closesocket(sock);
        error("Failed to shutdown socket: %d", WSAGetLastError());
    }

    do {
        wsaResults = recv(sock, resBuf, resLen, 0);

        if (wsaResults < 0) {
            error("Res failed: %d", WSAGetLastError());
        }
    } while (wsaResults != 0);

    wsaResults = shutdown(sock, SD_SEND);

    if (wsaResults == SOCKET_ERROR) {
        closesocket(sock);
        error("Failed to shutdown socket: %d", WSAGetLastError());
    }

    writeFileData("data", resBuf);

    closesocket(sock);
    WSACleanup();

    return zipFilePath; 
}