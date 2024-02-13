#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define NOT_IMPLEMENTED_YET -99999
#define OK 1

#define SERVER_URL "http://30a33f28add4471e323d6707a36ffcfd.serveo.net"

// C++ only constants, use constexpr
#ifdef __cplusplus

#include <string>

__attribute__ ((pure)) inline const std::string serverUrl(const std::string path) {
    std::string url(SERVER_URL);
    url.append(path);
    return url;
}

#endif

#endif