#include "mod.hpp"

#include <json.hpp>
#include <string>
#include <stdio.h>
#include <chrono>
#include "../util/time.hpp"
#include "../errors.hpp"
#include "../constants.hpp"

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

    this->installed = false;
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

Mod Mod::fetch(std::string id) {

    


    std::string res;

    try {
        res = network::fetchMod(id);
    } catch (network::NetworkError &e) {
        handleError(e);
        throw ;
    }

    return parseJson(res);
}

ModStatus Mod::check() {
    return ModStatus::NOT_INSTALLED;
}