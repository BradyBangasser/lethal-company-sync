#include "modpack.hpp"
#include "../constants.hpp"
#include "../network/network.hpp"
#include "../fs/lsf.h"
#include "../mod/mod.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include <http.hpp>
#include <json.hpp>
#include <stdio.h>
#include <list>
#include <thread>

ModPack::ModPack() {}
ModPack::ModPack(const std::string name, const std::string id, const std::vector<std::string> modIds, uint16_t revision) {
    if (id[0] != 'P') throw ModPackError("");
    this->name = name;
    this->id = id;
    this->modIds = modIds;
    this->revisionNumber = revision;

    this->gameId = id.substr(1, id.find(':'));
    this->slashSepartedId = id;
    std::replace(id.begin(), id.end(), ':', PATH_SLASH);
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
        std::string modpackInstallPath = installPath(this->slashSepartedId);
        this->writeLSF(modpackInstallPath);

        std::list<Mod> installJobs;
        std::list<std::string> downloadJobs;


    }
}

int ModPack::writeLSF(const std::string path) {
    struct LSFValue *vals = createLSFValue("id", this->id.c_str());

    if (vals == NULL) {
        return -1;
    }

    if (writeLSFFile(path.c_str(), vals) != 0) {
        freeLSFValues(vals);
        return -1;
    }

    freeLSFValues(vals);
    return 0;
}

ModPack ModPack::fromLSF(const std::string path) {
    throw Status::NOT_IMPLEMENTED_YET;
}