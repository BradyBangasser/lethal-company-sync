#include "modpack.hpp"
#include "../constants.hpp"
#include "../network/network.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include <http.hpp>
#include <json.hpp>

ModPack::ModPack() {}
ModPack::ModPack(const std::string name, const std::string id, const std::vector<std::string> modIds, uint16_t revision) {
    if (id[0] != 'P') throw ModPackError("");
    this->name = name;
    this->id = id;
    this->modIds = modIds;
    this->revisionNumber = revision;

    this->gameId = id.substr(1, id.find(':'));
    this->slashSepartedId = id;
    std::replace(id.begin(), id.end(), ':', '/');
}

int ModPack::addMod(const std::string id) {
    this->modIds.push_back(id);
    return Status::ALL_GOOD;
}

int ModPack::removeMod(std::string id) noexcept {
    std::vector<std::string>::iterator idIter = std::find(this->modIds.begin(), this->modIds.end(), id);

    if (idIter == this->modIds.end()) {
        return -1; // Mod not found
    }

    this->modIds.erase(idIter);

    return Status::ALL_GOOD;
}

ModPack ModPack::fetch(const std::string id) {
    struct blib_http::Response res; 
    std::string requestUrl = serverUrl(std::format("/{}/", id));
    res = blib_http::request<const struct blib_http::Response>(requestUrl, NULL);

    switch (res.status) {
        case 404:
            throw network::NetworkError(404, "Mod Not found");
        case 502:
            throw network::NetworkError(502, "Server Unreachable");
        case 200:
            return ModPack::fromJSON(res.content);
        default:
            throw network::NetworkError(res.status, "Network error");
    }
}

ModPack ModPack::fromJSON(std::string json) {
    throw Status::NOT_IMPLEMENTED_YET;
}

int ModPack::install() {
    if (isInstalled() == Status::INSTALLED) {
        // Verify that all mods are correctly installed 
    } else {
        
    }
}