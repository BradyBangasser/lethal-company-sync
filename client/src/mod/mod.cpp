#include "mod.hpp"

#include <json.hpp>
#include <string>
#include <stdio.h>
#include <chrono>
#include <format>
#include <http.hpp>

#include "../util/time.hpp"
#include "../errors.hpp"
#include "../constants.hpp"
#include "../util/utils.h"
#include "../fs/files.hpp"
#include "../fs/lsf.h"

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
    std::string res;

    try {
        res = network::fetchMod(id);
    } catch (network::NetworkError &e) {
        handleError(e);
        throw ;
    }

    return parseJson(res);
}

Mod::ModStatus Mod::install() {
    int result = 0;

    if (this->check() == ModStatus::ALL_GOOD) return ModStatus::ALREADY_INSTALLED;

    printf("%s id\n", id.c_str());
    std::string downloadPath = tmpPath(this->slashSepartedId);

    mkSubDirs(downloadPath.c_str());

    result = this->download(downloadPath);
    if (result != ModStatus::ALL_GOOD) {
        return (ModStatus) result;
    }

    // There will be an unzipping/unpacking algorithm here eventually
    
    // Also add profiles



    result = fmove(downloadPath.c_str(), installPath.c_str());

    if (result != 0) {
        // cry 
        return ModStatus::INTERNAL_ERROR;
    }

    return ModStatus::ALL_GOOD;
}

Mod::ModStatus Mod::check() noexcept {
    return ModStatus::NOT_INSTALLED;
}

Mod::ModStatus Mod::download(const std::string path) {
    int result;

    result = blib_http::request<int>(this->downloadUrl, path);

    if (result != 0) {
        return ModStatus::FAILED_TO_DOWNLOAD;
    }

    uint8_t hash[129];
    uint32_t len;
    result = fsha512(hash, path.c_str(), &len);

    printHexValues(hash, 129, '\0');
    printf("%s this\n", this->hash.c_str());

    if (result != LCS_OK) {
        return ModStatus::INTERNAL_ERROR;
    }

    if (strcmp(this->hash.c_str(), (char *) hash) != 0) {
        // TODO: report this to the server somehow, this will ensure we don't have bad files on the server

        result = remove(path.c_str());
        if (result != 0) {
            return ModStatus::INTERNAL_ERROR;
        }
    }

    return ModStatus::ALL_GOOD;
}

int Mod::writeLSF(const std::string path) noexcept {
    struct LSFValue *vals = createLSFValue("id", this->id.c_str());

    writeLSFFile(path.c_str(), vals);

    freeLSFValues(vals);

    return LCS_OK;
}