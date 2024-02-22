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
#define LCS_SERVER_URL "http://30a33f28add4471e323d6707a36ffcfd.serveo.net"

// C++ only constants, use constexpr
#ifdef __cplusplus

#include <string>

// ____Network Stuff____

/*
    Generates a request url for the server
    @param path the endpoint that you would like to request
*/
__attribute__ ((pure)) inline const std::string serverUrl(const std::string path) {
    std::string url(LCS_SERVER_URL);
    url.append(path);
    return url;
}

// 2024-02-12T17:37:31.6202393-06:00
static const std::string isoTimeFormat = "";


// ____Game, Mod, and Modpack constants____


static inline constexpr short gameIdLength = 6;
static inline constexpr short modIdLength = 56;

#endif

#endif