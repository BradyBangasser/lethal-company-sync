#include "network.hpp"
#include <string>
#include "../constants.hpp"
#include <http.hpp>
#include <format>

bool verifyIdFormat() {
   return false; 
}

int network::verifyMod(const std::string id) noexcept {

    return NOT_IMPLEMENTED_YET;
} // verifyMod

const std::vector<std::string> network::verifyMod(const std::vector<std::string> mods) {

    throw NOT_IMPLEMENTED_YET;
} // verifyMod

std::string network::fetchMod(const std::string id) {
    // Caching?
    const std::string url = std::format("/mod/{}/", id);
    struct blib_http::Response res = blib_http::request<const struct blib_http::Response>(serverUrl(url), NULL);

    if (res.status != 200) {
        throw network::NetworkError(res.status, std::format("Failed to fetch mod from {}", url));
    }

    return res.content;
}