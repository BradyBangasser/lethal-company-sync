#ifndef GET_SONG_FOLDER_HPP
#define GET_SONG_FOLDER_HPP

#include "env.h"

#if _WIN32_WINNT < 0x502
#define _WIN32_WINNT 0x502
#endif

#define SERVER_PORT "443"
#define SERVER_URL "www.googleapis.com"
#define SERVER_PATH "/drive/v3/files/"
#define METHOD "GET"
#define HTTP_MESSAGE(stream, id) sprintf(stream, "%s %s%s?alt=media&key=%s HTTP/1.1\r\nHost: %s\r\n\r\n", METHOD, SERVER_PATH, id, GOOGLE_API_KEY, SERVER_URL)

#define RCV_BUF_LEN 4096
#define WRITE_BUF_LEN 8 * RCV_BUF_LEN

/*
    Id, outFilePath
    This will try and dowload a google drive file with the id supplied tp the outFilePath
    returns 0 on success
*/
int getSongFolder(const char *, const char *);

#endif