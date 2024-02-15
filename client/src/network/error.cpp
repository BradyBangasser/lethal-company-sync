#include "network.hpp"
#include <string>
#include <format>

network::NetworkError::NetworkError(int code, std::string msg) {
    this->code = code;
    this->msg = msg;
}

const char *network::NetworkError::what() {
    return std::format("[{}] {}", code, msg).c_str();
}