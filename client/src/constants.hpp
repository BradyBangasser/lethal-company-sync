#ifndef LCS_CONSTANTS_HPP
#define LCS_CONSTANTS_HPP

#define LCS_VERSION "0.1"

// ____Id Stuff____
#define LCS_GID_LENGTH 6
#define LCS_MID_LENGTH 56
#define LCS_MPID_LENGTH 8

// ____C Return Types____
#define LCS_NOT_IMPLEMENTED_YET -99999
#define LCS_OK 1

// ____C Networking Stuff____
#define LCS_SERVER_URL "http://849f90976f6f2afae5fb990635c67915.serveo.net"

// ____File Constants____
#define LCS_PROGRAM_FILES "C:\\lcs"
#define LCS_INSTALLS_FOLDER "installs"
#define LCS_TMP_FOLDER "tmp"
#define LCS_CACHE_FOLDER "cache"
#define LCS_GAME_FILE ".game.lsf"
#define LCS_INFO_FILE "info.lsf"

// C++ only constants, use constexpr
#ifdef __cplusplus

#include <string>

// ____Network Stuff____

/**
    Generates a request url for the server
    @param path the endpoint that you would like to request
*/
__attribute__ ((pure)) inline const std::string serverUrl(const std::string path) {
    std::string url(LCS_SERVER_URL);
    url.append(path);
    return url;
}

__attribute__ ((pure)) inline const std::string cachePath(const std::string subpath) {
    std::string cacheFolder(LCS_CACHE_FOLDER);
    cacheFolder.append(subpath);
    return cacheFolder;
}

__attribute__ ((pure)) inline const std::string tmpPath(const std::string subpath) {
    std::string tmpFolder(LCS_TMP_FOLDER);
    tmpFolder.append("/" + subpath);
    return serverUrl(tmpFolder);
}

// 2024-02-12T17:37:31.6202393-06:00
static const std::string isoTimeFormat = "";


// ____Game, Mod, and Modpack constants____


static inline constexpr short gameIdLength = 6;
static inline constexpr short modIdLength = 56;

#endif

#endif