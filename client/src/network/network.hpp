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
            const char *what();
    };

    int verifyMod(const std::string id) noexcept;
    const std::vector<std::string> verifyMod(const std::vector<std::string>);
    int checkVersion();

    /*
        Attempts to fetch the mod JSON from 
    */
    std::string fetchMod(const std::string id);
}
// Caching needed

#endif