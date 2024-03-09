#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <vector>

namespace network {

    class NetworkError : public std::exception {
        private:
            std::string msg;
            int code;
        public:
            NetworkError() = delete;
            NetworkError(int code, std::string msg);
            virtual const char *what();
    };

    int checkVersion();
}
// Caching needed

#endif