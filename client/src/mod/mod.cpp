#include "mod.hpp"

#include <json.hpp>
#include <string>
#include <stdio.h>
#include <chrono>
#include <format>
#include <http.hpp>
#include <algorithm>
#include <http.hpp>

#include "../util/time.hpp"
#include "../errors.hpp"
#include "../constants.hpp"
#include "../util/utils.h"
#include "../fs/files.hpp"
#include "../fs/lsf.h"
#include "../network/cache.hpp"

using json = nlohmann::json;

bool Mod::verifyId(std::string id) {
    // Consider rewriting in C

    if (id.length() != 1 + modIdLength + gameIdLength) return false;
    std::string gameId, modId;
    if (id[6] != ':') return false;
    gameId = id.substr(0, 6);
    modId = id.substr(7);
    if (modId.length() != 56) return false;
    return true;
}

Mod::Mod(const std::string id, const std::string name, const std::string downloadUrl, const std::string version, const std::string description, const std::chrono::system_clock::time_point creation, const std::string hash) {
    this->id = id;
    this->name = name;
    this->downloadUrl = downloadUrl;
    this->version = version;
    this->description = description;
    this->updated = creation;
    this->hash = hash;

    std::string idc = id;

    std::replace(idc.begin(), idc.end(), ':', PATH_SLASH);
    this->slashSepartedId = idc;
}

Mod Mod::parseJson(std::string jsonString) {
    std::string name, id, downloadUrl, version, description, hash;
    std::chrono::system_clock::time_point timeStamp;

    try {
        json data = json::parse(jsonString);

        name = data["name"].get<std::string>();
        id = data["id"].get<std::string>();
        downloadUrl = data["durl"].get<std::string>();
        version = data["v"].get<std::string>();
        timeStamp = parseTime(data["ts"].get<std::string>());
        description = data["des"].get<std::string>();
        hash = data["hash"].get<std::string>(); 
    } catch (const json::exception &e) {
        handleError(e);
        throw ; 
    }

    return Mod(id, name, downloadUrl, version, description, timeStamp, hash);
}

Mod Mod::fetch(std::string id, bool force) {
    if (!force) {
        // Attempt to fetch from installs or cache


    } else {

    }

    std::string surl = serverUrl(std::format("/mod/{}/", id));

    const struct blib_http::Response bres = blib_http::request<const struct blib_http::Response>(surl);

    switch (bres.status) {
        case 200:
            return parseJson(bres.content);
        case 404:
            throw network::NetworkError(404, "Mod not found");
        case 502:
            throw network::NetworkError(502, "Server is likely down");
        default:
            throw network::NetworkError(bres.status, std::format("Failed to fetch mod from {}", surl));
    }
}

Status Mod::install() {
    int result = 0;

    if (this->check() == Status::ALL_GOOD) return Status::INSTALLED;

    // Change this to use the built in tmpFile
    std::string downloadPath = tmpPath(this->slashSepartedId);

    mkSubDirs(downloadPath.c_str());

    result = this->download(downloadPath);
    if (result != Status::ALL_GOOD) {
        return (Status) result;
    }

    // There will be an unzipping/unpacking algorithm here eventually
    
    // Also add profiles

    result = fmove(downloadPath.c_str(), installPath.c_str());

    if (result != 0) {
        // cry 
        return Status::INTERNAL_ERROR;
    }

    return Status::ALL_GOOD;
}

Status Mod::install(const std::string id) {
    throw Status::NOT_IMPLEMENTED_YET;
}

Status Mod::check() noexcept {
    return Status::NOT_INSTALLED;
}

Status Mod::download(const std::string path, bool force) {
    int result;

    if (!force) {
        if (this->isCached(this->id) == 0) {
            if (cache_manager::fetchFromCache(modDataCache, "/" + this->slashSepartedId, path) != 0) {
                return Status::INTERNAL_ERROR;
            } else {
                return Status::CACHE_HIT;
            }
        }
    }

    result = blib_http::request<int>(this->downloadUrl, path);

    if (result != 0) {
        return Status::DOWNLOAD_FAILED;
    }

    uint8_t hash[129];
    uint32_t len;
    char hashString[129];
    result = fsha512(hash, path.c_str(), &len);

    toHexString(hash, len, hashString);

    if (result != Status::ALL_GOOD) {
        return Status::INTERNAL_ERROR;
    }

    if (strcmp(this->hash.c_str(), (char *) hashString) != 0) {
        // TODO: report this to the server somehow, this will ensure we don't have bad files on the server

        result = remove(path.c_str());
        if (result != 0) {
            return Status::INTERNAL_ERROR;
        }
    }

    // Caching

    cache_manager::cacheInsert(modDataCache, "/" + this->slashSepartedId, path);

    return Status::ALL_GOOD;
}

int Mod::writeLSF(const std::string path) noexcept {
    struct LSFValue *vals = createLSFValue("id", this->id.c_str());

    writeLSFFile(path.c_str(), vals);

    freeLSFValues(vals);

    return Status::ALL_GOOD;
}

int Mod::isCached(std::string modId) noexcept {
    using namespace cache_manager;
    std::replace(modId.begin(), modId.end(), ':', '/');
    Status result = checkCache("/mod", "/" + modId);

    if (result == Status::CACHE_HIT) {
        return 0;
    } else {
        return -1;
    }
}