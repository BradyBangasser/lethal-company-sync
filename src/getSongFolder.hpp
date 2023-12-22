#ifndef GET_SONG_FOLDER_HPP
#define GET_SONG_FOLDER_HPP

#define _WIN32_WINNT 0x502
#define DEFAULT_SERVER_PORT "27015"
#define DEFAULT_BUF_LEN 1024

const char* getSongFolder(const char *url, const char *port);

#endif