#ifndef GET_SONG_FOLDER_HPP
#define GET_SONG_FOLDER_HPP

#if _WIN32_WINNT < 0x502
#define _WIN32_WINNT 0x502
#endif

#define DEFAULT_SERVER_PORT "27015"
#define DEFAULT_BUF_LEN 4096

const char* getSongFolder(const char *url, const char *port);

#endif